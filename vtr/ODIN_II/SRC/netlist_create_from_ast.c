/*

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/ 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "globals.h"
#include "errors.h"
#include "netlist_utils.h"
#include "odin_util.h"
#include "ast_util.h"
#include "netlist_create_from_ast.h"
#include "string_cache.h"
#include "netlist_visualizer.h"
#include "parse_making_ast.h"
#include "node_creation_library.h"
#include "util.h"
#include "multipliers.h"
#include "hard_blocks.h"
#include "memories.h"

/* NAMING CONVENTIONS
 {previous_string}.module_name+instance_name
 {previous_string}.module_name+instance_name^signal_name
 {previous_string}.module_name+instance_name^signal_name~bit
*/

#define INSTANTIATE_DRIVERS 1
#define ALIAS_INPUTS 2

#define COMBINATIONAL 1
#define SEQUENTIAL 2

STRING_CACHE *output_nets_sc;
STRING_CACHE *input_nets_sc;

STRING_CACHE *local_symbol_table_sc;
STRING_CACHE *global_param_table_sc;
ast_node_t** local_symbol_table;
int num_local_symbol_table;
signal_list_t *local_clock_list;
short local_clock_found;
int local_clock_idx;

/* CONSTANT NET ELEMENTS */
char *one_string = "ONE_VCC_CNS";
char *zero_string = "ZERO_GND_ZERO";
char *pad_string = "ZERO_PAD_ZERO";

ast_node_t *top_module;

netlist_t *verilog_netlist;

int netlist_create_line_number = -2;

int type_of_circuit;

/* PROTOTYPES */

void convert_ast_to_netlist_recursing_via_modules(ast_node_t* current_module, char *instance_name, int level);
signal_list_t *netlist_expand_ast_of_module(ast_node_t* node, char *instance_name_prefix);

void create_all_driver_nets_in_this_module(char *instance_name_prefix);

ast_node_t *find_top_module();

void create_top_driver_nets(ast_node_t* module, char *instance_name_prefix);
void create_top_output_nodes(ast_node_t* module, char *instance_name_prefix);
nnet_t* define_nets_with_driver(ast_node_t* var_declare, char *instance_name_prefix);
nnet_t* define_nodes_and_nets_with_driver(ast_node_t* var_declare, char *instance_name_prefix);

void connect_hard_block_and_alias(ast_node_t* module_instance, char *instance_name_prefix);
void connect_module_instantiation_and_alias(short PASS, ast_node_t* module_instance, char *instance_name_prefix);
void create_symbol_table_for_module(ast_node_t* module_items, char *module_name);

signal_list_t *concatenate_signal_lists(signal_list_t **signal_lists, int num_signal_lists);

signal_list_t *create_gate(ast_node_t* gate, char *instance_name_prefix);
signal_list_t *create_hard_block(ast_node_t* block, char *instance_name_prefix);
signal_list_t *create_pins(ast_node_t* var_declare, char *name, char *instance_name_prefix);
signal_list_t *create_output_pin(ast_node_t* var_declare, char *instance_name_prefix);
signal_list_t *assignment_alias(ast_node_t* assignment, char *instance_name_prefix);
signal_list_t *create_operation_node(ast_node_t *op, signal_list_t **input_lists, int list_size, char *instance_name_prefix);

void terminate_continuous_assignment(ast_node_t *node, signal_list_t* assignment, char *instance_name_prefix);
void terminate_registered_assignment(ast_node_t *always_node, signal_list_t* assignment, signal_list_t *potential_clocks, char *instance_name_prefix);

signal_list_t *create_case(ast_node_t *case_ast, char *instance_name_prefix);
void create_case_control_signals(ast_node_t *case_list_of_items, ast_node_t *compare_against, nnode_t *case_node, char *instance_name_prefix);
signal_list_t *create_case_mux_statements(ast_node_t *case_list_of_items, nnode_t *case_node, char *instance_name_prefix);
signal_list_t *create_if(ast_node_t *if_ast, char *instance_name_prefix);
void create_if_control_signals(ast_node_t *if_expression, nnode_t *if_node, char *instance_name_prefix);
signal_list_t *create_if_mux_statements(ast_node_t *if_ast, nnode_t *if_node, char *instance_name_prefix);
signal_list_t *create_if_for_question(ast_node_t *if_ast, char *instance_name_prefix);
signal_list_t *create_if_question_mux_expressions(ast_node_t *if_ast, nnode_t *if_node, char *instance_name_prefix);
signal_list_t *create_mux_statements(signal_list_t **statement_lists, nnode_t *case_node, int num_statement_lists, char *instance_name_prefix);
signal_list_t *create_mux_expressions(signal_list_t **expression_lists, nnode_t *mux_node, int num_expression_lists, char *instance_name_prefix);

signal_list_t *evaluate_sensitivity_list(ast_node_t *delay_control, char *instance_name_prefix);

int alias_output_assign_pins_to_inputs(char_list_t *output_list, signal_list_t *input_list, ast_node_t *node);

int find_smallest_non_numerical(ast_node_t *node, signal_list_t **input_list, int num_input_lists);
void pad_with_zeros(ast_node_t* node, signal_list_t *list, int pad_size, char *instance_name_prefix);

void look_for_clocks(netlist_t *netlist);

/*----------------------------------------------------------------------------
 * (function: create_param_table_for_module)
 *--------------------------------------------------------------------------*/
/**
 * Scan through all VAR_DECLARE_LISTs in MODULE_ITEMS and create a hash table
 * for all parameters in this instantiation, taking into account if they
 * are being overridden by their parent
 */
void create_param_table_for_module(ast_node_t* parent_parameter_list, ast_node_t *module_items, char *module_name)
{
	/* with the top module we need to visit the entire ast tree */
	int i, j;
	char *temp_string;
	long sc_spot;
	oassert(module_items->type == MODULE_ITEMS);
	int parameter_idx;
	STRING_CACHE *local_param_table_sc;
	parameter_idx = 0;

	sc_spot = sc_add_string(global_param_table_sc, module_name);
	if (global_param_table_sc->data[sc_spot] != NULL) 
		return;
	local_param_table_sc = sc_new_string_cache();
	global_param_table_sc->data[sc_spot] = local_param_table_sc;

	/* search for VAR_DECLARE_LISTS */
	if (module_items->num_children > 0)
	{
		for (i = 0; i < module_items->num_children; i++)
		{
			if (module_items->children[i]->type == VAR_DECLARE_LIST)
			{
				/* go through the vars in this declare list */
				for (j = 0; j < module_items->children[i]->num_children; j++)
				{	
					ast_node_t *var_declare = module_items->children[i]->children[j];

					if (	(var_declare->types.variable.is_input) ||
						(var_declare->types.variable.is_output) ||
						(var_declare->types.variable.is_reg) ||
						(var_declare->types.variable.is_wire)) continue;

					oassert(module_items->children[i]->children[j]->type == VAR_DECLARE);
					oassert(var_declare->types.variable.is_parameter);

					/* make the string to add to the string cache */
					temp_string = make_full_ref_name(NULL, NULL, NULL, var_declare->children[0]->types.identifier, -1);

					if (var_declare->types.variable.is_parameter)
					{
						if (parent_parameter_list)
						{
							// Ensure that there are no more parameters in this module than 
							// there are specified in the parent parameter list
							if (parameter_idx < parent_parameter_list->num_children)
							{
								// Use parent-specified parameter value instead of default
								// This node looks identical to the default node below, 
								// as far as get_name_of_pins() is concerned
								var_declare = parent_parameter_list->children[parameter_idx];
							}
							else
								warning_message(NETLIST_ERROR, parent_parameter_list->line_number, parent_parameter_list->file_number, 
									"There are more parameters (>%d) in %s than there are specified in the module instantiation (%d)!", 
									parameter_idx, module_name, parent_parameter_list->num_children);
							parameter_idx++;
						}
						ast_node_t *node = resolve_node(module_name, var_declare->children[5]);
						oassert(node->type == NUMBERS);
						//fprintf(stderr, "Parameter instance found: %s:%s = %d\n", module_name, temp_string, node->types.number.value);
						sc_spot = sc_add_string(local_param_table_sc, temp_string);
						local_param_table_sc->data[sc_spot] = (void *)node;
					}
					free(temp_string);
				}
			}
		}
	}
}



/*---------------------------------------------------------------------------------------------
 * (function: create_netlist)
 *--------------------------------------------------------------------------*/
void create_netlist()
{
	/* just build all the fundamental elements, and then hookup with port definitions...every net has
	 * a named net as a variable instance...even modules...the only trick with modules will
	 * be instance names.  There are a few implied nets as in Muxes for cases, signals
	 * for flip-flops and memories */

	// Alias the symbol nodes in ast_modules to the actual MODULE nodes
	int i;
	for (i = 0; i < num_modules; i++)
	{
		if (ast_modules[i]->type == IDENTIFIERS)
		{
			// double check that it's in modules_names_to_idx
			char *module_param_name = ast_modules[i]->types.identifier;
			long sc_spot = sc_lookup_string(module_names_to_idx, module_param_name);
			oassert(sc_spot > -1);
			// now isolate the original module name
			char *underscores = strstr(module_param_name, "___");
			oassert(underscores);
			int len = underscores - module_param_name;
			char *module_name = (char *)malloc((len+1)*sizeof(char));
			strncpy(module_name, module_param_name, len);
			module_name[len] = '\0';
			// verify that it does exist
			long sc_spot2 = sc_lookup_string(module_names_to_idx, module_name);
			oassert(sc_spot2 > -1);
			free(module_name);
			// create a new MODULE node with new IDENTIFIER, but keep same ports and module_items
			ast_node_t *module = (ast_node_t *)module_names_to_idx->data[sc_spot2];
			ast_node_t *symbol_node = newSymbolNode(module_param_name, module->line_number);
			ast_node_t* new_node = create_node_w_type(MODULE, module->line_number, module->file_number);
			allocate_children_to_node(new_node, 3, symbol_node, module->children[1], module->children[2]);
			new_node->types.module.index = i;
			// and to the module_names_to_idx for parameterised name
			module_names_to_idx->data[sc_spot] = new_node;
			ast_modules[i] = new_node;
		}
		oassert(ast_modules[i]->type == MODULE);
	}

	/* we will find the top module */
	top_module = find_top_module();

	/* Since the modules are in a tree, we will bottom up build the netlist.  Essentially,
	 * we will go to the leafs of the module tree, build them upwards such that when we search for the nets,
	 * we will find them and can hook them up at that point */

	/* PASS 1 - we make all the nets based on registers defined in modules */
	
	/* initialize the string caches that hold the aliasing of module nets and input pins */
	output_nets_sc = sc_new_string_cache();
	input_nets_sc = sc_new_string_cache();
	/* initialize the storage of the top level drivers.  Assigned in create_top_driver_nets */
	verilog_netlist = allocate_netlist();

	// create the parameter table for the top module
	create_param_table_for_module(NULL, top_module->children[2], "top");

	/* now recursively parse the modules by going through the tree of modules starting at top */
	create_top_driver_nets(top_module, "top");
	convert_ast_to_netlist_recursing_via_modules(top_module, "top", 0);
	create_top_output_nodes(top_module, "top");

	/* now look for high-level signals */
	look_for_clocks(verilog_netlist); 
}

/*---------------------------------------------------------------------------------------------
   * (function: look_for_clocks)
 *-------------------------------------------------------------------------------------------*/
void look_for_clocks(netlist_t *netlist)
{
	int i; 

	for (i = 0; i < netlist->num_ff_nodes; i++)
	{
		if (netlist->ff_nodes[i]->input_pins[1]->net->driver_pin->node->type != CLOCK_NODE)
		{
			netlist->ff_nodes[i]->input_pins[1]->net->driver_pin->node->type = CLOCK_NODE;
		}
	}
}

/*---------------------------------------------------------------------------------------------
 * (function: find_top_module)
 * 	Finds the top module based on that it is not called by anyone else
 * 	Assumes there is only one top
 *-------------------------------------------------------------------------------------------*/
ast_node_t *find_top_module()
{
	int i, j;
	long sc_spot;
	int found_top = -1;

	/* go through all the instantiations for each module and mark them if they've be instantiated */
	for (i = 0; i < num_modules; i++)
	{
		for (j = 0; j < ast_modules[i]->types.module.size_module_instantiations; j++)
		{
			/* Check to see if the module is a hard block - a hard block is 
				never the top level! */
#ifdef VPR6
			if ((sc_spot = sc_lookup_string(hard_block_names, ast_modules[i]->types.module.module_instantiations_instance[j]->children[0]->types.identifier)) == -1)
#endif
			{
				/* get the module index from the string cache */
				if ((sc_spot = sc_lookup_string(module_names_to_idx, 
								ast_modules[i]->types.module.module_instantiations_instance[j]->children[0]->types.identifier)) == -1)
				{
					error_message(NETLIST_ERROR, 
							ast_modules[i]->line_number, 
							ast_modules[i]->file_number, 
							"Can't find module name (%s)\n", 
							ast_modules[i]->types.module.module_instantiations_instance[j]->children[0]->types.identifier);
				}

				/* use that number to mark this module as instantiated */
				ast_modules[((ast_node_t*)module_names_to_idx->data[sc_spot])->types.module.index]->types.module.is_instantiated = TRUE;
			}
		}
	}

	/* now check for which module wasn't marked...this one will be the top */
	for (i = 0; i < num_modules; i++)
	{
		if ((ast_modules[i]->types.module.is_instantiated == FALSE) && (found_top == -1))
		{
			found_top = i;
		}
		else if ((ast_modules[i]->types.module.is_instantiated == FALSE) && (found_top != -1))
		{
			error_message(NETLIST_ERROR, ast_modules[i]->line_number, ast_modules[i]->file_number,
					"Two top level modules - Odin II cannot deal with these types of designs\n");
		}
	}

	/* check atleast one module is top ... and only one */
	if (found_top == -1)
	{
		error_message(NETLIST_ERROR, -1, -1, "Could not find a top level module\n");
	}

	return ast_modules[found_top];
}

/*---------------------------------------------------------------------------------------------
 * (function: convert_ast_to_netlist_recursing_via_modules)
 * 	Recurses through modules by depth first traversal of the tree of modules.  Expands
 * 	the netlists at each level.
 *-------------------------------------------------------------------------------------------*/
void convert_ast_to_netlist_recursing_via_modules(ast_node_t* current_module, char *instance_name, int level)
{
	signal_list_t *list = NULL;

	/* BASE CASE is when there are no other instantiations of modules in this module */
	if (current_module->types.module.size_module_instantiations == 0)
	{
		list = netlist_expand_ast_of_module(current_module, instance_name);
	}
	else
	{
		/* ELSE - we need to visit all the children before */
		int i;
		for (i = 0; i < current_module->types.module.size_module_instantiations; i++)
		{
			/* make the stringed up module instance name - instance name is
			 * MODULE_INSTANCE->MODULE_NAMED_INSTANCE(child[1])->IDENTIFIER(child[0]).
			 * module name is MODULE_INSTANCE->IDENTIFIER(child[0])
			 */
			char *temp_instance_name = make_full_ref_name(instance_name,
					current_module->types.module.module_instantiations_instance[i]->children[0]->types.identifier,
					current_module->types.module.module_instantiations_instance[i]->children[1]->children[0]->types.identifier,
					NULL, -1);

			long sc_spot;
			/* lookup the name of the module associated with this instantiated point */
			if ((sc_spot = sc_lookup_string(module_names_to_idx, current_module->types.module.module_instantiations_instance[i]->children[0]->types.identifier)) == -1)
			{
				error_message(NETLIST_ERROR, current_module->line_number, current_module->file_number,
						"Can't find module name %s\n", current_module->types.module.module_instantiations_instance[i]->children[0]->types.identifier);
			}

			ast_node_t *parent_parameter_list = current_module->types.module.module_instantiations_instance[i]->children[1]->children[2];
			// create the parameter table for the instantiated module
			create_param_table_for_module(parent_parameter_list,
				/* module_items */
				((ast_node_t*)module_names_to_idx->data[sc_spot])->children[2],
				temp_instance_name);

			/* recursive call point */
			convert_ast_to_netlist_recursing_via_modules(((ast_node_t*)module_names_to_idx->data[sc_spot]), temp_instance_name, level+1);

			/* free the string */
			free(temp_instance_name);
		}
		
		/* once we've done everyone lower, we can do this module */
		list = netlist_expand_ast_of_module(current_module, instance_name);
	}

	if (list) clean_signal_list_structure(list);
}

/*---------------------------------------------------------------------------
 * (function: netlist_expand_ast_of_module)
 * 	Main recursion point that looks at the abstract syntax tree.
 * 	Allows for a pre amble, looks at children (dfs), then does post amble
 * 	Can skip children traverse and the ambles...
 *-------------------------------------------------------------------------*/
