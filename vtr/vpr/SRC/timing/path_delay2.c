#include <assert.h>
#include "util.h"
#include "vpr_types.h"
#include "globals.h"
#include "path_delay2.h"
#include "read_xml_arch_file.h"

/************* Variables (globals) shared by all path_delay modules **********/
/* [0..num_nets - 1].  Gives the index of the tnode that drives each net. */

int *net_to_driver_tnode;


/* [0..num__tnode_levels - 1].  Count and list of tnodes at each level of    *
 * the timing graph, to make breadth-first searches easier.                  */

struct s_ivec *tnodes_at_level;
int num_tnode_levels;		/* Number of levels in the timing graph. */



/******************* Subroutines local to this module ************************/

static int *alloc_and_load_tnode_fanin_and_check_edges(int *num_sinks_ptr);



/************************** Subroutine definitions ***************************/


static int *
alloc_and_load_tnode_fanin_and_check_edges(int *num_sinks_ptr)
{

/* Allocates an array and fills it with the number of in-edges (inputs) to   *
 * each tnode.  While doing this it also checks that each edge in the timing *
 * graph points to a valid tnode. Also counts the number of sinks.           */

    int inode, iedge, to_node, num_edges, error, num_sinks;
    int *tnode_num_fanin;
    t_tedge *tedge;

    tnode_num_fanin = (int *)my_calloc(num_tnodes, sizeof(int));
    error = 0;
    num_sinks = 0;

    for(inode = 0; inode < num_tnodes; inode++)
	{
	    num_edges = tnode[inode].num_edges;

	    if(num_edges > 0)
		{
		    tedge = tnode[inode].out_edges;
		    for(iedge = 0; iedge < num_edges; iedge++)
			{
			    to_node = tedge[iedge].to_node;
				if(to_node < 0 || to_node >= num_tnodes)
				{
				    printf
					("Error in alloc_and_load_tnode_fanin_and_check_edges:\n"
					 "tnode #%d edge #%d goes to illegal node #%d.\n",
					 inode, iedge, to_node);
				    error++;
				}

			    tnode_num_fanin[to_node]++;
			}
		}

	    else if(num_edges == 0)
		{
		    num_sinks++;
		}

	    else
		{
		    printf
			("Error in alloc_and_load_tnode_fanin_and_check_edges: \n"
			 "tnode #%d has %d edges.\n", inode, num_edges);
		    error++;
		}

	}

    if(error != 0)
	{
	    printf("Found %d Errors in the timing graph.  Aborting.\n",
		   error);
	    exit(1);
	}

    *num_sinks_ptr = num_sinks;
    return (tnode_num_fanin);
}


int
alloc_and_load_timing_graph_levels(void)
{

/* Does a breadth-first search through the timing graph in order to levelize *
 * it.  This allows subsequent breadth-first traversals to be faster. Also   *
 * returns the number of sinks in the graph (nodes with no fanout).          */

    t_linked_int *free_list_head, *nodes_at_level_head;
    int inode, num_at_level, iedge, to_node, num_edges, num_sinks,
	num_levels, i;
    t_tedge *tedge;

/* [0..num_tnodes-1]. # of in-edges to each tnode that have not yet been    *
 * seen in this traversal.                                                  */

    int *tnode_fanin_left;


    tnode_fanin_left = alloc_and_load_tnode_fanin_and_check_edges(&num_sinks);

    free_list_head = NULL;
    nodes_at_level_head = NULL;

/* Very conservative -> max number of levels = num_tnodes.  Realloc later.  *
 * Temporarily need one extra level on the end because I look at the first  *
 * empty level.                                                             */

    tnodes_at_level = (struct s_ivec *)my_malloc((num_tnodes + 1) *
						 sizeof(struct s_ivec));

/* Scan through the timing graph, putting all the primary input nodes (no    *
 * fanin) into level 0 of the level structure.                               */

    num_at_level = 0;

    for(inode = 0; inode < num_tnodes; inode++)
	{
	    if(tnode_fanin_left[inode] == 0)
		{
		    num_at_level++;
		    nodes_at_level_head =
			insert_in_int_list(nodes_at_level_head, inode,
					   &free_list_head);
		}
	}

    alloc_ivector_and_copy_int_list(&nodes_at_level_head, num_at_level,
				    &tnodes_at_level[0], &free_list_head);

    num_levels = 0;

    while(num_at_level != 0)
	{			/* Until there's nothing in the queue. */
	    num_levels++;
	    num_at_level = 0;

	    for(i = 0; i < tnodes_at_level[num_levels - 1].nelem; i++)
		{
		    inode = tnodes_at_level[num_levels - 1].list[i];
		    tedge = tnode[inode].out_edges;
		    num_edges = tnode[inode].num_edges;

		    for(iedge = 0; iedge < num_edges; iedge++)
			{
			    to_node = tedge[iedge].to_node;
			    tnode_fanin_left[to_node]--;

			    if(tnode_fanin_left[to_node] == 0)
				{
				    num_at_level++;
				    nodes_at_level_head =
					insert_in_int_list
					(nodes_at_level_head, to_node,
					 &free_list_head);
				}
			}
		}

	    alloc_ivector_and_copy_int_list(&nodes_at_level_head,
					    num_at_level,
					    &tnodes_at_level[num_levels],
					    &free_list_head);
	}

    tnodes_at_level =
	(struct s_ivec *)my_realloc(tnodes_at_level,
				    num_levels * sizeof(struct s_ivec));
    num_tnode_levels = num_levels;

    free(tnode_fanin_left);
    free_int_list(&free_list_head);
    return (num_sinks);
}