signal_list_t *netlist_expand_ast_of_module(ast_node_t* node, char *instance_name_prefix)
{
	/* with the top module we need to visit the entire ast tree */
	int i;
	short *child_skip_list = NULL; // list of children not to traverse into
	short skip_children = FALSE; // skips the DFS completely if TRUE 
	signal_list_t *return_sig_list = NULL;
	signal_list_t **children_signal_list = NULL;

	if (node == NULL)
	{
		/* print out the node and label details */
	}
	else
	{
		/* make a skip list of nodes in the tree we don't need to visit for this node.
		 * For example, a module we know that the 0th entry is the identifier of the module */
		if (node->num_children > 0)
		{
			child_skip_list = (short*)calloc(node->num_children, sizeof(short));
			children_signal_list = (signal_list_t**)malloc(sizeof(signal_list_t*)*node->num_children);
		}

		/* ------------------------------------------------------------------------------*/
		/* PREAMBLE */
		switch(node->type)
		{
			case FILE_ITEMS:
				oassert(FALSE);
				break;
			case MODULE: 
				/* set the skip list */
				child_skip_list[0] = TRUE; /* skip the identifier */
				child_skip_list[1] = TRUE; /* skip portlist ... we'll use where they're defined */
				break;
			case MODULE_ITEMS: 
				/* items include: wire, reg, input, outputs, assign, gate, module_instance, always */

				/* make the symbol table */
				local_symbol_table_sc = sc_new_string_cache();
				local_symbol_table = NULL;
				num_local_symbol_table = 0;
				create_symbol_table_for_module(node, instance_name_prefix);
				local_clock_found = FALSE;

				/* create all the driven nets based on the "reg" registers */		
				create_all_driver_nets_in_this_module(instance_name_prefix);

				/* process elements in the list */
				if (node->num_children > 0)
				{
					for (i = 0; i < node->num_children; i++)
					{
						if (node->children[i]->type == VAR_DECLARE_LIST)
						{
							/* IF - The port lists of this module are handled else where */
							child_skip_list[i] = TRUE;
						}
						else if (node->children[i]->type == MODULE_INSTANCE)
						{
							/* ELSE IF - we deal with instantiations of modules twice to alias input and output nets.  In this
							 * pass we are looking for any drivers emerging from a module */

							/* make the aliases for all the drivers as they're passed through modules */
							connect_module_instantiation_and_alias(INSTANTIATE_DRIVERS, node->children[i], instance_name_prefix);

							/* is a call site for another module.  Alias names to nets and pins */
							child_skip_list[i] = TRUE;
						}
					}
				}
				break;
			case GATE:
				/* create gate instances */
				return_sig_list = create_gate(node, instance_name_prefix);
				/* create_gate does it's own instantiations so skip the children in the traverse */
				skip_children = TRUE;
				break;
			/* ---------------------- */
			/* All these are input references that we need to grab their pins from by create_pin */
			case ARRAY_REF:
			case IDENTIFIERS:
			case RANGE_REF:
			case NUMBERS: 
			{
				return_sig_list = create_pins(node, NULL, instance_name_prefix);
				/* children are traversed in the create_pin function */
				//skip_children = TRUE;
				break;
			}
			/* ---------------------- */
			case ASSIGN:
				/* combinational path */
				type_of_circuit = COMBINATIONAL;
				break;
			case BLOCKING_STATEMENT:
				if (type_of_circuit == SEQUENTIAL)
				{
					error_message(NETLIST_ERROR, node->line_number, node->file_number,
							"ODIN doesn't handle blocking statements in Sequential blocks\n");
				}
				else
				{
					return_sig_list = assignment_alias(node, instance_name_prefix); 	
					skip_children = TRUE;
				}
				break;
			case NON_BLOCKING_STATEMENT:
				if (type_of_circuit != SEQUENTIAL)
				{
					error_message(NETLIST_ERROR, node->line_number, node->file_number,
							"ODIN doesn't handle non blocking statements in combinational blocks\n");
				}
				return_sig_list = assignment_alias(node, instance_name_prefix); 	
				skip_children = TRUE;
				break;
			case ALWAYS:
				/* evaluate if this is a sensitivity list with posedges/negedges (=SEQUENTIAL) or none (=COMBINATIONAL) */
				local_clock_list = evaluate_sensitivity_list(node->children[0], instance_name_prefix);
				child_skip_list[0] = TRUE;
				break;
			case CASE:
				return_sig_list = create_case(node, instance_name_prefix);
				skip_children = TRUE;
				break;
			case IF:
				return_sig_list = create_if(node, instance_name_prefix);
				skip_children = TRUE;
				break;
			case IF_Q:
				return_sig_list = create_if_for_question(node, instance_name_prefix);
				skip_children = TRUE;
				break;
#ifdef VPR6
			case HARD_BLOCK:
				/* set the skip list */
				child_skip_list[0] = TRUE; /* skip the identifier */
				child_skip_list[1] = TRUE; /* skip portlist ... we'll use where they're defined */
				return_sig_list = create_hard_block(node, instance_name_prefix);
				break;
#endif
			default:
				break;
		}	
		/* ------------------------------------------------------------------------------*/
		/* This is the depth first traverse (DFT aka DFS) of the ast nodes that make up the netlist. */
		if (skip_children == FALSE)
		{
			/* traverse all the children */
			for (i = 0; i < node->num_children; i++)
			{
				if (child_skip_list[i] == FALSE)
				{
					/* recursively call through the tree going to each instance.  This is depth first traverse. */
					children_signal_list[i] = netlist_expand_ast_of_module(node->children[i], instance_name_prefix);
				}
			}
		}

		/* ------------------------------------------------------------------------------*/
		/* POST AMBLE - process the children */
		switch(node->type)
		{
			case FILE_ITEMS:
				error_message(NETLIST_ERROR, node->line_number, node->file_number,
						"FILE_ITEMS are not supported by Odin.\n");
				break;
			case CONCATENATE:
				return_sig_list = concatenate_signal_lists(children_signal_list, node->num_children);
				break;
			case MODULE_ITEMS: 
			{
				if (node->num_children > 0)
				{
					for (i = 0; i < node->num_children; i++)
					{
						if (node->children[i]->type == MODULE_INSTANCE)
						{
							/* make the aliases for all the drivers as they're passed through modules.  This is the
 							second time we call this */
							connect_module_instantiation_and_alias(ALIAS_INPUTS, node->children[i], instance_name_prefix);
						}
					}
				}

				/* free the symbol table for this module since we're done processing */
				sc_free_string_cache(local_symbol_table_sc);
				free(local_symbol_table);

				break;
			}
			case ASSIGN:
				oassert(node->num_children == 1);	
				/* attach the drivers to the driver nets */
				terminate_continuous_assignment(node, children_signal_list[0], instance_name_prefix); 	
				break;
			case ALWAYS:
				/* attach the drivers to the driver nets */
				if (type_of_circuit == COMBINATIONAL)
				{
					/* idx 1 element since always has DELAY Control first */
					terminate_continuous_assignment(node, children_signal_list[1], instance_name_prefix); 	
				}
				else if (type_of_circuit == SEQUENTIAL)
				{
					terminate_registered_assignment(node, children_signal_list[1], local_clock_list, instance_name_prefix); 	
				}
				else
					oassert(FALSE);
				break;
			case BINARY_OPERATION: 
				oassert(node->num_children == 2);
				return_sig_list = create_operation_node(node, children_signal_list, node->num_children, instance_name_prefix);
				break;
			case UNARY_OPERATION:
				oassert(node->num_children == 1);
				return_sig_list = create_operation_node(node, children_signal_list, node->num_children, instance_name_prefix);
				break;
			case BLOCK: 
				return_sig_list = combine_lists(children_signal_list, node->num_children);
				break;
			#ifdef VPR6
			case RAM: 
				connect_memory_and_alias(node, instance_name_prefix);
				break;
			case HARD_BLOCK: 
				connect_hard_block_and_alias(node, instance_name_prefix);
				break;
			#endif
			case IF:
			default:
				break;
		}
		/* ------------------------------------------------------------------------------*/
	}

	/* cleaning */
	if (child_skip_list != NULL)
	{
		free(child_skip_list);
	}
	if (children_signal_list != NULL)
	{
		free(children_signal_list);
	}

	return return_sig_list;
}


signal_list_t *concatenate_signal_lists(signal_list_t **signal_lists, int num_signal_lists)
{
	signal_list_t *return_list = init_signal_list_structure();

	int i;
	for (i = num_signal_lists - 1; i >= 0; i--)
	{
		// When concatenating, ignore the carry out from adders so that they occupy the expected width.
		if (signal_lists[i]->is_adder)
			signal_lists[i]->signal_list_size--;

		int j;
		for (j = 0; j < signal_lists[i]->signal_list_size; j++)
		{
			npin_t *pin = signal_lists[i]->signal_list[j];
			add_pin_to_signal_list(return_list, pin);
		}
		clean_signal_list_structure(signal_lists[i]);
	}

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_all_driver_nets_in_this_module)
 * 	Use to define all the nets that will connect to instantiated nodes.  This means we go
 * 	through the var_declare_list of module variables and all registers are made
 * 	as drivers.
 *-------------------------------------------------------------------------------------------*/
void create_all_driver_nets_in_this_module(char *instance_name_prefix)
{
	/* with the top module we need to visit the entire ast tree */
	int i;

	/* use the symbol table to decide if driver */
	for (i = 0; i < num_local_symbol_table; i++)
	{
		oassert(local_symbol_table[i]->type == VAR_DECLARE);
		if (
			/* all registers are drivers */
				(local_symbol_table[i]->types.variable.is_reg)
			/* a wire that is an input can be a driver */
			|| (
					   (local_symbol_table[i]->types.variable.is_wire)
					&& (!local_symbol_table[i]->types.variable.is_input)
			)
			/* any output that has nothing else is an implied wire driver */
			|| (
					   (local_symbol_table[i]->types.variable.is_output)
					&& (!local_symbol_table[i]->types.variable.is_reg)
					&& (!local_symbol_table[i]->types.variable.is_wire)
			)
		   )
		{
			/* create nets based on this driver as the name */
			define_nets_with_driver(local_symbol_table[i], instance_name_prefix);
		}

	}
}

/*--------------------------------------------------------------------------
 * (function: create_top_driver_nets)
 * 	This function creates the drivers for the top module.  Top module is 
 * 	slightly special since all inputs are actually drivers.
 * 	Also make the 0 and 1 constant nodes at this point.
 *  Note: Also creates hbpad signal for padding hard block inputs.
 *-------------------------------------------------------------------------*/
void create_top_driver_nets(ast_node_t* module, char *instance_name_prefix)
{
	/* with the top module we need to visit the entire ast tree */
	int i, j;
	long sc_spot;
	ast_node_t *module_items = module->children[2];
	npin_t *new_pin;

	oassert(module_items->type == MODULE_ITEMS);

	/* search for VAR_DECLARE_LISTS */
	if (module_items->num_children > 0)
	{
		for (i = 0; i < module_items->num_children; i++)
		{
			if (module_items->children[i]->type == VAR_DECLARE_LIST)
			{
				/* go through the vars in this declare list looking for inputs to make drivers */
				for (j = 0; j < module_items->children[i]->num_children; j++)
				{	
					if (module_items->children[i]->children[j]->types.variable.is_input)
					{
						define_nodes_and_nets_with_driver(module_items->children[i]->children[j], instance_name_prefix);
					}
				}
			}
		}
	}
	else
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Module is empty\n");
	}

	/* create the constant nets */
	verilog_netlist->zero_net = allocate_nnet();
	verilog_netlist->gnd_node = allocate_nnode();
	verilog_netlist->gnd_node->type = GND_NODE;
	allocate_more_node_output_pins(verilog_netlist->gnd_node, 1);
	add_output_port_information(verilog_netlist->gnd_node, 1);
	new_pin = allocate_npin();
	add_a_output_pin_to_node_spot_idx(verilog_netlist->gnd_node, new_pin, 0);
	add_a_driver_pin_to_net(verilog_netlist->zero_net, new_pin);

	verilog_netlist->one_net = allocate_nnet();
	verilog_netlist->vcc_node = allocate_nnode();
	verilog_netlist->vcc_node->type = VCC_NODE;
	allocate_more_node_output_pins(verilog_netlist->vcc_node, 1);
	add_output_port_information(verilog_netlist->vcc_node, 1);
	new_pin = allocate_npin();
	add_a_output_pin_to_node_spot_idx(verilog_netlist->vcc_node, new_pin, 0);
	add_a_driver_pin_to_net(verilog_netlist->one_net, new_pin);

	verilog_netlist->pad_net = allocate_nnet();
	verilog_netlist->pad_node = allocate_nnode();
	verilog_netlist->pad_node->type = PAD_NODE;
	allocate_more_node_output_pins(verilog_netlist->pad_node, 1);
	add_output_port_information(verilog_netlist->pad_node, 1);
	new_pin = allocate_npin();
	add_a_output_pin_to_node_spot_idx(verilog_netlist->pad_node, new_pin, 0);
	add_a_driver_pin_to_net(verilog_netlist->pad_net, new_pin);

	/* CREATE the driver for the ZERO */
	zero_string = make_full_ref_name(instance_name_prefix, NULL, NULL, zero_string, -1);
	verilog_netlist->gnd_node->name = zero_string;

	sc_spot = sc_add_string(output_nets_sc, zero_string);
	if (output_nets_sc->data[sc_spot] != NULL)
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Error in Odin\n");
	}
	/* store the data which is an idx here */
	output_nets_sc->data[sc_spot] = (void*)verilog_netlist->zero_net;
	verilog_netlist->zero_net->name = zero_string;

	/* CREATE the driver for the ONE and store twice */
	one_string = make_full_ref_name(instance_name_prefix, NULL, NULL, one_string, -1);
	verilog_netlist->vcc_node->name = one_string;

	sc_spot = sc_add_string(output_nets_sc, one_string);
	if (output_nets_sc->data[sc_spot] != NULL)
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Error in Odin\n");
	}
	/* store the data which is an idx here */
	output_nets_sc->data[sc_spot] = (void*)verilog_netlist->one_net;
	verilog_netlist->one_net->name = one_string;

	/* CREATE the driver for the PAD */
	pad_string = make_full_ref_name(instance_name_prefix, NULL, NULL, pad_string, -1);
	verilog_netlist->pad_node->name = pad_string;

	sc_spot = sc_add_string(output_nets_sc, pad_string);
	if (output_nets_sc->data[sc_spot] != NULL)
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Error in Odin\n");
	}
	/* store the data which is an idx here */
	output_nets_sc->data[sc_spot] = (void*)verilog_netlist->pad_net;
	verilog_netlist->pad_net->name = pad_string;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_top_output_nodes)
 * 	This function is for the top module and makes references for the output pins
 * 	as actual nodes in the netlist and hooks them up to the netlist as it has been 
 * 	created.  Therefore, this is one of the last steps when creating the netlist.
 *-------------------------------------------------------------------------------------------*/
void create_top_output_nodes(ast_node_t* module, char *instance_name_prefix)
{
	/* with the top module we need to visit the entire ast tree */
	int i, j, k;
	long sc_spot;
	ast_node_t *module_items = module->children[2];
	nnode_t *new_node;

	oassert(module_items->type == MODULE_ITEMS);

	/* search for VAR_DECLARE_LISTS */
	if (module_items->num_children > 0)
	{
		for (i = 0; i < module_items->num_children; i++)
		{
			if (module_items->children[i]->type == VAR_DECLARE_LIST)
			{
				/* go through the vars in this declare list */
				for (j = 0; j < module_items->children[i]->num_children; j++)
				{	
					if (module_items->children[i]->children[j]->types.variable.is_output)
					{
						char *full_name;
						ast_node_t *var_declare = module_items->children[i]->children[j];
						npin_t *new_pin;

						/* decide what type of variable this is */
						if (var_declare->children[1] == NULL)
						{
							/* IF - this is a identifier then find it in the output_nets and hook it up to a newly created node */
							/* get the name of the pin */
							full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, -1);
	
							/* check if the instantiation pin exists. */
							if ((sc_spot = sc_lookup_string(output_nets_sc, full_name)) == -1)
							{
								error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
										"Output pin (%s) is not hooked up!!!\n", full_name);
							}
	
							new_pin = allocate_npin();
							/* hookup this pin to this net */
							add_a_fanout_pin_to_net((nnet_t*)output_nets_sc->data[sc_spot], new_pin);
	
							/* create the node */
							new_node = allocate_nnode();
							new_node->related_ast_node = module_items->children[i]->children[j];
							new_node->name = full_name;
							new_node->type = OUTPUT_NODE;
							/* allocate the pins needed */
							allocate_more_node_input_pins(new_node, 1);
							add_input_port_information(new_node, 1);
	
							/* hookup the pin, and node */
							add_a_input_pin_to_node_spot_idx(new_node, new_pin, 0);

							/* record this node */	
							verilog_netlist->top_output_nodes = realloc(verilog_netlist->top_output_nodes, sizeof(nnode_t*)*(verilog_netlist->num_top_output_nodes+1));
							verilog_netlist->top_output_nodes[verilog_netlist->num_top_output_nodes] = new_node;
							verilog_netlist->num_top_output_nodes++;
						}	
						else if (var_declare->children[3] == NULL)
						{
							ast_node_t *node_max = resolve_node(instance_name_prefix, var_declare->children[1]);
							ast_node_t *node_min = resolve_node(instance_name_prefix, var_declare->children[2]);
							oassert(node_min->type == NUMBERS && node_max->type == NUMBERS);
							/* assume digit 1 is largest */
							for (k = node_min->types.number.value; k <= node_max->types.number.value; k++)
							{
								/* get the name of the pin */
								full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, k);
		
								/* check if the instantiation pin exists. */
								if ((sc_spot = sc_lookup_string(output_nets_sc, full_name)) == -1)
								{
									error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
											"Output pin (%s) is not hooked up!!!\n", full_name);
								}
								new_pin = allocate_npin();
								/* hookup this pin to this net */
								add_a_fanout_pin_to_net((nnet_t*)output_nets_sc->data[sc_spot], new_pin);
		
								/* create the node */
								new_node = allocate_nnode();
								new_node->related_ast_node = module_items->children[i]->children[j];
								new_node->name = full_name;
								new_node->type = OUTPUT_NODE;
								/* allocate the pins needed */
								allocate_more_node_input_pins(new_node, 1);
								add_input_port_information(new_node, 1);
		
								/* hookup the pin, and node */
								add_a_input_pin_to_node_spot_idx(new_node, new_pin, 0);

								/* record this node */	
								verilog_netlist->top_output_nodes = realloc(verilog_netlist->top_output_nodes, sizeof(nnode_t*)*(verilog_netlist->num_top_output_nodes+1));
								verilog_netlist->top_output_nodes[verilog_netlist->num_top_output_nodes] = new_node;
								verilog_netlist->num_top_output_nodes++;
							}
						}
						else
						{
							/* MEMORY */
							error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
									"Memory not handled ... yet!\n");
						}
					}
				}
			}
		}
	}
	else
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Empty module\n");
	}
}

/*---------------------------------------------------------------------------------------------
 * (function: define_nets_with_driver)
 * 	Given a register declaration, this function defines it as a driver.
 *-------------------------------------------------------------------------------------------*/
nnet_t* define_nets_with_driver(ast_node_t* var_declare, char *instance_name_prefix)
{
	int i;
	char *temp_string;
	long sc_spot;
	nnet_t *new_net = NULL;
			
	if (var_declare->children[1] == NULL)
	{
		/* FOR single driver signal since spots 1, 2, 3, 4 are NULL */

		/* create the net */
		new_net = allocate_nnet();

		/* make the string to add to the string cache */
		temp_string = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, -1);

		/* look for that element */
		sc_spot = sc_add_string(output_nets_sc, temp_string);
		if (output_nets_sc->data[sc_spot] != NULL)
		{
			error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
					"Net (%s) with the same name already created\n", temp_string);
		}
		/* store the data which is an idx here */
		output_nets_sc->data[sc_spot] = (void*)new_net;
		new_net->name = temp_string;
	}	
	else if (var_declare->children[3] == NULL)
	{
		ast_node_t *node_max = resolve_node(instance_name_prefix, var_declare->children[1]);
		ast_node_t *node_min = resolve_node(instance_name_prefix, var_declare->children[2]);

		/* FOR array driver  since sport 3 and 4 are NULL */
		oassert((node_max->type == NUMBERS) && (node_min->type == NUMBERS)) ;
		/* This register declaration is a range as opposed to a single bit so we need to define each element */
		/* assume digit 1 is largest */
		for (i = node_min->types.number.value; i <= node_max->types.number.value; i++)
		{
			/* create the net */
			new_net = allocate_nnet();

			/* create the string to add to the cache */
			temp_string = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, i);

			sc_spot = sc_add_string(output_nets_sc, temp_string);
			if (output_nets_sc->data[sc_spot] != NULL)
			{
				error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
						"Net (%s) with the same name already created\n", temp_string);
			}		
			/* store the data which is an idx here */
			output_nets_sc->data[sc_spot] = (void*)new_net;
			new_net->name = temp_string;
		}
	}
	else if (var_declare->children[3] != NULL)
	{
		/* FOR memory */
		temp_string = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, -1);
		error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number, 
			"2D array: %s not supported!\n", temp_string);
	}

	return new_net;
}

/*---------------------------------------------------------------------------------------------
 * (function:  define_nodes_and_nets_with_driver)
 * 	Similar to define_nets_with_driver except this one is for top level nodes and
 * 	is making the input pins into nodes and drivers.
 *-------------------------------------------------------------------------------------------*/
nnet_t* define_nodes_and_nets_with_driver(ast_node_t* var_declare, char *instance_name_prefix)
{
	int i;
	char *temp_string;
	long sc_spot;
	nnet_t *new_net = NULL;
	npin_t *new_pin;
	nnode_t *new_node;
				
	if (var_declare->children[1] == NULL)
	{
		/* FOR single driver signal since spots 1, 2, 3, 4 are NULL */

		/* create the net */
		new_net = allocate_nnet();

		temp_string = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, -1);

		sc_spot = sc_add_string(output_nets_sc, temp_string);
		if (output_nets_sc->data[sc_spot] != NULL)
		{
			error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
					"Net (%s) with the same name already created\n", temp_string);
		}
		/* store the data which is an idx here */
		output_nets_sc->data[sc_spot] = (void*)new_net;
		new_net->name = temp_string;

		/* create this node and make the pin connection to the net */
		new_pin = allocate_npin();
		new_node = allocate_nnode();
		new_node->name = temp_string;

		new_node->related_ast_node = var_declare;
		new_node->type = INPUT_NODE;
		/* allocate the pins needed */
		allocate_more_node_output_pins(new_node, 1);
		add_output_port_information(new_node, 1);

		/* hookup the pin, net, and node */
		add_a_output_pin_to_node_spot_idx(new_node, new_pin, 0);
		add_a_driver_pin_to_net(new_net, new_pin);

		/* store it in the list of input nodes */
		verilog_netlist->top_input_nodes = (nnode_t**)realloc(verilog_netlist->top_input_nodes, sizeof(nnode_t*)*(verilog_netlist->num_top_input_nodes+1));
		verilog_netlist->top_input_nodes[verilog_netlist->num_top_input_nodes] = new_node;
		verilog_netlist->num_top_input_nodes++;
	}	
	else if (var_declare->children[3] == NULL)
	{
		/* FOR array driver  since sport 3 and 4 are NULL */
		ast_node_t *node_max = resolve_node(instance_name_prefix, var_declare->children[1]);
		ast_node_t *node_min = resolve_node(instance_name_prefix, var_declare->children[2]);
		oassert((node_max->type == NUMBERS) && (node_min->type == NUMBERS)) ;
		
		/* assume digit 1 is largest */
		for (i = node_min->types.number.value; i <= node_max->types.number.value; i++)
		{
			/* create the net */
			new_net = allocate_nnet();

			/* FOR single driver signal */
			temp_string = make_full_ref_name(instance_name_prefix, NULL, NULL, var_declare->children[0]->types.identifier, i);

			sc_spot = sc_add_string(output_nets_sc, temp_string);
			if (output_nets_sc->data[sc_spot] != NULL)
			{
				error_message(NETLIST_ERROR, var_declare->children[0]->line_number, var_declare->children[0]->file_number,
						"Net (%s) with the same name already created\n", temp_string);
			}		
			/* store the data which is an idx here */
			output_nets_sc->data[sc_spot] = (void*)new_net;
			new_net->name = temp_string;

			/* create this node and make the pin connection to the net */
			new_pin = allocate_npin();
			new_node = allocate_nnode();
	
			new_node->related_ast_node = var_declare;
			new_node->name = temp_string;
			new_node->type = INPUT_NODE;
			/* allocate the pins needed */
			allocate_more_node_output_pins(new_node, 1);
			add_output_port_information(new_node, 1);
	
			/* hookup the pin, net, and node */
			add_a_output_pin_to_node_spot_idx(new_node, new_pin, 0);
			add_a_driver_pin_to_net(new_net, new_pin);
	
			/* store it in the list of input nodes */
			verilog_netlist->top_input_nodes = (nnode_t**)realloc(verilog_netlist->top_input_nodes, sizeof(nnode_t*)*(verilog_netlist->num_top_input_nodes+1));
			verilog_netlist->top_input_nodes[verilog_netlist->num_top_input_nodes] = new_node;
			verilog_netlist->num_top_input_nodes++;
		}
	}
	else if (var_declare->children[3] != NULL)
	{
		/* FOR memory */
		oassert(FALSE);
	}

	return new_net;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_symbol_table_for_module)
 * 	Creates a lookup of the variables declared here so that in the analysis we can look
 * 	up the definition of it to decide what to do.
 *-------------------------------------------------------------------------------------------*/
void create_symbol_table_for_module(ast_node_t* module_items, char *module_name)
{
	/* with the top module we need to visit the entire ast tree */
	int i, j;
	char *temp_string;
	long sc_spot;
	oassert(module_items->type == MODULE_ITEMS);

	/* search for VAR_DECLARE_LISTS */
	if (module_items->num_children > 0)
	{
		for (i = 0; i < module_items->num_children; i++)
		{
			if (module_items->children[i]->type == VAR_DECLARE_LIST)
			{
				/* go through the vars in this declare list */
				for (j = 0; j < module_items->children[i]->num_children; j++)
				{	
					ast_node_t *var_declare = module_items->children[i]->children[j];

					/* parameters are already dealt with */
					if (var_declare->types.variable.is_parameter)
						continue;

					oassert(module_items->children[i]->children[j]->type == VAR_DECLARE);
					oassert(	(var_declare->types.variable.is_input) ||
						(var_declare->types.variable.is_output) ||
						(var_declare->types.variable.is_reg) ||
						(var_declare->types.variable.is_wire));

					/* make the string to add to the string cache */
					temp_string = make_full_ref_name(NULL, NULL, NULL, var_declare->children[0]->types.identifier, -1);
					/* look for that element */
					sc_spot = sc_add_string(local_symbol_table_sc, temp_string);
					if (local_symbol_table_sc->data[sc_spot] != NULL)
					{
						/* ERROR checks here 
						 * output with reg is fine
						 * output with wire is fine 
						 * Then update the stored string chache entry with information */
						if ((var_declare->types.variable.is_input)
								&& (
									   (((ast_node_t*)local_symbol_table_sc->data[sc_spot])->types.variable.is_reg)
									|| (((ast_node_t*)local_symbol_table_sc->data[sc_spot])->types.variable.is_wire)
								)
						)
						{
							error_message(NETLIST_ERROR, var_declare->line_number, var_declare->file_number,
									"Input defined as wire or reg means it is a driver in this module.  Not possible\n");
						}
						/* MORE ERRORS ... could check for same declaration name ... */
						else if (var_declare->types.variable.is_output)
						{
							/* copy all the reg and wire info over */
							((ast_node_t*)local_symbol_table_sc->data[sc_spot])->types.variable.is_output = TRUE;
						}
						else if ((var_declare->types.variable.is_reg) || (var_declare->types.variable.is_wire))
						{
							/* copy the output status over */
							((ast_node_t*)local_symbol_table_sc->data[sc_spot])->types.variable.is_wire = var_declare->types.variable.is_wire;
							((ast_node_t*)local_symbol_table_sc->data[sc_spot])->types.variable.is_reg = var_declare->types.variable.is_reg;
						}
						else
						{
							abort();
						}
					}
					else
					{
						/* store the data which is an idx here */
						local_symbol_table_sc->data[sc_spot] = (void *)var_declare;

						/* store the symbol */		
						local_symbol_table = (ast_node_t **)realloc(local_symbol_table, sizeof(ast_node_t*)*(num_local_symbol_table+1));
						local_symbol_table[num_local_symbol_table] = (void *)var_declare;
						num_local_symbol_table ++;
					}
					free(temp_string);
				}
			}
		}
	}
	else
	{
		error_message(NETLIST_ERROR, module_items->line_number, module_items->file_number, "Empty module\n");
	}
}

#ifdef VPR6
/*--------------------------------------------------------------------------
 * (function: connect_memory_and_alias)
 * 	This function looks at the memory instantiation points and checks
 * 		if there are any inputs that don't have a driver at this level.
 *  	If they don't then name needs to be aliased for higher levels to
 *  	understand.  If there exists a driver, then we connect the two.
 *
 * 	Assume that ports are written in the same order as the instantiation.
 *-------------------------------------------------------------------------*/
void connect_memory_and_alias(ast_node_t* hb_instance, char *instance_name_prefix)
{
	t_model *hb_model;
	ast_node_t *hb_connect_list;
	int i, j;
	long sc_spot_output;
	long sc_spot_input_new, sc_spot_input_old;

	/* See if the hard block declared is supported by FPGA architecture */
	hb_model = find_hard_block(hb_instance->children[0]->types.identifier);
	if (hb_model == NULL)
	{
		printf("Found Hard Block %s: Not supported by FPGA Architecture\n", hb_instance->children[0]->types.identifier);
		oassert(FALSE);
	}

	/* Note: Hard Block port matching is checked in earlier node processing */
	hb_connect_list = hb_instance->children[1]->children[1];
	for (i = 0; i < hb_connect_list->num_children; i++)
	{
		int port_size;
		enum PORTS port_dir;
		ast_node_t *hb_var_node = hb_connect_list->children[i]->children[0];
		ast_node_t *hb_instance_var_node = hb_connect_list->children[i]->children[1];

		/* We can ignore inputs since they are already resolved */
		port_dir = hard_block_port_direction(hb_model, hb_var_node->types.identifier);
		if ((port_dir == OUT_PORT) || (port_dir == INOUT_PORT))
		{
			char *name_of_hb_input;
			char *full_name;
			char *alias_name;

			name_of_hb_input = get_name_of_pin_at_bit(hb_instance_var_node, -1, instance_name_prefix);
			full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_hb_input, -1);
			free(name_of_hb_input);
			alias_name = make_full_ref_name(instance_name_prefix,
					hb_instance->children[0]->types.identifier,
					hb_instance->children[1]->children[0]->types.identifier,
					hb_connect_list->children[i]->children[0]->types.identifier, -1);

			/* Lookup port size in cache */
			port_size = get_memory_port_size(alias_name);
			free(alias_name);
			oassert(port_size != 0);

			for (j = 0; j < port_size; j++)
			{
				/* This is an output pin from the hard block. We need to
				 * alias this output pin with it's calling name here so that
				 * everyone can see it at this level.
				 *
				 * Make the new string for the alias name */
				if (port_size > 1)
				{
					name_of_hb_input = get_name_of_pin_at_bit(hb_instance_var_node, j, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_hb_input, -1);
					free(name_of_hb_input);

					alias_name = make_full_ref_name(instance_name_prefix,
							hb_instance->children[0]->types.identifier,
							hb_instance->children[1]->children[0]->types.identifier,
							hb_connect_list->children[i]->children[0]->types.identifier, j);
				}
				else
				{
					oassert(j == 0);
					name_of_hb_input = get_name_of_pin_at_bit(hb_instance_var_node, -1, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_hb_input, -1);
					free(name_of_hb_input);

					alias_name = make_full_ref_name(instance_name_prefix,
							hb_instance->children[0]->types.identifier,
							hb_instance->children[1]->children[0]->types.identifier,
							hb_connect_list->children[i]->children[0]->types.identifier, -1);
				}

				/* Search for the old_input name */
				sc_spot_input_old = sc_lookup_string(input_nets_sc, alias_name);

				/* check if the instantiation pin exists */
				if ((sc_spot_output = sc_lookup_string(output_nets_sc, full_name)) == -1)
				{
					/* IF - no driver, then assume that it needs to be 
					   aliased to move up as an input */
					if ((sc_spot_input_new = sc_lookup_string(input_nets_sc, full_name)) == -1)
					{
						/* if this input is not yet used in this module
						   then we'll add it */
						sc_spot_input_new = sc_add_string(input_nets_sc, full_name);
						/* copy the pin to the old spot */
						input_nets_sc->data[sc_spot_input_new] = input_nets_sc->data[sc_spot_input_old];
					}
					else
					{
						/* already exists so we'll join the nets */
						combine_nets((nnet_t*)input_nets_sc->data[sc_spot_input_old], (nnet_t*)input_nets_sc->data[sc_spot_input_new], verilog_netlist);
					}
				}
				else
				{
					/* ELSE - we've found a matching net, 
					   so add this pin to the net */
					nnet_t* net = (nnet_t*)output_nets_sc->data[sc_spot_output];
					nnet_t* in_net = (nnet_t*)input_nets_sc->data[sc_spot_input_old];

					/* if they haven't been combined already,
					   then join the inputs and output */
					in_net->name = net->name;
					combine_nets(net, in_net, verilog_netlist);

					/* since the driver net is deleted,
					   copy the spot of the in_net over */
					input_nets_sc->data[sc_spot_input_old] = (void*)in_net;
					output_nets_sc->data[sc_spot_output] = (void*)in_net;

					/* if this input is not yet used in this module
					   then we'll add it */
					sc_spot_input_new = sc_add_string(input_nets_sc, full_name);
					/* copy the pin to the old spot */
					input_nets_sc->data[sc_spot_input_new] = (void *)in_net;
				}

				free(full_name);
				free(alias_name);
			}
		}
	}

	return;
}

/*--------------------------------------------------------------------------
 * (function: connect_hard_block_and_alias)
 * 	This function looks at the hard block instantiation points and checks
 * 		if there are any inputs that don't have a driver at this level.
 *  	If they don't then name needs to be aliased for higher levels to
 *  	understand.  If there exists a driver, then we connect the two.
 *
 * 	Assume that ports are written in the same order as the instantiation.
 * 	Also, we will assume that the portwidths have to match
 *-------------------------------------------------------------------------*/