void
check_timing_graph(int num_sinks)
{

/* Checks the timing graph to see that: (1) all the tnodes have been put    *
 * into some level of the timing graph; */
 
	/* Addition error checks that need to be done but not yet implemented: (2) the number of primary inputs    *
 * to the timing graph is equal to the number of input pads + the number of *
 * constant generators; and (3) the number of sinks (nodes with no fanout)  *
 * equals the number of output pads + the number of flip flops.             */

    int num_tnodes_check, ilevel, error, num_p_inputs, num_p_outputs;

    error = 0;
    num_tnodes_check = 0;
    num_p_inputs = 0;
    num_p_outputs = 0;
	/* TODO: Rework error checks for I/Os*/
    
    for(ilevel = 0; ilevel < num_tnode_levels; ilevel++)
	num_tnodes_check += tnodes_at_level[ilevel].nelem;

    if(num_tnodes_check != num_tnodes)
	{
	    printf
		("Error in check_timing_graph: %d tnodes appear in the tnode level "
		 "structure.  Expected %d.\n", num_tnodes_check, num_tnodes);
	    printf("Check the netlist for combinational cycles.\n");
	    error++;
	}
	/* Todo: Add error checks that # of flip-flops, memories, and other
	         black boxes match # of sinks/sources*/

    if(error != 0)
	{
	    printf("Found %d Errors in the timing graph.  Aborting.\n",
		   error);
	    exit(1);
	}
}


float
print_critical_path_node(FILE * fp,
			 t_linked_int * critical_path_node)
{

/* Prints one tnode on the critical path out to fp. Returns the delay to    *
 * the next node.                                                           */

    int inode, iblk, inet, downstream_node;
	t_pb_graph_pin * pb_graph_pin;
    t_tnode_type type;
	static char *tnode_type_names[] = { "INPAD_SOURCE", "INPAD_OPIN", "OUTPAD_IPIN", "OUTPAD_SINK",
										"CB_IPIN", "CB_OPIN", "INTERMEDIATE_NODE", "PRIMITIVE_IPIN", "PRIMITIVE_OPIN", 
										"FF_IPIN", "FF_OPIN",
										"FF_SINK", "FF_SOURCE",
										"CONSTANT_GEN_SOURCE"};
  
    t_linked_int *next_crit_node;
    float Tdel;

    inode = critical_path_node->data;
    type = tnode[inode].type;
	iblk = tnode[inode].block;
	pb_graph_pin = tnode[inode].pb_graph_pin;


    fprintf(fp, "Node: %d  %s Block #%d (%s)\n", inode,
	    tnode_type_names[type], iblk, block[iblk].name);

	if(pb_graph_pin == NULL) {
		assert(type == INPAD_SOURCE || type == OUTPAD_SINK || type == FF_SOURCE || type == FF_SINK );
	}

	if(pb_graph_pin != NULL) {
		fprintf(fp, "Pin: %s.%s[%d] ", pb_graph_pin->parent_node->pb_type->name, 
			pb_graph_pin->port->name, pb_graph_pin->pin_number);
	}
    if(type != INPAD_SOURCE && type != OUTPAD_SINK)
	{
	    fprintf(fp, "\n");
	}

    fprintf(fp, "T_arr: %g  T_req: %g  ", tnode[inode].T_arr,
	    tnode[inode].T_req);

    next_crit_node = critical_path_node->next;
    if(next_crit_node != NULL)
	{
	    downstream_node = next_crit_node->data;
	    Tdel = tnode[downstream_node].T_arr - tnode[inode].T_arr;
	    fprintf(fp, "Tdel: %g\n", Tdel);
	}
    else
	{			/* last node, no Tdel. */
	    Tdel = 0.;
	    fprintf(fp, "\n");
	}
    
	if(type == CB_OPIN) {
		inet = block[iblk].pb->rr_graph[pb_graph_pin->pin_count_in_cluster].net_num;
		inet = vpack_to_clb_net_mapping[inet];
		fprintf(fp, "External-to-Block Net: #%d (%s).  Pins on net: %d.\n",
			inet, clb_net[inet].name, (clb_net[inet].num_sinks + 1));
	} else if (pb_graph_pin != NULL) {
		inet = block[iblk].pb->rr_graph[pb_graph_pin->pin_count_in_cluster].net_num;
		fprintf(fp, "Internal Net: #%d (%s).  Pins on net: %d.\n",
			inet, vpack_net[inet].name, (vpack_net[inet].num_sinks + 1));
	}


    fprintf(fp, "\n");
    return (Tdel);
}