void connect_hard_block_and_alias(ast_node_t* hb_instance, char *instance_name_prefix)
{
	t_model *hb_model;
	ast_node_t *hb_connect_list;
	int i, j;
	long sc_spot_output;
	long sc_spot_input_new, sc_spot_input_old;

	/* See if the hard block declared is supported by FPGA architecture */
	hb_model = find_hard_block(hb_instance->children[0]->types.identifier);
	if (hb_model == NULL)
	{
		printf("Found Hard Block %s: Not supported by FPGA Architecture\n", hb_instance->children[0]->types.identifier);
		oassert(FALSE);
	}

	/* Note: Hard Block port matching is checked in earlier node processing */
	hb_connect_list = hb_instance->children[1]->children[1];
	for (i = 0; i < hb_connect_list->num_children; i++)
	{
		int port_size;
		enum PORTS port_dir;
		ast_node_t *hb_var_node = hb_connect_list->children[i]->children[0];
		ast_node_t *hb_instance_var_node = hb_connect_list->children[i]->children[1];

		/* We can ignore inputs since they are already resolved */
		port_dir = hard_block_port_direction(hb_model, hb_var_node->types.identifier);
		if ((port_dir == OUT_PORT) || (port_dir == INOUT_PORT))
		{
			port_size = hard_block_port_size(hb_model, hb_var_node->types.identifier);
			oassert(port_size != 0);

			for (j = 0; j < port_size; j++)
			{
				/* This is an output pin from the hard block. We need to
				 * alias this output pin with it's calling name here so that
				 * everyone can see it at this level
				 */
				char *name_of_hb_input;
				char *full_name;
				char *alias_name;

				/* make the new string for the alias name */
				if (port_size > 1)
				{
					name_of_hb_input = get_name_of_pin_at_bit(hb_instance_var_node, j, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_hb_input, -1);
					free(name_of_hb_input);

					alias_name = make_full_ref_name(instance_name_prefix,
							hb_instance->children[0]->types.identifier,
							hb_instance->children[1]->children[0]->types.identifier,
							hb_connect_list->children[i]->children[0]->types.identifier, j);
				}
				else
				{
					oassert(j == 0);
					name_of_hb_input = get_name_of_pin_at_bit(hb_instance_var_node, -1, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_hb_input, -1);
					free(name_of_hb_input);

					alias_name = make_full_ref_name(instance_name_prefix,
							hb_instance->children[0]->types.identifier,
							hb_instance->children[1]->children[0]->types.identifier,
							hb_connect_list->children[i]->children[0]->types.identifier, -1);
				}

				/* Search for the old_input name */
				sc_spot_input_old = sc_lookup_string(input_nets_sc, alias_name);

				/* check if the instantiation pin exists */
				if ((sc_spot_output = sc_lookup_string(output_nets_sc, full_name)) == -1)
				{
					/* IF - no driver, then assume that it needs to be 
					   aliased to move up as an input */
					if ((sc_spot_input_new = sc_lookup_string(input_nets_sc, full_name)) == -1)
					{
						/* if this input is not yet used in this module
						   then we'll add it */
						sc_spot_input_new = sc_add_string(input_nets_sc, full_name);
						/* copy the pin to the old spot */
						input_nets_sc->data[sc_spot_input_new] = input_nets_sc->data[sc_spot_input_old];
					}
					else
					{
						/* already exists so we'll join the nets */
						combine_nets((nnet_t*)input_nets_sc->data[sc_spot_input_old], (nnet_t*)input_nets_sc->data[sc_spot_input_new], verilog_netlist);
					}
				}
				else
				{
					/* ELSE - we've found a matching net, 
					   so add this pin to the net */
					nnet_t* net = (nnet_t*)output_nets_sc->data[sc_spot_output];
					nnet_t* in_net = (nnet_t*)input_nets_sc->data[sc_spot_input_old];


					/* if they haven't been combined already,
						then join the inputs and output */
					in_net->name = net->name;
					combine_nets(net, in_net, verilog_netlist);
                                        
					/* since the driver net is deleted,
						copy the spot of the in_net over */
					input_nets_sc->data[sc_spot_input_old] = (void*)in_net;
					output_nets_sc->data[sc_spot_output] = (void*)in_net;

					/* if this input is not yet used in this module
						then we'll add it */
					sc_spot_input_new = sc_add_string(input_nets_sc, full_name);
					/* copy the pin to the old spot */
					input_nets_sc->data[sc_spot_input_new] = (void *)in_net;
				}

				free(full_name);
				free(alias_name);
			}
		}
	}

	return;
}
#endif

/*--------------------------------------------------------------------------
 * (function: connect_module_instantiation_and_alias)
 * 	This function looks at module instantiation points and does one of two things:
 * 		On the first pass this function looks at an instantiation (which has already
 * 		been processed) and checks if there are drivers in there that need to be seen
 * 		as we process the instantiating module.  
 *
 * 		On the second pass this function looks at an instantiation and checks if
 * 		there are any inputs that don't have a driver at this level.  If they don't then
 * 		name needs to be aliased for higher levels to understand.  If there exists a 
 * 		driver, then we connect the two.
 *
 * 	Assume that ports are written in the same order as the instantiation.  Also,
 * 	we will assume that the portwidths have to match
 *-------------------------------------------------------------------------*/
void connect_module_instantiation_and_alias(short PASS, ast_node_t* module_instance, char *instance_name_prefix)
{
	int i, j;
	ast_node_t *module_node;
	ast_node_t *module_list;
	ast_node_t *module_instance_list = module_instance->children[1]->children[1]; // MODULE_INSTANCE->MODULE_INSTANCE_NAME(child[1])->MODULE_CONNECT_LIST(child[1])
	long sc_spot;
	long sc_spot_output;
	long sc_spot_input_old;
	long sc_spot_input_new;

	char *module_instance_name = module_instance->children[0]->types.identifier;

	/* lookup the node of the module associated with this instantiated module */
	if ((sc_spot = sc_lookup_string(module_names_to_idx, module_instance_name)) == -1)
	{
		error_message(NETLIST_ERROR, module_instance->line_number, module_instance->file_number,
				"Can't find module %s\n", module_instance_name);
	}
	
	if (module_instance_name != module_instance->children[0]->types.identifier)
		free(module_instance_name);

	module_node = (ast_node_t*)module_names_to_idx->data[sc_spot];
	module_list = module_node->children[1]; // MODULE->VAR_DECLARE_LIST(child[1])

	if (module_list->num_children != module_instance_list->num_children)
	{
		error_message(NETLIST_ERROR, module_instance->line_number, module_instance->file_number,
				"Module instantiation (%s) and definition don't match in terms of ports\n",
				module_instance->children[0]->types.identifier);
	}

	for (i = 0; i < module_list->num_children; i++)
	{
		int port_size = 0;
		// VAR_DECLARE_LIST(child[i])->VAR_DECLARE_PORT(child[0])->VAR_DECLARE_input-or-output(child[0])
		ast_node_t *module_var_node = module_list->children[i]->children[0];
		// MODULE_CONNECT_LIST(child[i])->MODULE_CONNECT(child[1]) // child[0] is for aliasing
		ast_node_t *module_instance_var_node = module_instance_list->children[i]->children[1];

		if ( 
			   // skip inputs on pass 1
			   ((PASS == INSTANTIATE_DRIVERS) && (module_list->children[i]->children[0]->types.variable.is_input))
			   // skip outputs on pass 2
			|| ((PASS == ALIAS_INPUTS) && (module_list->children[i]->children[0]->types.variable.is_output))
		)
		{
			continue;
		}

		/* calculate the port details */
		if (module_var_node->children[1] == NULL)
		{
			port_size = 1;
		}
		else if (module_var_node->children[3] == NULL)
		{
			char *module_name = make_full_ref_name(instance_name_prefix, 
				// module_name
				module_instance->children[0]->types.identifier, 
				// instance name
				module_instance->children[1]->children[0]->types.identifier, 
				NULL, -1);
			ast_node_t *node1 = resolve_node(module_name, module_var_node->children[1]);
			ast_node_t *node2 = resolve_node(module_name, module_var_node->children[2]);
			free(module_name);
			oassert(node2->type == NUMBERS && node1->type == NUMBERS);
			/* assume all arrays declared [largest:smallest] */
			oassert(node2->types.number.value <= node1->types.number.value); 
			port_size = node1->types.number.value - node2->types.number.value + 1;
		}
		else if (module_var_node->children[3] != NULL)
		{
			/* MEMORY output */
			oassert(FALSE);
		}
		
		for (j = 0; j < port_size; j++)
		{
			if (module_list->children[i]->children[0]->types.variable.is_input)
			{
				/* IF - this spot in the module list is an input, then we need to find it in the
				 * string cache (as its old name), check if the new_name (the instantiation name)
 				 * is already a driver at this level.  IF it is a driver then we can hook the two up.
 				 * IF it's not we need to alias the pin name as it is used here since it
 				 * must be driven at a higher level of hierarchy in the tree of modules */
				char *name_of_module_instance_of_input;
				char *full_name;
				char *alias_name;
				
				if (port_size > 1)
				{		
					/* Get the name of the module instantiation pin */
					name_of_module_instance_of_input = get_name_of_pin_at_bit(module_instance_var_node, j, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_module_instance_of_input, -1); 
					free(name_of_module_instance_of_input);

					/* make the new string for the alias name - has to be a identifier in the instantiated modules old names */
					name_of_module_instance_of_input = get_name_of_var_declare_at_bit(module_list->children[i]->children[0], j);
					alias_name = make_full_ref_name(instance_name_prefix,
							module_instance->children[0]->types.identifier,
							module_instance->children[1]->children[0]->types.identifier,
							name_of_module_instance_of_input, -1);

					free(name_of_module_instance_of_input);
				}
				else
				{
					oassert(j == 0);

					/* Get the name of the module instantiation pin */
					name_of_module_instance_of_input = get_name_of_pin_at_bit(module_instance_var_node, -1, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_module_instance_of_input, -1); 
					free(name_of_module_instance_of_input);

					name_of_module_instance_of_input = get_name_of_var_declare_at_bit(module_list->children[i]->children[0], 0);
					alias_name = make_full_ref_name(instance_name_prefix,
							module_instance->children[0]->types.identifier,
							module_instance->children[1]->children[0]->types.identifier,
							name_of_module_instance_of_input, -1);

					free(name_of_module_instance_of_input);
				}

				/* search for the old_input name */
				if ((sc_spot_input_old = sc_lookup_string(input_nets_sc, alias_name)) == -1)
                {
					/* doesn it have to exist since might only be used in module */
					error_message(NETLIST_ERROR, module_instance->line_number, module_instance->file_number,
							"This module port %s is unused in module %s", alias_name, module_node->children[0]->types.identifier);
				}

				/* check if the instantiation pin exists. */
				if ((sc_spot_output = sc_lookup_string(output_nets_sc, full_name)) == -1)
				{
					/* IF - no driver, then assume that it needs to be aliased to move up as an input */
					if ((sc_spot_input_new = sc_lookup_string(input_nets_sc, full_name)) == -1)
					{
						/* if this input is not yet used in this module then we'll add it */
						sc_spot_input_new = sc_add_string(input_nets_sc, full_name);
						
						/* copy the pin to the old spot */
						input_nets_sc->data[sc_spot_input_new] = input_nets_sc->data[sc_spot_input_old];
					}
					else
					{
						/* already exists so we'll join the nets */
						combine_nets((nnet_t*)input_nets_sc->data[sc_spot_input_old], (nnet_t*)input_nets_sc->data[sc_spot_input_new], verilog_netlist);
					}
				}
				else
				{
					/* ELSE - we've found a matching net, so add this pin to the net */
					nnet_t* net = (nnet_t*)output_nets_sc->data[sc_spot_output];
					nnet_t* in_net = (nnet_t*)input_nets_sc->data[sc_spot_input_old];

					if ((net != in_net) && (net->combined == TRUE))
					{
						/* if they haven't been combined already, then join the inputs and output */
						join_nets(net, in_net);
						/* since the driver net is deleted, copy the spot of the in_net over */
						input_nets_sc->data[sc_spot_input_old] = (void*)net;
					}
					else if ((net != in_net) && (net->combined == FALSE))
					{
						/* if they haven't been combined already, then join the inputs and output */
						combine_nets(net, in_net, verilog_netlist);
						/* since the driver net is deleted, copy the spot of the in_net over */
						output_nets_sc->data[sc_spot_output] = (void*)in_net;
					}
				}

				/* IF the designer uses port names then make sure they line up */
				if (module_instance_list->children[i]->children[0] != NULL)
				{
					if (strcmp(module_instance_list->children[i]->children[0]->types.identifier,
							module_list->children[i]->children[0]->children[0]->types.identifier) != 0
					)
					{
						error_message(NETLIST_ERROR, module_list->children[i]->children[0]->line_number, module_list->children[i]->children[0]->file_number,
								"This module entry does not match up correctly (%s != %s).  Odin expects the order of ports to be the same\n",
								module_instance_list->children[i]->children[0]->types.identifier,
								module_list->children[i]->children[0]->children[0]->types.identifier
						);
					}
				}

				free(full_name);
				free(alias_name);
			}
			else if (module_list->children[i]->children[0]->types.variable.is_output)
			{
				/* ELSE IF - this is an output pin from the module.  We need to alias this output
				 * pin with it's calling name here so that everyone can see it at this level */
				char *name_of_module_instance_of_input;
				char *full_name;
				char *alias_name;
				
				/* make the new string for the alias name - has to be a identifier in the
				 * instantiated modules old names */
				if (port_size > 1)
				{		
					/* Get the name of the module instantiation pin */
					name_of_module_instance_of_input = get_name_of_pin_at_bit(module_instance_var_node, j, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_module_instance_of_input, -1); 
					free(name_of_module_instance_of_input);

					name_of_module_instance_of_input = get_name_of_var_declare_at_bit(module_list->children[i]->children[0], j);
					alias_name = make_full_ref_name(instance_name_prefix,
							module_instance->children[0]->types.identifier,
							module_instance->children[1]->children[0]->types.identifier, name_of_module_instance_of_input, -1);
					free(name_of_module_instance_of_input);
				}
				else
				{
					oassert(j == 0);
					/* Get the name of the module instantiation pin */
					name_of_module_instance_of_input = get_name_of_pin_at_bit(module_instance_var_node, -1, instance_name_prefix);
					full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_module_instance_of_input, -1); 
					free(name_of_module_instance_of_input);

					name_of_module_instance_of_input = get_name_of_var_declare_at_bit(module_list->children[i]->children[0], 0);
					alias_name = make_full_ref_name(instance_name_prefix,
							module_instance->children[0]->types.identifier,
							module_instance->children[1]->children[0]->types.identifier, name_of_module_instance_of_input, -1);
					free(name_of_module_instance_of_input);
				}

				/* check if the instantiation pin exists. */
				if ((sc_spot_output = sc_lookup_string(output_nets_sc, alias_name)) == -1)
				{
					error_message(NETLIST_ERROR, module_list->children[i]->children[0]->line_number, module_list->children[i]->children[0]->file_number,
							"This output (%s) must exist...must be an error\n", alias_name);
				}
				
				/* can already be there */
				sc_spot_input_new = sc_add_string(output_nets_sc, full_name);

				/* add this alias for the net */
				output_nets_sc->data[sc_spot_input_new] = output_nets_sc->data[sc_spot_output];

				/* IF the designer users port names then make sure they line up */
				if (module_instance_list->children[i]->children[0] != NULL)
				{
					if (strcmp(module_instance_list->children[i]->children[0]->types.identifier, module_list->children[i]->children[0]->children[0]->types.identifier) != 0)
					{
						error_message(NETLIST_ERROR, module_list->children[i]->children[0]->line_number, module_list->children[i]->children[0]->file_number,
								"This module entry does not match up correctly (%s != %s).  Odin expects the order of ports to be the same\n",
								module_instance_list->children[i]->children[0]->types.identifier,
								module_list->children[i]->children[0]->children[0]->types.identifier
						);
					}
				}

				free(full_name);
				free(alias_name);
			}
		}	
	}
}

/*---------------------------------------------------------------------------------------------
 * (function: create_pins)
 * 	Create pin creates the pins representing this naming isntance, adds them to the input
 * 	nets list (if not already there), checks if a driver already exists (and hooks input
 * 	to output if needed), and adds the pin to the list.
 * 	Note: only for input paths...
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_pins(ast_node_t* var_declare, char *name, char *instance_name_prefix)
{
	int i;
	signal_list_t *return_sig_list = init_signal_list_structure();
	long sc_spot;
	long sc_spot_output;
	npin_t *new_pin;
	nnet_t *new_in_net;
	char_list_t *pin_lists = NULL;

	if (name == NULL)
	{
		/* get all the pins */
		pin_lists = get_name_of_pins_with_prefix(var_declare, instance_name_prefix);
	}
	else if (var_declare == NULL)
	{
		/* if you have the name and just want a pin then use this method */
		pin_lists = (char_list_t*)malloc(sizeof(char_list_t)*1);
		pin_lists->strings = (char**)malloc(sizeof(char*));
		pin_lists->strings[0] = name;
		pin_lists->num_strings = 1;
	}
	else
	{
		error_message(0,0,-1,"Invalid state or internal error");
	}


	for (i = 0; i < pin_lists->num_strings; i++)
	{
		new_pin = allocate_npin();
		new_pin->name = pin_lists->strings[i];

		/* check if the instantiation pin exists. */
		if (strstr(pin_lists->strings[i], "ONE_VCC_CNS") != NULL)
		{
			add_a_fanout_pin_to_net(verilog_netlist->one_net, new_pin);
			sc_spot = sc_add_string(input_nets_sc, pin_lists->strings[i]);
			input_nets_sc->data[sc_spot] = (void*)verilog_netlist->one_net;
		}
		else if (strstr(pin_lists->strings[i], "ZERO_GND_ZERO") != NULL)
		{
			add_a_fanout_pin_to_net(verilog_netlist->zero_net, new_pin);
			sc_spot = sc_add_string(input_nets_sc, pin_lists->strings[i]);
			input_nets_sc->data[sc_spot] = (void*)verilog_netlist->zero_net;
		}
		else
		{
			/* search for the input name  if already exists...needs to be added to
			 * string cache in case it's an input pin */
			if ((sc_spot = sc_lookup_string(input_nets_sc, pin_lists->strings[i])) == -1)
			{	
				new_in_net = allocate_nnet();
	
				sc_spot = sc_add_string(input_nets_sc, pin_lists->strings[i]);
				input_nets_sc->data[sc_spot] = (void*)new_in_net;
			}
	
			/* store the pin in this net */
			add_a_fanout_pin_to_net((nnet_t*)input_nets_sc->data[sc_spot], new_pin);

			if ((sc_spot_output = sc_lookup_string(output_nets_sc, pin_lists->strings[i])) != -1)
			{
				/* ELSE - we've found a matching net, so add this pin to the net */
				nnet_t* net = (nnet_t*)output_nets_sc->data[sc_spot_output];

				if ((net != (nnet_t*)input_nets_sc->data[sc_spot]) && net->combined )
				{
					/* IF - the input and output nets don't match, then they need to be joined */
					join_nets(net, (nnet_t*)input_nets_sc->data[sc_spot]);
					/* since the driver net is deleted, copy the spot of the in_net over */
					input_nets_sc->data[sc_spot] = (void*)net;
				}
				else if ((net != (nnet_t*)input_nets_sc->data[sc_spot]) && !net->combined)
				{
					/* IF - the input and output nets don't match, then they need to be joined */

					combine_nets(net, (nnet_t*)input_nets_sc->data[sc_spot], verilog_netlist);
					/* since the driver net is deleted, copy the spot of the in_net over */
					output_nets_sc->data[sc_spot_output] = (void*)input_nets_sc->data[sc_spot];
				}
			}
		}

		/* add the pin now stored in the string chache to the returned signal list */		
		add_pin_to_signal_list(return_sig_list, new_pin);
	}
	
	return return_sig_list; 
}

/*---------------------------------------------------------------------------------------------
 * (function: create_output_pin)
 * 	Create OUTPUT pin creates a pin representing this naming isntance, adds it to the input
 * 	nets list (if not already there) and adds the pin to the list.
 * 	Note: only for output drivers...
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_output_pin(ast_node_t* var_declare, char *instance_name_prefix)
{
	char *name_of_pin;
	char *full_name;
	signal_list_t *return_sig_list = init_signal_list_structure();
	npin_t *new_pin;
	
	/* get the name of the pin */
	name_of_pin = get_name_of_pin_at_bit(var_declare, -1, instance_name_prefix);
	full_name = make_full_ref_name(instance_name_prefix, NULL, NULL, name_of_pin, -1); 
	free(name_of_pin);

	new_pin = allocate_npin();
	new_pin->name = full_name;

	add_pin_to_signal_list(return_sig_list, new_pin);

	return return_sig_list; 
}

/*---------------------------------------------------------------------------------------------
 * (function: assignment_alias)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *assignment_alias(ast_node_t* assignment, char *instance_name_prefix)
{
	signal_list_t *in_1;
	signal_list_t *return_list;
	char_list_t *out_list;
	int i;
	int output_size;

	/* process the signal for the input gate */
	in_1 = netlist_expand_ast_of_module(assignment->children[1], instance_name_prefix);
	oassert(in_1 != NULL);
	out_list = get_name_of_pins_with_prefix(assignment->children[0], instance_name_prefix); 
	oassert(out_list != NULL);
	oassert(out_list->strings != NULL);

	/* aliases the input pin names to the output names */
	output_size = alias_output_assign_pins_to_inputs(out_list, in_1, assignment);

	if (output_size < in_1->signal_list_size)
	{
		return_list = init_signal_list_structure();
		/* need to shrink the output list */
		for (i = 0; i < output_size; i++)
		{
			add_pin_to_signal_list(return_list, in_1->signal_list[i]);
		}
		
		clean_signal_list_structure(in_1);
	}
	else
	{
		return_list = in_1;
	}

	/* clean the name string list since we don't need it anymore */
	free(out_list->strings);
	free(out_list);
	
	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: terminate_registered_assignment)
 *-------------------------------------------------------------------------------------------*/
void terminate_registered_assignment(ast_node_t *always_node, signal_list_t* assignment, signal_list_t *potential_clocks, char *instance_name_prefix)
{
	int i;
	long sc_spot;
	npin_t *ff_output_pin;

	oassert(potential_clocks != NULL);

	/* figure out which one is the clock */
	if (local_clock_found == FALSE)
	{
		for (i = 0; i < potential_clocks->signal_list_size; i++)
		{
			nnet_t *temp_net;
			/* searching for the clock with no net */
			if ((sc_spot = sc_lookup_string(output_nets_sc, potential_clocks->signal_list[i]->name)) == -1)
			{
				if ((sc_spot = sc_lookup_string(input_nets_sc, potential_clocks->signal_list[i]->name)) == -1)
				{
					error_message(NETLIST_ERROR, always_node->line_number, always_node->file_number,
							"Sensitivity list element (%s) is not a driver or net ... must be\n", potential_clocks->signal_list[i]->name);
				}
				temp_net = (nnet_t*)input_nets_sc->data[sc_spot];
			}
			else
			{
				temp_net = (nnet_t*)output_nets_sc->data[sc_spot];
			}
	
			
			if (
				(((temp_net->num_fanout_pins == 1) && (temp_net->fanout_pins[0]->node == NULL)) || (temp_net->num_fanout_pins == 0))
				&& (local_clock_found == TRUE))
			{
				error_message(NETLIST_ERROR, always_node->line_number, always_node->file_number,
						"Suspected second clock (%s).  In a sequential sensitivity list, Odin expects the "
						"clock not to drive anything and any other signals in this list to drive stuff.  "
						"For example, a reset in the sensitivy list has to be hooked up to something in the always block.\n",
						potential_clocks->signal_list[i]->name);
			}
			else if (temp_net->num_fanout_pins == 0)
			{
				/* If this element is in the sensitivity list and doesn't drive anything it's the clock */
				local_clock_found = TRUE;
				local_clock_idx = i;
			}
			else if ((temp_net->num_fanout_pins == 1) && (temp_net->fanout_pins[0]->node == NULL))
			{
				/* If this element is in the sensitivity list and doesn't drive anything it's the clock */
				local_clock_found = TRUE;
				local_clock_idx = i;
			}

		}
	}

	/* in continuous assign we can hook up the inputs to the driving side of the nets */	
	for (i = 0; i < assignment->signal_list_size; i++)
	{
		nnode_t *ff_node = allocate_nnode();
		/* look up the net */
		if ((sc_spot = sc_lookup_string(output_nets_sc, assignment->signal_list[i]->name)) == -1)
		{
			error_message(NETLIST_ERROR, always_node->line_number, always_node->file_number,
					"Assignment is missing driver (%s)\n", assignment->signal_list[i]->name);
		}

		/* HERE create the ff node and hookup everything */
		ff_node->related_ast_node = always_node;

		ff_node->type = FF_NODE;
		/* create the unique name for this gate */
		ff_node->name = node_name(ff_node, instance_name_prefix);
		/* allocate the pins needed */
		allocate_more_node_input_pins(ff_node, 2);
		add_input_port_information(ff_node, 1);
		allocate_more_node_output_pins(ff_node, 1);
		add_output_port_information(ff_node, 1);
		
		/* add the clock to the flip_flop */
		/* add a fanout pin */
		npin_t *fanout_pin_of_clock = allocate_npin();
		add_a_fanout_pin_to_net(potential_clocks->signal_list[local_clock_idx]->net, fanout_pin_of_clock);
		add_a_input_pin_to_node_spot_idx(ff_node, fanout_pin_of_clock, 1);

		/* hookup the driver pin (the in_1) to to this net (the lookup) */
		add_a_input_pin_to_node_spot_idx(ff_node, assignment->signal_list[i], 0);

		/* finally hookup the output pin of the flip flop to the orginal driver net */
		ff_output_pin = allocate_npin();
		add_a_output_pin_to_node_spot_idx(ff_node, ff_output_pin, 0);

		if(((nnet_t*)output_nets_sc->data[sc_spot])->driver_pin)
		{
			error_message(NETLIST_ERROR, always_node->line_number, always_node->file_number,
					"You've defined the driver \"%s\" twice\n", get_pin_name(assignment->signal_list[i]->name));
		}
		add_a_driver_pin_to_net((nnet_t*)output_nets_sc->data[sc_spot], ff_output_pin);

		verilog_netlist->ff_nodes = (nnode_t**)realloc(verilog_netlist->ff_nodes, sizeof(nnode_t*)*(verilog_netlist->num_ff_nodes+1));
		verilog_netlist->ff_nodes[verilog_netlist->num_ff_nodes] = ff_node;
		verilog_netlist->num_ff_nodes++;
	}

	clean_signal_list_structure(assignment);
}

/*---------------------------------------------------------------------------------------------
 * (function: terminate_continuous_assignment)
 *-------------------------------------------------------------------------------------------*/
void terminate_continuous_assignment(ast_node_t *node, signal_list_t* assignment, char *instance_name_prefix)
{
	int i;
	long sc_spot;
	npin_t *buf_input_pin;
	npin_t *buf_output_pin;

	for (i = 0; i < assignment->signal_list_size; i++)
	{
		nnode_t *buf_node;


		/* look up the net */
		if ((sc_spot = sc_lookup_string(output_nets_sc, assignment->signal_list[i]->name)) == -1)
		{
			error_message(NETLIST_ERROR, node->line_number, node->file_number,
					"Assignment (%s) is missing driver\n", assignment->signal_list[i]->name);
		}

		/* check if the instantiation pin exists. */
		if (((nnet_t*)output_nets_sc->data[sc_spot])->name == NULL)
		{
			((nnet_t*)output_nets_sc->data[sc_spot])->name = assignment->signal_list[i]->name;
		}

		buf_node = allocate_nnode();
		buf_node->type = BUF_NODE;
		/* create the unique name for this gate */
		buf_node->name = node_name(buf_node, instance_name_prefix);

		buf_node->related_ast_node = node;
		/* allocate the pins needed */
		allocate_more_node_input_pins(buf_node, 1);
		add_input_port_information(buf_node, 1);
		allocate_more_node_output_pins(buf_node, 1);
		add_output_port_information(buf_node, 1);
		
		/* hookup the driver pin (the in_1) to this net (the lookup) */
		buf_input_pin = assignment->signal_list[i];
		add_a_input_pin_to_node_spot_idx(buf_node, buf_input_pin, 0);

		/* finally hookup the output pin of the flip flop to the orginal driver net */
		/* finally hookup the output pin of the buffer to the orginal driver net */
		buf_output_pin = allocate_npin();
		add_a_output_pin_to_node_spot_idx(buf_node, buf_output_pin, 0);
		if(((nnet_t*)output_nets_sc->data[sc_spot])->driver_pin != NULL)
		{
			error_message(NETLIST_ERROR, node->line_number, node->file_number,
					"You've defined this driver %s twice (i.e. in the statement block you've probably put the statement as a = b; a = c; in some form that's incorrect).  "
					"Note that Odin II does not currently support combinational a = ? overiding for if and case blocks.\n", assignment->signal_list[i]->name);
		}
		add_a_driver_pin_to_net((nnet_t*)output_nets_sc->data[sc_spot], buf_output_pin);
	}

	clean_signal_list_structure(assignment);
}

/*---------------------------------------------------------------------------------------------
 * (function: alias_output_assign_pins_to_inputs)
 * 	Makes the names of the pins in the input list have the name of the output assignment
 *-------------------------------------------------------------------------------------------*/
int alias_output_assign_pins_to_inputs(char_list_t *output_list, signal_list_t *input_list, ast_node_t *node)
{
	int i;

	if (output_list->num_strings >= input_list->signal_list_size)
	{
		for (i = 0; i < input_list->signal_list_size; i++)
		{
			input_list->signal_list[i]->name = output_list->strings[i];
		}
		for (i = input_list->signal_list_size; i < output_list->num_strings; i++)
		{
			if (global_args.all_warnings)
				warning_message(NETLIST_ERROR, node->line_number, node->file_number,
						"More nets to drive than drivers, padding with ZEROs for driver %s\n", output_list->strings[i]);

			add_pin_to_signal_list(input_list, get_a_zero_pin(verilog_netlist));
			input_list->signal_list[i]->name = output_list->strings[i];
		}

		return output_list->num_strings;
	}
	else
	{
		for (i = 0; i < output_list->num_strings; i++)
		{
			input_list->signal_list[i]->name = output_list->strings[i];
		}

		if (global_args.all_warnings)
			warning_message(NETLIST_ERROR, node->line_number, node->file_number,
					"More driver pins than nets to drive: sometimes using decimal numbers causes this problem\n");
		return output_list->num_strings;
	}
}

/*--------------------------------------------------------------------------
 * (function: create_gate)
 * 	This function creates a gate node in the netlist and hooks up the inputs
 * 	and outputs.
 *------------------------------------------------------------------------*/
signal_list_t *create_gate(ast_node_t* gate, char *instance_name_prefix)
{
	signal_list_t *in_1, *in_2, *out_1;
	nnode_t *gate_node;
	ast_node_t *gate_instance = gate->children[0];

	if (gate_instance->children[3] == NULL)
	{
		/* IF one input gate */
		
		/* process the signal for the input gate */
		in_1 = netlist_expand_ast_of_module(gate_instance->children[2], instance_name_prefix);
		/* process the signal for the input ga$te */
		out_1 = create_output_pin(gate_instance->children[1], instance_name_prefix);
		oassert((in_1 != NULL) && (out_1 != NULL));

		/* create the node */
		gate_node = allocate_nnode();
		/* store all the relevant info */
		gate_node->related_ast_node = gate;
		gate_node->type = gate->types.operation.op;
		oassert(gate_node->type > 0);
		gate_node->name = node_name(gate_node, instance_name_prefix);
		/* allocate the pins needed */
		allocate_more_node_input_pins(gate_node, 1);
		add_input_port_information(gate_node, 1);
		allocate_more_node_output_pins(gate_node, 1);
		add_output_port_information(gate_node, 1);
		
		/* hookup the input pins */
		hookup_input_pins_from_signal_list(gate_node, 0, in_1, 0, 1, verilog_netlist);
		/* hookup the output pins */
		hookup_output_pins_from_signal_list(gate_node, 0, out_1, 0, 1);

		clean_signal_list_structure(in_1);
	}
	else
	{
		/* ELSE 2 input gate */
		
		/* process the signal for the input gate */
		in_1 = netlist_expand_ast_of_module(gate_instance->children[2], instance_name_prefix);
		in_2 = netlist_expand_ast_of_module(gate_instance->children[3], instance_name_prefix);
		/* process the signal for the input gate */
		out_1 = create_output_pin(gate_instance->children[1], instance_name_prefix);
		oassert((in_1 != NULL) && (in_2 != NULL) && (out_1 != NULL));

		/* create the node */
		gate_node = allocate_nnode();
		/* store all the relevant info */
		gate_node->related_ast_node = gate;
		gate_node->type = gate->types.operation.op;
		oassert(gate_node->type > 0);

		gate_node->name = node_name(gate_node, instance_name_prefix);
		/* allocate the needed pins */
		allocate_more_node_input_pins(gate_node, 2);
		add_input_port_information(gate_node, 1);
		add_input_port_information(gate_node, 1);
		allocate_more_node_output_pins(gate_node, 1);
		add_output_port_information(gate_node, 1);
		
		/* hookup the input pins */
		hookup_input_pins_from_signal_list(gate_node, 0, in_1, 0, 1, verilog_netlist);
		hookup_input_pins_from_signal_list(gate_node, 1, in_2, 0, 1, verilog_netlist);
		/* hookup the output pins */
		hookup_output_pins_from_signal_list(gate_node, 0, out_1, 0, 1);

		clean_signal_list_structure(in_1);
		clean_signal_list_structure(in_2);
	}
	
	return out_1;
}



/*----------------------------------------------------------------------------
 * (function: create_operation_node)
 *--------------------------------------------------------------------------*/
signal_list_t *create_operation_node(ast_node_t *op, signal_list_t **input_lists, int list_size, char *instance_name_prefix)
{
	int i;
	signal_list_t *return_list = init_signal_list_structure();
	nnode_t *operation_node;
	int max_input_port_width = -1;
	int output_port_width = -1;
	int input_port_width = -1;
	int current_idx;

	/* create the node */
	operation_node = allocate_nnode();
	/* store all the relevant info */
	operation_node->related_ast_node = op;
	operation_node->type = op->types.operation.op;
	operation_node->name = node_name(operation_node, instance_name_prefix);

	current_idx = 0;

	/* analyse the inputs */
	for (i = 0; i < list_size; i++)
	{
		if (max_input_port_width < input_lists[i]->signal_list_size)
		{
			max_input_port_width = input_lists[i]->signal_list_size;
		}
	}
		
	switch(operation_node->type)
	{
		case BITWISE_NOT: // ~	
			/* only one input port */
			output_port_width = max_input_port_width;
			input_port_width = output_port_width;
			break;
		case ADD: // +
			/* add the largest bit width + the other input padded with 0's */
			return_list->is_adder = TRUE;
			output_port_width = max_input_port_width + 1;
			input_port_width = max_input_port_width;
			break;
		case MINUS: // -
			/* subtract the largest bit width + the other input padded with 0's ... concern for 2's comp */
			output_port_width = max_input_port_width;
			input_port_width = output_port_width;
			break;
		case MULTIPLY: // *
			/* pad the smaller one with 0's */
			output_port_width = input_lists[0]->signal_list_size + input_lists[1]->signal_list_size;
			input_port_width = -2;

			/* Record multiply nodes for netlist optimization */
			mult_list = insert_in_vptr_list(mult_list, operation_node);
			break;
		case BITWISE_AND: // &
		case BITWISE_OR: // |
		case BITWISE_NAND: // ~&
		case BITWISE_NOR: // ~| 
		case BITWISE_XNOR: // ~^ 
		case BITWISE_XOR: // ^
			/* we'll padd the other inputs with 0, do it for the largest and throw a warning */
			if (list_size == 2)
			{
				output_port_width = max_input_port_width;
				input_port_width = output_port_width;
			}
			else 
			{
				oassert(list_size == 1);
				/* Logical reduction - same as a logic function */
				output_port_width = 1;
				input_port_width = max_input_port_width;
			}
			break;
		case SR: // >>
		case SL: // <<
			/* Shifts doesn't matter about port size, but second input needs to be a number */
			output_port_width = max_input_port_width;
			input_port_width = -2;
			break;
		case LOGICAL_NOT: // ! 
		case LOGICAL_OR: // ||
		case LOGICAL_AND: // &&
			/* only one input port */
			output_port_width = 1;
			input_port_width = max_input_port_width;
			break;
		case LT: // <
		case GT: // >
		case LOGICAL_EQUAL: // == 
		case NOT_EQUAL: // !=
		case LTE: // <=
		case GTE: // >=
		{
			if (input_lists[0]->signal_list_size != input_lists[1]->signal_list_size)
			{
				int index_of_smallest = find_smallest_non_numerical(op, input_lists, 2);

				input_port_width = input_lists[index_of_smallest]->signal_list_size;

				/* pad the input lists */
				pad_with_zeros(op, input_lists[0], input_port_width, instance_name_prefix);
				pad_with_zeros(op, input_lists[1], input_port_width, instance_name_prefix);
			}
			else
			{
				input_port_width = input_lists[0]->signal_list_size;
			}
			output_port_width = 1;
			break;
		}
		case DIVIDE: // /
			error_message(NETLIST_ERROR,  op->line_number, op->file_number, "Divide operation not supported by Odin\n");
			break;
		case MODULO: // %
			error_message(NETLIST_ERROR,  op->line_number, op->file_number, "Modulo operation not supported by Odin\n");
			break;
		default:
			error_message(NETLIST_ERROR,  op->line_number, op->file_number, "Operation not supported by Odin\n");
			break;
	}

	oassert(input_port_width != -1);
	oassert(output_port_width != -1);

	for (i = 0; i < list_size; i++)
	{
		if ((operation_node->type == SR) || (operation_node->type == SL))
		{
			/* Need to check that 2nd operand is constant */
			ast_node_t *second = resolve_node(instance_name_prefix, op->children[1]);
			if (second->type != NUMBERS)
				error_message(NETLIST_ERROR, op->line_number, op->file_number, "Odin only supports constant shifts at present\n");
			oassert(second->type == NUMBERS);

			/* for shift left or right, it's actually a one port operation. The 2nd port is constant */
			if (i == 0)
			{
				/* allocate the pins needed */
				allocate_more_node_input_pins(operation_node, input_lists[i]->signal_list_size);
				/* record this port size */
				add_input_port_information(operation_node, input_lists[i]->signal_list_size);
				/* hookup the input pins */
				hookup_input_pins_from_signal_list(operation_node, current_idx, input_lists[i], 0, input_lists[i]->signal_list_size, verilog_netlist);
			}
		}
		else if (input_port_width != -2)
		{
			/* IF taking port widths based on preset */
			/* allocate the pins needed */
			allocate_more_node_input_pins(operation_node, input_port_width);
			/* record this port size */
			add_input_port_information(operation_node, input_port_width);

			/* hookup the input pins = will do padding of zeros for smaller port */
			hookup_input_pins_from_signal_list(operation_node, current_idx, input_lists[i], 0, input_port_width, verilog_netlist);
			current_idx += input_port_width;
		}
		else
		{
			/* ELSE if taking the port widths as they are */
			/* allocate the pins needed */
			allocate_more_node_input_pins(operation_node, input_lists[i]->signal_list_size);
			/* record this port size */
			add_input_port_information(operation_node, input_lists[i]->signal_list_size);

			/* hookup the input pins */
			hookup_input_pins_from_signal_list(operation_node, current_idx, input_lists[i], 0, input_lists[i]->signal_list_size, verilog_netlist);
			
			current_idx += input_lists[i]->signal_list_size;
		}


	}
	/* allocate the pins for the ouput port */
	allocate_more_node_output_pins(operation_node, output_port_width);
	add_output_port_information(operation_node, output_port_width);
		
	/* make the inplicit output list and hook up the outputs */
	for (i = 0; i < output_port_width; i++)
	{
		npin_t *new_pin1;
		npin_t *new_pin2;
		nnet_t *new_net;
		new_pin1 = allocate_npin();
		new_pin2 = allocate_npin();
		new_net = allocate_nnet();
		new_net->name = operation_node->name;
		/* hook the output pin into the node */
		add_a_output_pin_to_node_spot_idx(operation_node, new_pin1, i);
		/* hook up new pin 1 into the new net */
		add_a_driver_pin_to_net(new_net, new_pin1);
		/* hook up the new pin 2 to this new net */
		add_a_fanout_pin_to_net(new_net, new_pin2);
		
		/* add the new_pin 2 to the list of outputs */
		add_pin_to_signal_list(return_list, new_pin2);
	}

	for (i = 0; i < list_size; i++)
	{
		clean_signal_list_structure(input_lists[i]);
	}

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: evaluate_sensitivity_list)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *evaluate_sensitivity_list(ast_node_t *delay_control, char *instance_name_prefix)
{
	int i;
	short edge_type = -1;
	signal_list_t *return_sig_list = init_signal_list_structure();
	signal_list_t *temp_list;

	if (delay_control == NULL)
	{
		/* Assume always @(*) */
		clean_signal_list_structure(return_sig_list);
		return_sig_list = NULL;
		type_of_circuit = COMBINATIONAL;

		return return_sig_list;
	}

	oassert(delay_control->type == DELAY_CONTROL);

	for (i = 0; i < delay_control->num_children; i++)
	{
		if (	((delay_control->children[i]->type == NEGEDGE) || (delay_control->children[i]->type == POSEDGE)) 
			&& 
			((edge_type == -1) || (edge_type == SEQUENTIAL)))
		{
			edge_type = SEQUENTIAL;		

			temp_list = create_pins(delay_control->children[i]->children[0], NULL, instance_name_prefix);
			oassert(temp_list->signal_list_size == 1);

			add_pin_to_signal_list(return_sig_list, temp_list->signal_list[0]);
			clean_signal_list_structure(temp_list);
		}
		else if ((edge_type == -1) || (edge_type == COMBINATIONAL))
		{
			/* ELSE - a combinational edge and we don't need to do anything */
			edge_type = COMBINATIONAL;
		}
		else
		{
			error_message(NETLIST_ERROR, delay_control->line_number, delay_control->file_number,
					"Sensitivity list switches from sequential and combinational.  You can't define something like always @(posedge clock or a).\n");
		}
	}

	/* update the analysis type of this block of statements */
	if (edge_type == -1)
	{
		error_message(NETLIST_ERROR, delay_control->line_number, delay_control->file_number, "Sensitivity list error...looks empty?\n");
	}
	else if (edge_type == COMBINATIONAL)
	{
		clean_signal_list_structure(return_sig_list);
		return_sig_list = NULL;
		type_of_circuit = edge_type;
	}
	else if (edge_type == SEQUENTIAL)
	{
		type_of_circuit = edge_type;
	}

	return return_sig_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_if_for_question)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_if_for_question(ast_node_t *if_ast, char *instance_name_prefix)
{
	signal_list_t *return_list;
	nnode_t *if_node;

	/* create the node */
	if_node = allocate_nnode();
	/* store all the relevant info */
	if_node->related_ast_node = if_ast;
	if_node->type = MULTI_PORT_MUX; // port 1 = control, port 2+ = mux options
	if_node->name = node_name(if_node, instance_name_prefix);

	/* create the control structure for the if node */
	create_if_control_signals(if_ast->children[0], if_node, instance_name_prefix);

	/* create the statements and integrate them into the mux */
	return_list = create_if_question_mux_expressions(if_ast, if_node, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_if_question_mux_expressions)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_if_question_mux_expressions(ast_node_t *if_ast, nnode_t *if_node, char *instance_name_prefix)
{
	signal_list_t **if_expressions;
	signal_list_t *return_list;
	int i;

	/* make storage for statements and expressions */
	if_expressions = (signal_list_t**)malloc(sizeof(signal_list_t*)*2);

	/* now we will process the statements and add to the other ports */
	for (i = 0; i < 2; i++)
	{
		if (if_ast->children[i+1] != NULL) // checking to see if expression exists.  +1 since first child is control expression
		{
			/* IF - this is a normal case item, then process the case match and the details of the statement */
			if_expressions[i] = netlist_expand_ast_of_module(if_ast->children[i+1], instance_name_prefix);
		}
		else 
		{
			error_message(NETLIST_ERROR, if_ast->line_number, if_ast->file_number, "No such thing as a a = b ? z;\n");
		}
	}
	
	/* now with all the lists sorted, we do the matching and proper propogation */	
	return_list = create_mux_expressions(if_expressions, if_node, 2, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_if)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_if(ast_node_t *if_ast, char *instance_name_prefix)
{
	signal_list_t *return_list;
	nnode_t *if_node;

	/* create the node */
	if_node = allocate_nnode();
	/* store all the relevant info */
	if_node->related_ast_node = if_ast;
	if_node->type = MULTI_PORT_MUX; // port 1 = control, port 2+ = mux options
	if_node->name = node_name(if_node, instance_name_prefix);

	/* create the control structure for the if node */
	create_if_control_signals(if_ast->children[0], if_node, instance_name_prefix);

	/* create the statements and integrate them into the mux */
	return_list = create_if_mux_statements(if_ast, if_node, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_if_control_signals)
 *-------------------------------------------------------------------------------------------*/
void create_if_control_signals(ast_node_t *if_expression, nnode_t *if_node, char *instance_name_prefix)
{
	signal_list_t *if_logic_expression;
	signal_list_t *if_logic_expression_final;
	nnode_t *not_node;
	npin_t *not_pin;
	signal_list_t *out_pin_list;

	/* reserve the first 2 pins of the mux for the control signals */
	allocate_more_node_input_pins(if_node, 2);
	/* record this port size */
	add_input_port_information(if_node, 2);
	
	/* get the logic */
	if_logic_expression = netlist_expand_ast_of_module(if_expression, instance_name_prefix);
	oassert(if_logic_expression != NULL);

	if(if_logic_expression->signal_list_size != 1)
	{
		nnode_t *or_gate;
		signal_list_t *default_expression;
		
		or_gate = make_1port_logic_gate_with_inputs(LOGICAL_OR, if_logic_expression->signal_list_size, if_logic_expression, if_node, -1);
		default_expression = make_output_pins_for_existing_node(or_gate, 1);
		
		/* copy that output pin to be put into the default */
		add_a_input_pin_to_node_spot_idx(if_node, default_expression->signal_list[0], 0);

		if_logic_expression_final = default_expression;
	}
	else
	{
		/* hookup this pin to the spot in the if_node */
		add_a_input_pin_to_node_spot_idx(if_node, if_logic_expression->signal_list[0], 0);
		if_logic_expression_final = if_logic_expression;
	}

	/* hookup pin again to not gate and then to other spot */
	not_pin = copy_input_npin(if_logic_expression_final->signal_list[0]);

	/* make a NOT gate that collects all the other signals and if they're all off */
	not_node = make_not_gate_with_input(not_pin, if_node, -1);

	/* get the output pin of the not gate .... also adds a net inbetween and the linking output pin to node and net */
	out_pin_list = make_output_pins_for_existing_node(not_node, 1);
	oassert(out_pin_list->signal_list_size == 1);
			

	// Mark the else condition for the simulator.
	out_pin_list->signal_list[0]->is_default = TRUE;

	/* copy that output pin to be put into the default */
	add_a_input_pin_to_node_spot_idx(if_node, out_pin_list->signal_list[0], 1);

	clean_signal_list_structure(out_pin_list);
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_if_mux_statements)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_if_mux_statements(ast_node_t *if_ast, nnode_t *if_node, char *instance_name_prefix)
{
	signal_list_t **if_statements;
	signal_list_t *return_list;
	int i;

	/* make storage for statements and expressions */
	if_statements = (signal_list_t**)malloc(sizeof(signal_list_t*)*2);

	/* now we will process the statements and add to the other ports */
	for (i = 0; i < 2; i++)
	{
		if (if_ast->children[i+1] != NULL) // checking to see if statement exists.  +1 since first child is control expression
		{
			/* IF - this is a normal case item, then process the case match and the details of the statement */
			if_statements[i] = netlist_expand_ast_of_module(if_ast->children[i+1], instance_name_prefix);
			sort_signal_list_alphabetically(if_statements[i]);
		}
		else 
		{
			/* ELSE - there is no if/else and we need to make a placeholder since it means there will be implied signals */
			if_statements[i] = init_signal_list_structure();
		}
	}
	
	/* now with all the lists sorted, we do the matching and proper propogation */	
	return_list = create_mux_statements(if_statements, if_node, 2, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function: create_case)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_case(ast_node_t *case_ast, char *instance_name_prefix)
{
	signal_list_t *return_list;
	nnode_t *case_node;
	ast_node_t *case_list_of_items;
	ast_node_t *case_match_input;

	/* create the node */
	case_node = allocate_nnode();
	/* store all the relevant info */
	case_node->related_ast_node = case_ast;
	case_node->type = MULTI_PORT_MUX; // port 1 = control, port 2+ = mux options
	case_node->name = node_name(case_node, instance_name_prefix);

	/* pull out the identifier to match to "i.e. case(a_in)" - this is the pins we match against */
	case_match_input = case_ast->children[0];

	/* point to the case list */
	case_list_of_items = case_ast->children[1];
	
	/* create all the control structures for the case mux ... each bit will turn on one of the paths ... one hot mux */
	create_case_control_signals(case_list_of_items, case_match_input, case_node, instance_name_prefix);

	/* create the statements and integrate them into the mux */
	return_list = create_case_mux_statements(case_list_of_items, case_node, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_case_control_signals)
 *-------------------------------------------------------------------------------------------*/
void create_case_control_signals(ast_node_t *case_list_of_items, ast_node_t *compare_against, nnode_t *case_node, char *instance_name_prefix)
{
	int i;
	signal_list_t *other_expressions_pin_list = init_signal_list_structure();

	/* reserve the first X pins of the mux for the control signals where X is the number of items */
	allocate_more_node_input_pins(case_node, case_list_of_items->num_children);
	/* record this port size */
	add_input_port_information(case_node, case_list_of_items->num_children);
	
	/* now go through each of the case items and build the comparison expressions */
	for (i = 0; i < case_list_of_items->num_children; i++)
	{
		if (case_list_of_items->children[i]->type == CASE_ITEM)
		{
			/* IF - this is a normal case item, then process the case match and the details of the statement */
			signal_list_t *case_compare_expression;
			signal_list_t **case_compares = (signal_list_t **)malloc(sizeof(signal_list_t*)*2);
			ast_node_t *logical_equal = create_node_w_type(BINARY_OPERATION, -1, -1);
			logical_equal->types.operation.op = LOGICAL_EQUAL;

			/* get the signals to compare against */
			case_compares[0] = netlist_expand_ast_of_module(compare_against, instance_name_prefix);
			case_compares[1] = netlist_expand_ast_of_module(case_list_of_items->children[i]->children[0], instance_name_prefix);

			/* make a LOGIC_EQUAL gate that collects all the other signals and if they're all off */
			case_compare_expression = create_operation_node(logical_equal, case_compares, 2, instance_name_prefix);
			oassert(case_compare_expression->signal_list_size == 1);

			/* hookup this pin to the spot in the case_node */
			add_a_input_pin_to_node_spot_idx(case_node, case_compare_expression->signal_list[0], i);

			/* copy that output pin to be put into the default */
			add_pin_to_signal_list(other_expressions_pin_list, copy_input_npin(case_compare_expression->signal_list[0]));
			
			/* clean up */
			clean_signal_list_structure(case_compare_expression);

			free(case_compares);
		}
		else if (case_list_of_items->children[i]->type == CASE_DEFAULT)
		{
			/* take all the other pins from the case expressions and intstall in the condition */
			nnode_t *default_node;
			signal_list_t *default_expression;

			oassert(i == case_list_of_items->num_children - 1); // has to be at the end

			/* make a NOR gate that collects all the other signals and if they're all off */
			default_node = make_1port_logic_gate_with_inputs(LOGICAL_NOR, case_list_of_items->num_children-1, other_expressions_pin_list, case_node, -1);
			default_expression = make_output_pins_for_existing_node(default_node, 1);
			
			// Mark the "default" case for simulation.
			default_expression->signal_list[0]->is_default = TRUE;

			/* copy that output pin to be put into the default */
			add_a_input_pin_to_node_spot_idx(case_node, default_expression->signal_list[0], i);
		}
		else
		{
			oassert(FALSE);
		}
	}
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_case_mux_statements)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_case_mux_statements(ast_node_t *case_list_of_items, nnode_t *case_node, char *instance_name_prefix)
{
	signal_list_t **case_statement;
	signal_list_t *return_list;
	int i;

	/* make storage for statements and expressions */
	case_statement = (signal_list_t**)malloc(sizeof(signal_list_t*)*(case_list_of_items->num_children));

	/* now we will process the statements and add to the other ports */
	for (i = 0; i < case_list_of_items->num_children; i++)
	{
		if (case_list_of_items->children[i]->type == CASE_ITEM)
		{
			/* IF - this is a normal case item, then process the case match and the details of the statement */
			case_statement[i] = netlist_expand_ast_of_module(case_list_of_items->children[i]->children[1], instance_name_prefix);
			sort_signal_list_alphabetically(case_statement[i]);
		}
		else if (case_list_of_items->children[i]->type == CASE_DEFAULT)
		{
			oassert(i == case_list_of_items->num_children - 1); // has to be at the end
			case_statement[i] = netlist_expand_ast_of_module(case_list_of_items->children[i]->children[0], instance_name_prefix);
			sort_signal_list_alphabetically(case_statement[i]);
		}
		else
		{
			oassert(FALSE);
		}
	}
	
	/* now with all the lists sorted, we do the matching and proper propogation */	
	return_list = create_mux_statements(case_statement, case_node, case_list_of_items->num_children, instance_name_prefix);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_mux_statements)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_mux_statements(signal_list_t **statement_lists, nnode_t *mux_node, int num_statement_lists, char *instance_name_prefix)
{
	int i, j;
	signal_list_t *combined_lists;
	int *per_case_statement_idx;
	signal_list_t *return_list = init_signal_list_structure();
	int in_index = 1;
	int out_index = 0;

	/* allocate and initialize indexes */
	per_case_statement_idx = (int*)calloc(sizeof(int), num_statement_lists);

	/* make the uber list and sort it */
	combined_lists = combine_lists_without_freeing_originals(statement_lists, num_statement_lists);
	sort_signal_list_alphabetically(combined_lists);

	for (i = 0; i < combined_lists->signal_list_size; i++)
	{
		int i_skip = 0; // iskip is the number of statemnts that do have this signal so we can skip in the combine list
		npin_t *new_pin1;
		npin_t *new_pin2;
		nnet_t *new_net;
		new_pin1 = allocate_npin();
		new_pin2 = allocate_npin();
		new_net = allocate_nnet();

		/* allocate a port the width of all the signals ... one MUX */
		allocate_more_node_input_pins(mux_node, num_statement_lists);
		/* record the port size */
		add_input_port_information(mux_node, num_statement_lists);

		/* allocate the pins for the ouput port and pass out that pin for higher statements */
		allocate_more_node_output_pins(mux_node, 1);
		add_a_output_pin_to_node_spot_idx(mux_node, new_pin1, out_index);
		/* hook up new pin 1 into the new net */
		add_a_driver_pin_to_net(new_net, new_pin1);
		/* hook up the new pin 2 to this new net */
		add_a_fanout_pin_to_net(new_net, new_pin2);
		/* name it with this name */
		new_pin2->name = combined_lists->signal_list[i]->name;
		/* add this pin to the return list */
		add_pin_to_signal_list(return_list, new_pin2);

		/* going through each of the statement lists looking for common ones and building implied ones if they're not there */
		for (j = 0; j < num_statement_lists; j++)
		{
			int pin_index = in_index*num_statement_lists+j;

			/* check if the current element for this case statement is defined */ 	
			if (
					   (per_case_statement_idx[j] < statement_lists[j]->signal_list_size)
					&& (strcmp(combined_lists->signal_list[i]->name, statement_lists[j]->signal_list[per_case_statement_idx[j]]->name) == 0)
			)
			{
				/* If they match then we have a signal with this name and we can attach the pin */ 
				add_a_input_pin_to_node_spot_idx(mux_node, statement_lists[j]->signal_list[per_case_statement_idx[j]], pin_index);

				per_case_statement_idx[j]++; // increment the local index
				i_skip ++; // it's a match so the combo list will have atleast +1 entries the same
			}
			else
			{
				/* Don't match, so this signal is an IMPLIED SIGNAL !!! */


				/* implied signal for mux */
				if (type_of_circuit == SEQUENTIAL)
				{
					/* lookup this driver name */
					signal_list_t *this_pin_list = create_pins(NULL, combined_lists->signal_list[i]->name, instance_name_prefix);
					oassert(this_pin_list->signal_list_size == 1);
					//add_a_input_pin_to_node_spot_idx(mux_node, get_a_zero_pin(verilog_netlist), pin_index);
					add_a_input_pin_to_node_spot_idx(mux_node, this_pin_list->signal_list[0], pin_index);

					/* clean up */
					clean_signal_list_structure(this_pin_list);
				}
				else if (type_of_circuit == COMBINATIONAL)
				{
					/* DON'T CARE - so hookup zero */
					add_a_input_pin_to_node_spot_idx(mux_node, get_a_zero_pin(verilog_netlist), pin_index);
					// Allows the simulator to be aware of the implied nature of this signal.
					mux_node->input_pins[pin_index]->is_implied = TRUE;
				}
				else
					oassert(FALSE);
			}
		}

		i += i_skip - 1; // for every match move index i forward except this one wihich is handled by for i++ 
		in_index++;
		out_index++;
	}

	/* clean up */
	for (i = 0; i < num_statement_lists; i++)
	{
		clean_signal_list_structure(statement_lists[i]);
	}
	clean_signal_list_structure(combined_lists);

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  create_mux_expressions)
 *-------------------------------------------------------------------------------------------*/
signal_list_t *create_mux_expressions(signal_list_t **expression_lists, nnode_t *mux_node, int num_expression_lists, char *instance_name_prefix)
{
	int i, j;
	signal_list_t *return_list = init_signal_list_structure();
	int max_index = -1;

	/* find the biggest element */
	for (i = 0; i < num_expression_lists; i++)
	{
		if (max_index < expression_lists[i]->signal_list_size)
		{
			max_index = expression_lists[i]->signal_list_size;
		}
	}

	for (i = 0; i < max_index; i++)
	{
		npin_t *new_pin1;
		npin_t *new_pin2;
		nnet_t *new_net;
		new_pin1 = allocate_npin();
		new_pin2 = allocate_npin();
		new_net = allocate_nnet();

		/* allocate a port the width of all the signals ... one MUX */
		allocate_more_node_input_pins(mux_node, num_expression_lists);
		/* record the port information */
		add_input_port_information(mux_node, num_expression_lists);

		/* allocate the pins for the ouput port and pass out that pin for higher statements */
		allocate_more_node_output_pins(mux_node, 1);
		add_a_output_pin_to_node_spot_idx(mux_node, new_pin1, i);
		/* hook up new pin 1 into the new net */
		add_a_driver_pin_to_net(new_net, new_pin1);
		/* hook up the new pin 2 to this new net */
		add_a_fanout_pin_to_net(new_net, new_pin2);
		/* name it with this name */
		new_pin2->name = NULL; 
		/* add this pin to the return list */
		add_pin_to_signal_list(return_list, new_pin2);

		/* going through each of the statement lists looking for common ones and building implied ones if they're not there */
		for (j = 0; j < num_expression_lists; j++)
		{
			int pin_index = (i+1)*num_expression_lists+j;

			/* check if the current element for this case statement is defined */ 	
			if (i < expression_lists[j]->signal_list_size)
			{
				/* If there is a signal */
				add_a_input_pin_to_node_spot_idx(mux_node, expression_lists[j]->signal_list[i], pin_index);

			}
			else
			{
				/* Don't match, so this signal is an IMPLIED SIGNAL !!! */
				/* implied signal for mux */
				/* DON'T CARE - so hookup zero */
				add_a_input_pin_to_node_spot_idx(mux_node, get_a_zero_pin(verilog_netlist), pin_index);
			}
		}
	}

	/* clean up */
	for (i = 0; i < num_expression_lists; i++)
	{
		clean_signal_list_structure(expression_lists[i]);
	}

	return return_list;
}

/*---------------------------------------------------------------------------------------------
 * (function:  pad_compares_to_smallest_non_numerical_implementation)
 *-------------------------------------------------------------------------------------------*/
int find_smallest_non_numerical(ast_node_t *node, signal_list_t **input_list, int num_input_lists)
{
	int i;
	int smallest;
	int smallest_idx;
	short *tested = (short*)calloc(sizeof(short), num_input_lists);
	short found_non_numerical = FALSE;
	
	while(found_non_numerical == FALSE)
	{
		smallest_idx = -1;
		smallest = -1;

		/* find the smallest width, now verify that it's not a number */
		for (i = 0; i < num_input_lists; i++)
		{
			if (tested[i] == 1)
			{
				/* skip the ones we've already tried */
				continue;
			}
			if ((smallest == -1) || (smallest >= input_list[i]->signal_list_size))
			{
				smallest = input_list[i]->signal_list_size;
				smallest_idx = i;
			}
		}	

		if (smallest_idx == -1)
		{
			error_message(NETLIST_ERROR, node->line_number, node->file_number, "all numbers in padding non numericals\n");
		}
		else
		{
			/* mark that we're evaluating this input */
			tested[smallest_idx] = TRUE;

			/* check if the smallest is not a number */
			for (i = 0; i < input_list[smallest_idx]->signal_list_size; i++)
			{
				if (input_list[smallest_idx]->signal_list[i]->name == NULL)
				{
					/* Not a number so this is the smallest */
					found_non_numerical = TRUE;
					break;
				}
				if (!((strstr(input_list[smallest_idx]->signal_list[i]->name, "ONE_VCC_CNS") != NULL)
						|| strstr(input_list[smallest_idx]->signal_list[i]->name, "ZERO_GND_ZERO") != NULL))
				{
					/* Not a number so this is the smallest */
					found_non_numerical = TRUE;
					break;
				}
			}
		}
	}

	return smallest_idx;
}

/*---------------------------------------------------------------------------------------------
 * (function: pad_with_zeros)
 *-------------------------------------------------------------------------------------------*/
void pad_with_zeros(ast_node_t* node, signal_list_t *list, int pad_size, char *instance_name_prefix)
{
	int i;

	if (pad_size > list->signal_list_size)
	{
		for (i = list->signal_list_size; i < pad_size; i++)
		{
			if (global_args.all_warnings)
				warning_message(NETLIST_ERROR, node->line_number, node->file_number,
						"Padding an input port with 0 for operation (likely compare)\n");
			add_pin_to_signal_list(list, get_a_zero_pin(verilog_netlist));
		}
	}
	else if (pad_size < list->signal_list_size) 
	{
		if (global_args.all_warnings)
			warning_message(NETLIST_ERROR, node->line_number, node->file_number,
					"More driver pins than nets to drive.  This means that for this operation you are losing some of the most significant bits\n");
	}
}

#ifdef VPR6
/*--------------------------------------------------------------------------
 * (function: create_dual_port_ram_block)
 * 	This function creates a dual port ram block node in the netlist 
 *	and hooks up the inputs and outputs.
 *------------------------------------------------------------------------*/
signal_list_t *create_dual_port_ram_block(ast_node_t* block, char *instance_name_prefix, t_model* hb_model)
{
	signal_list_t **in_list, *return_list;
	nnode_t *block_node;
	ast_node_t *block_instance = block->children[1];
	ast_node_t *block_list = block_instance->children[1];
	ast_node_t *block_connect;
	char *ip_name;
	t_model_ports *hb_ports;
	int i, j, current_idx, current_out_idx;
	int out_port_size1, out_port_size2;

	out_port_size1 = 0;
	out_port_size2 = 0;
	if ((hb_model == NULL) || (strcmp(hb_model->name, "dual_port_ram") != 0))
	{
		printf("Error in creating dual port ram\n");
		oassert(FALSE);
	}

	// EDDIE: Uses new enum in ids: RAM (opposed to MEMORY from operation_t previously)
	block->type = RAM;
	return_list = init_signal_list_structure();
	current_idx = 0;
	current_out_idx = 0;

	/* create the node */
	block_node = allocate_nnode();
	/* store all of the relevant info */
	block_node->related_ast_node = block;
	block_node->type = HARD_IP;
	block_node->name = hard_node_name(block_node, instance_name_prefix, block->children[0]->types.identifier, block_instance->children[0]->types.identifier);
	
	/* Declare the hard block as used for the blif generation */
	hb_model->used = 1;

	/* Need to do a sanity check to make sure ports line up */
	for (i = 0; i < block_list->num_children; i++)
	{
		block_connect = block_list->children[i];
		ip_name = block_connect->children[0]->types.identifier;
		hb_ports = hb_model->inputs;
		while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
			hb_ports = hb_ports->next;
		if (hb_ports == NULL)
		{
			hb_ports = hb_model->outputs;
			while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
				hb_ports = hb_ports->next;
		}

		if (hb_ports == NULL)
		{
			printf("Non-existant port %s in hard block %s\n", ip_name, block->children[0]->types.identifier);
			block_connect->children[1]->hb_port = NULL;
			oassert(FALSE);
		}

		/* Link the signal to the port definition */
		block_connect->children[1]->hb_port = (void *)hb_ports;
	}




	in_list = (signal_list_t **)malloc(sizeof(signal_list_t *)*block_list->num_children);
	for (i = 0; i < block_list->num_children; i++)
	{
		int port_size;
		ast_node_t *block_port_connect;

		in_list[i] = NULL;
		block_connect = block_list->children[i]->children[0];
		block_port_connect = block_list->children[i]->children[1];
		hb_ports = (t_model_ports *)block_list->children[i]->children[1]->hb_port;
		ip_name = block_connect->types.identifier;

		if (hb_ports->dir == IN_PORT)
		{
			int min_size = 0;

			/* Create the pins for port if needed */
			in_list[i] = create_pins(block_port_connect, NULL, instance_name_prefix);
			port_size = in_list[i]->signal_list_size;
			if (strcmp(hb_ports->name, "data1") == 0)
				out_port_size1 = port_size;
			if (strcmp(hb_ports->name, "data2") == 0)
				out_port_size2 = port_size;

			if ((strcmp(hb_ports->name, "addr1") == 0) ||
			  (strcmp(hb_ports->name, "addr2") == 0))
				if (port_size < hb_ports->size)
					min_size = hb_ports->size - port_size;

			for (j = 0; j < port_size; j++)
				in_list[i]->signal_list[j]->mapping = ip_name;

			/* allocate the pins needed */
			allocate_more_node_input_pins(block_node, port_size + min_size);
			/* record this port size */
			add_input_port_information(block_node, port_size + min_size);

			/* hookup the input pins */
			hookup_hb_input_pins_from_signal_list(block_node, current_idx, in_list[i], 0, port_size + min_size, verilog_netlist);

			/* Name any grounded ports in the block mapping */
			for (j = port_size; j < port_size + min_size; j++)
				block_node->input_pins[current_idx+j]->mapping = strdup(ip_name);
			current_idx += port_size + min_size;
		}
	}

	if (out_port_size2 != 0)
		oassert(out_port_size2 == out_port_size1);

	for (i = 0; i < block_list->num_children; i++)
	{
		int out_port_size;

		block_connect = block_list->children[i]->children[0];
		hb_ports = (t_model_ports *)block_list->children[i]->children[1]->hb_port;
		ip_name = block_connect->types.identifier;
		if (strcmp(hb_ports->name, "out1") == 0)
			out_port_size = out_port_size1;
		else
			out_port_size = out_port_size2;

		if (hb_ports->dir != IN_PORT)
		{
			char *alias_name;
			t_memory_port_sizes *ps;

			allocate_more_node_output_pins(block_node, out_port_size);
			add_output_port_information(block_node, out_port_size);

			alias_name = make_full_ref_name(
					instance_name_prefix,
					block->children[0]->types.identifier,
					block->children[1]->children[0]->types.identifier,
					block_connect->types.identifier, -1);
			ps = (t_memory_port_sizes *)malloc(sizeof(t_memory_port_sizes));
			ps->size = out_port_size;
			ps->name = alias_name;
			memory_port_size_list = insert_in_vptr_list(memory_port_size_list, ps);

			/* make the implicit output list and hook up the outputs */
			for (j = 0; j < out_port_size; j++)
			{
				npin_t *new_pin1;
				npin_t *new_pin2;
				nnet_t *new_net;
				char *pin_name;
				long sc_spot;

				if (out_port_size > 1)
					pin_name = make_full_ref_name(
							instance_name_prefix,
							block->children[0]->types.identifier,
							block->children[1]->children[0]->types.identifier,
							block_connect->types.identifier,
							j
					);

				else
					pin_name = make_full_ref_name(
							instance_name_prefix,
							block->children[0]->types.identifier,
							block->children[1]->children[0]->types.identifier,
							block_connect->types.identifier,
							-1
					);

				new_pin1 = allocate_npin();
				new_pin1->mapping = make_signal_name(hb_ports->name, -1);
				new_pin1->name = pin_name;
				new_pin2 = allocate_npin();
				new_net = allocate_nnet();
				new_net->name = hb_ports->name;
				/* hook the output pin into the node */
				add_a_output_pin_to_node_spot_idx(block_node, new_pin1, current_out_idx + j);
				/* hook up new pin 1 into the new net */
				add_a_driver_pin_to_net(new_net, new_pin1);
				/* hook up the new pin 2 to this new net */
				add_a_fanout_pin_to_net(new_net, new_pin2);

				/* add the new_pin 2 to the list of outputs */
				add_pin_to_signal_list(return_list, new_pin2);

				/* add the net to the list of inputs */
				sc_spot = sc_add_string(input_nets_sc, pin_name);
				input_nets_sc->data[sc_spot] = (void*)new_net;
			}
			current_out_idx += j;
		}
	}

	for (i = 0; i < block_list->num_children; i++)
	{
		clean_signal_list_structure(in_list[i]);
	}

	dp_memory_list = insert_in_vptr_list(dp_memory_list, block_node);
	block_node->type = MEMORY;

	return return_list;
}

/*--------------------------------------------------------------------------
 * (function: create_single_port_ram_block)
 * 	This function creates a single port ram block node in the netlist 
 *	and hooks up the inputs and outputs.
 *------------------------------------------------------------------------*/
signal_list_t *create_single_port_ram_block(ast_node_t* block, char *instance_name_prefix, t_model* hb_model)
{
	signal_list_t **in_list, *return_list;
	nnode_t *block_node;
	ast_node_t *block_instance = block->children[1];
	ast_node_t *block_list = block_instance->children[1];
	ast_node_t *block_connect;
	char *ip_name = NULL;
	t_model_ports *hb_ports;
	int i, j, current_idx, current_out_idx;
	int out_port_size = 0;

	if ((hb_model == NULL) || (strcmp(hb_model->name, "single_port_ram") != 0))
	{
		printf("Error in creating single port ram\n");
		oassert(FALSE);
	}

	// EDDIE: Uses new enum in ids: RAM (opposed to MEMORY from operation_t previously)
	block->type = RAM;
	return_list = init_signal_list_structure();
	current_idx = 0;
	current_out_idx = 0;

	/* create the node */
	block_node = allocate_nnode();
	/* store all of the relevant info */
	block_node->related_ast_node = block;
	block_node->type = HARD_IP;
	block_node->name = hard_node_name(block_node,
			instance_name_prefix,
			block->children[0]->types.identifier,
			block_instance->children[0]->types.identifier
	);
	
	/* Declare the hard block as used for the blif generation */
	hb_model->used = 1;

	/* Need to do a sanity check to make sure ports line up */
	for (i = 0; i < block_list->num_children; i++)
	{
		block_connect = block_list->children[i];
		ip_name = block_connect->children[0]->types.identifier;
		hb_ports = hb_model->inputs;
		while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
			hb_ports = hb_ports->next;
		if (hb_ports == NULL)
		{
			hb_ports = hb_model->outputs;
			while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
				hb_ports = hb_ports->next;
		}

		if (hb_ports == NULL)
		{
			printf("Non-existant port %s in hard block %s\n", ip_name, block->children[0]->types.identifier);
			block_connect->children[1]->hb_port = NULL;
			oassert(FALSE);
		}

		/* Link the signal to the port definition */
		block_connect->children[1]->hb_port = (void *)hb_ports;
	}

	/* Need to make sure ALL ports are defined */
	hb_ports = hb_model->inputs;
	i = 0;
	while (hb_ports != NULL)
	{
		i++;
		hb_ports = hb_ports->next;
	}
	hb_ports = hb_model->outputs;
	while (hb_ports != NULL)
	{
		i++;
		hb_ports = hb_ports->next;
	}
	if (i != block_list->num_children)
	{
		printf("Not all ports defined in hard block %s\n", ip_name);
		oassert(FALSE);
	}

	in_list = (signal_list_t **)malloc(sizeof(signal_list_t *)*block_list->num_children);
	for (i = 0; i < block_list->num_children; i++)
	{
		int port_size;
		ast_node_t *block_port_connect;

		in_list[i] = NULL;
		block_connect = block_list->children[i]->children[0];
		block_port_connect = block_list->children[i]->children[1];
		hb_ports = (t_model_ports *)block_list->children[i]->children[1]->hb_port;
		ip_name = block_connect->types.identifier;

		if (hb_ports->dir == IN_PORT)
		{
			int min_size = 0;

			/* Create the pins for port if needed */
			in_list[i] = create_pins(block_port_connect, NULL, instance_name_prefix);
			port_size = in_list[i]->signal_list_size;
			if (strcmp(hb_ports->name, "data") == 0)
				out_port_size = port_size;

			if (strcmp(hb_ports->name, "addr") == 0)
				if (port_size < hb_ports->size)
					min_size = hb_ports->size - port_size;

			for (j = 0; j < port_size; j++)
				in_list[i]->signal_list[j]->mapping = ip_name;

			/* allocate the pins needed */
			allocate_more_node_input_pins(block_node, port_size + min_size);
			/* record this port size */
			add_input_port_information(block_node, port_size + min_size);

			/* hookup the input pins */
			hookup_hb_input_pins_from_signal_list(block_node, current_idx, in_list[i], 0, port_size + min_size, verilog_netlist);

			/* Name any grounded ports in the block mapping */
			for (j = port_size; j < port_size + min_size; j++)
				block_node->input_pins[current_idx+j]->mapping = strdup(ip_name);
			current_idx += port_size + min_size;
		}
	}

	for (i = 0; i < block_list->num_children; i++)
	{
		block_connect = block_list->children[i]->children[0];
		hb_ports = (t_model_ports *)block_list->children[i]->children[1]->hb_port;
		ip_name = block_connect->types.identifier;

		if (hb_ports->dir != IN_PORT)
		{
			char *alias_name;
			t_memory_port_sizes *ps;

			allocate_more_node_output_pins(block_node, out_port_size);
			add_output_port_information(block_node, out_port_size);

			alias_name = make_full_ref_name(
					instance_name_prefix,
					block->children[0]->types.identifier,
					block->children[1]->children[0]->types.identifier,
					block_connect->types.identifier, -1
			);
			ps = (t_memory_port_sizes *)malloc(sizeof(t_memory_port_sizes));
			ps->size = out_port_size;
			ps->name = alias_name;
			memory_port_size_list = insert_in_vptr_list(memory_port_size_list, ps);

			/* make the implicit output list and hook up the outputs */
			for (j = 0; j < out_port_size; j++)
			{
				npin_t *new_pin1;
				npin_t *new_pin2;
				nnet_t *new_net;
				char *pin_name;
				long sc_spot;

				if (out_port_size > 1)
					pin_name = make_full_ref_name(instance_name_prefix,
							block->children[0]->types.identifier,
							block->children[1]->children[0]->types.identifier,
							block_connect->types.identifier, j
					);
				else
					pin_name = make_full_ref_name(
							instance_name_prefix,
							block->children[0]->types.identifier,
							block->children[1]->children[0]->types.identifier,
							block_connect->types.identifier, -1
					);

				new_pin1 = allocate_npin();
				new_pin1->mapping = make_signal_name(hb_ports->name, -1);
				new_pin1->name = pin_name;
				new_pin2 = allocate_npin();
				new_net = allocate_nnet();
				new_net->name = hb_ports->name;
				/* hook the output pin into the node */
				add_a_output_pin_to_node_spot_idx(block_node, new_pin1, current_out_idx + j);
				/* hook up new pin 1 into the new net */
				add_a_driver_pin_to_net(new_net, new_pin1);
				/* hook up the new pin 2 to this new net */
				add_a_fanout_pin_to_net(new_net, new_pin2);

				/* add the new_pin 2 to the list of outputs */
				add_pin_to_signal_list(return_list, new_pin2);

				/* add the net to the list of inputs */
				sc_spot = sc_add_string(input_nets_sc, pin_name);
				input_nets_sc->data[sc_spot] = (void*)new_net;
			}
			current_out_idx += j;
		}
	}

	for (i = 0; i < block_list->num_children; i++)
	{
		clean_signal_list_structure(in_list[i]);
	}

	sp_memory_list = insert_in_vptr_list(sp_memory_list, block_node);
	block_node->type = MEMORY;
	block->net_node = block_node;

	return return_list;
}

/*--------------------------------------------------------------------------
 * (function: create_hard_block)
 * 	This function creates a hard block node in the netlist and hooks up the 
 * 	inputs and outputs.
 *------------------------------------------------------------------------*/

signal_list_t *create_hard_block(ast_node_t* block, char *instance_name_prefix)
{
	signal_list_t **in_list, *return_list;
	nnode_t *block_node;
	ast_node_t *block_instance = block->children[1];
	ast_node_t *block_list = block_instance->children[1];
	ast_node_t *block_connect;
	t_model *hb_model = NULL;
	char *ip_name;
	t_model_ports *hb_ports = NULL;
	int i, j, current_idx, current_out_idx;
	int is_mult = 0;
	int mult_size = 0;

	/* See if the hard block declared is supported by FPGA architecture */
	hb_model = find_hard_block(block->children[0]->types.identifier);
	if (hb_model == NULL)
	{
		printf("Found Hard Block %s: Not supported by FPGA Architecture\n", block->children[0]->types.identifier);
		oassert(FALSE);
	}

	/* single_port_ram's are a special case due to splitting */
	if (strcmp(hb_model->name, "single_port_ram") == 0)
	{
		return create_single_port_ram_block(block, instance_name_prefix, hb_model);
	}

	/* dual_port_ram's are a special case due to splitting */
	if (strcmp(hb_model->name, "dual_port_ram") == 0)
	{
		return create_dual_port_ram_block(block, instance_name_prefix, hb_model);
	}

	/* memory's are a special case due to splitting */
	if (strcmp(hb_model->name, "multiply") == 0)
	{
		is_mult = 1;
	}

	return_list = init_signal_list_structure();
	current_idx = 0;
	current_out_idx = 0;

	/* create the node */
	block_node = allocate_nnode();
	/* store all of the relevant info */
	block_node->related_ast_node = block;
	block_node->type = HARD_IP;
	block_node->name = hard_node_name(
			block_node,
			instance_name_prefix,
			block->children[0]->types.identifier,
			block_instance->children[0]->types.identifier
	);
	
	/* Declare the hard block as used for the blif generation */
	hb_model->used = 1;

	/* Need to do a sanity check to make sure ports line up */
	for (i = 0; i < block_list->num_children; i++)
	{
		block_connect = block_list->children[i];
		ip_name = block_connect->children[0]->types.identifier;
		hb_ports = hb_model->inputs;
		while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
			hb_ports = hb_ports->next;
		if (hb_ports == NULL)
		{
			hb_ports = hb_model->outputs;
			while ((hb_ports != NULL) && (strcmp(hb_ports->name, ip_name) != 0))
				hb_ports = hb_ports->next;
		}

		if (hb_ports == NULL)
		{
			printf("Non-existant port %s in hard block %s\n", ip_name, block->children[0]->types.identifier);
			block_connect->children[1]->hb_port = NULL;
			oassert(FALSE);
		}

		/* Link the signal to the port definition */
		block_connect->children[1]->hb_port = (void *)hb_ports;
	}

	in_list = (signal_list_t **)malloc(sizeof(signal_list_t *)*block_list->num_children);
	for (i = 0; i < block_list->num_children; i++)
	{
		int port_size;
		ast_node_t *block_port_connect;

		in_list[i] = NULL;
		block_connect = block_list->children[i]->children[0];
		block_port_connect = block_list->children[i]->children[1];
		hb_ports = (t_model_ports *)block_list->children[i]->children[1]->hb_port;
		ip_name = block_connect->types.identifier;

		if (hb_ports->dir == IN_PORT)
		{
			int min_size;

			/* Create the pins for port if needed */
			in_list[i] = create_pins(block_port_connect, NULL, instance_name_prefix);

			/* Only map the required number of pins to match port size */
			port_size = hb_ports->size;
			if (in_list[i]->signal_list_size < port_size)
				min_size = in_list[i]->signal_list_size;
			else
				min_size = port_size;

			/* IF a multiplier - leave input size arbitrary with no padding */
			if (is_mult == 1)
			{
				min_size = in_list[i]->signal_list_size;
				port_size = in_list[i]->signal_list_size;
				mult_size = mult_size + min_size;
			}

			for (j = 0; j < min_size; j++)
				in_list[i]->signal_list[j]->mapping = ip_name;

			/* allocate the pins needed */
			allocate_more_node_input_pins(block_node, port_size);
			/* record this port size */
			add_input_port_information(block_node, port_size);

			/* hookup the input pins */
			hookup_hb_input_pins_from_signal_list(block_node, current_idx, in_list[i], 0, port_size, verilog_netlist);

			/* Name any grounded ports in the block mapping */
			for (j = min_size; j < port_size; j++)
				block_node->input_pins[current_idx+j]->mapping = strdup(ip_name);
			current_idx += port_size;
		}
		else
		{
			/* IF a multiplier - need to process the output pins last!!! */
			/* Makes the assumption that a multiplier has only 1 output */
			if (is_mult == 0)
			{
				allocate_more_node_output_pins(block_node, hb_ports->size);
				add_output_port_information(block_node, hb_ports->size);

				/* make the implicit output list and hook up the outputs */
				for (j = 0; j < hb_ports->size; j++)
				{
					npin_t *new_pin1;
					npin_t *new_pin2;
					nnet_t *new_net;
					char *pin_name;
					long sc_spot;
	
					if (hb_ports->size > 1)
						pin_name = make_full_ref_name(block_node->name, NULL, NULL, hb_ports->name, j);
					else
						pin_name = make_full_ref_name(block_node->name, NULL, NULL, hb_ports->name, -1);
	
					new_pin1 = allocate_npin();
//					if (hb_ports->size > 1)
//						new_pin1->mapping = make_signal_name(hb_ports->name, j);
//					else
						new_pin1->mapping = make_signal_name(hb_ports->name, -1);

					new_pin1->name = pin_name;
					new_pin2 = allocate_npin();
					new_net = allocate_nnet();
					new_net->name = hb_ports->name;
					/* hook the output pin into the node */
					add_a_output_pin_to_node_spot_idx(block_node, new_pin1, current_out_idx + j);
					/* hook up new pin 1 into the new net */
					add_a_driver_pin_to_net(new_net, new_pin1);
					/* hook up the new pin 2 to this new net */
					add_a_fanout_pin_to_net(new_net, new_pin2);
	
					/* add the new_pin 2 to the list of outputs */
					add_pin_to_signal_list(return_list, new_pin2);

					/* add the net to the list of inputs */
					sc_spot = sc_add_string(input_nets_sc, pin_name);
					input_nets_sc->data[sc_spot] = (void*)new_net;
				}
				current_out_idx += j;
			}
		}
	}

	/* IF a multiplier - need to process the output pins now */
	/* Size of the output is estimated to be size of the inputs added */
	if (is_mult == 1)
	{
		allocate_more_node_output_pins(block_node, mult_size);
		add_output_port_information(block_node, mult_size);

		/* make the implicit output list and hook up the outputs */
		for (j = 0; j < mult_size; j++)
		{
			npin_t *new_pin1;
			npin_t *new_pin2;
			nnet_t *new_net;
			char *pin_name;
			long sc_spot;
	
			if (hb_ports->size > 1)
				pin_name = make_full_ref_name(block_node->name, NULL, NULL, hb_ports->name, j);
			else
				pin_name = make_full_ref_name(block_node->name, NULL, NULL, hb_ports->name, -1);

			new_pin1 = allocate_npin();
			if (hb_ports->size > 1)
				new_pin1->mapping = make_signal_name(hb_ports->name, j);
			else
				new_pin1->mapping = make_signal_name(hb_ports->name, -1);

			new_pin2 = allocate_npin();
			new_net = allocate_nnet();
			new_net->name = hb_ports->name;
			/* hook the output pin into the node */
			add_a_output_pin_to_node_spot_idx(block_node, new_pin1, current_out_idx + j);
			/* hook up new pin 1 into the new net */
			add_a_driver_pin_to_net(new_net, new_pin1);
			/* hook up the new pin 2 to this new net */
			add_a_fanout_pin_to_net(new_net, new_pin2);
	
			/* add the new_pin 2 to the list of outputs */
			add_pin_to_signal_list(return_list, new_pin2);

			/* add the net to the list of inputs */
			sc_spot = sc_add_string(input_nets_sc, pin_name);
			input_nets_sc->data[sc_spot] = (void*)new_net;
		}
		current_out_idx += j;
	}

	for (i = 0; i < block_list->num_children; i++)
	{
		clean_signal_list_structure(in_list[i]);
	}

	/* Add multiplier to list for later splitting and optimizing */
	if (is_mult == 1)
		mult_list = insert_in_vptr_list(mult_list, block_node);

	return return_list;
}
#endif
