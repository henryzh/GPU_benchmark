#include <stdio.h>
#include <string.h>

#include "util.h"
#include "vpr_types.h"
#include "globals.h"
#include "path_delay.h"
#include "path_delay2.h"
#include "net_delay.h"
#include "vpr_utils.h"
#include <assert.h>
#include "read_xml_arch_file.h"

/****************** Timing graph Structure ************************************
 *                                                                            *
 * In the timing graph I create, input pads and constant generators have no   *
 * inputs; everything else has inputs.  Every input pad and output pad is     *
 * represented by two tnodes -- an input pin and an output pin.  For an input *
 * pad the input pin comes from off chip and has no fanin, while the output   *
 * pin drives outpads and/or CBs.  For output pads, the input node is driven *
 * by a CB or input pad, and the output node goes off chip and has no        *
 * fanout (out-edges).  I need two nodes to respresent things like pads       *
 * because I mark all delay on tedges, not on tnodes.                         *
 *                                                                            *
 * Every used (not OPEN) CB pin becomes a timing node.  As well, every used  *
 * subblock pin within a CB also becomes a timing node.  Unused (OPEN) pins  *
 * don't create any timing nodes. If a subblock is used in combinational mode *
 * (i.e. its clock pin is open), I just hook the subblock input tnodes to the *
 * subblock output tnode.  If the subblock is used in sequential mode, I      *
 * create two extra tnodes.  One is just the subblock clock pin, which is     *
 * connected to the subblock output.  This means that FFs don't generate      *
 * their output until their clock arrives.  For global clocks coming from an  *
 * input pad, the delay of the clock is 0, so the FFs generate their outputs  *
 * at T = 0, as usual.  For locally-generated or gated clocks, however, the   *
 * clock will arrive later, and the FF output will be generated later.  This  *
 * lets me properly model things like ripple counters and gated clocks.  The  *
 * other extra node is the FF storage node (i.e. a sink), which connects to   *
 * the subblock inputs and has no fanout.                                     *
 *                                                                            *
 * One other subblock that needs special attention is a constant generator.   *
 * This has no used inputs, but its output is used.  I create an extra tnode, *
 * a dummy input, in addition to the output pin tnode.  The dummy tnode has   *
 * no fanin.  Since constant generators really generate their outputs at T =  *
 * -infinity, I set the delay from the input tnode to the output to a large-  *
 * magnitude negative number.  This guarantees every block that needs the     *
 * output of a constant generator sees it available very early.               *
 *                                                                            *
 * For this routine to work properly, subblocks whose outputs are unused must *
 * be completely empty -- all their input pins and their clock pin must be    *
 * OPEN.  Check_netlist checks the input netlist to guarantee this -- don't   *
 * disable that check.                                                        *
 *                                                                            *
 * NB:  The discussion below is only relevant for circuits with multiple      *
 * clocks.  For circuits with a single clock, everything I do is exactly      *
 * correct.                                                                   *
 *                                                                            *
 * A note about how I handle FFs:  By hooking the clock pin up to the FF      *
 * output, I properly model the time at which the FF generates its output.    *
 * I don't do a completely rigorous job of modelling required arrival time at *
 * the FF input, however.  I assume every FF and outpad needs its input at    *
 * T = 0, which is when the earliest clock arrives.  This can be conservative *
 * -- a fuller analysis would be to do a fast path analysis of the clock      *
 * feeding each FF and subtract its earliest arrival time from the delay of   *
 * the D signal to the FF input.  This is too much work, so I'm not doing it. *
 * Alternatively, when one has N clocks, it might be better to just do N      *
 * separate timing analyses, with only signals from FFs clocked on clock i    *
 * being propagated forward on analysis i, and only FFs clocked on i being    *
 * considered as sinks.  This gives all the critical paths within clock       *
 * domains, but ignores interactions.  Instead, I assume all the clocks are   *
 * more-or-less synchronized (they might be gated or locally-generated, but   *
 * they all have the same frequency) and explore all interactions.  Tough to  *
 * say what's the better way.  Since multiple clocks aren't important for my  *
 * work, it's not worth bothering about much.                                 *
 *                                                                            *
 ******************************************************************************/

#define T_CONSTANT_GENERATOR -1000	/* Essentially -ve infinity */

/***************** Types local to this module ***************************/

enum e_subblock_pin_type
{ SUB_INPUT = 0, SUB_OUTPUT, SUB_CLOCK, NUM_SUB_PIN_TYPES };

/***************** Variables local to this module ***************************/

/* Variables for "chunking" the tedge memory.  If the head pointer is NULL, *
 * no timing graph exists now.                                              */

static struct s_linked_vptr *tedge_ch_list_head = NULL;
static int tedge_ch_bytes_avail = 0;
static char *tedge_ch_next_avail = NULL;

static struct s_net *timing_nets = NULL;
static int num_timing_nets = 0;

/***************** Subroutines local to this module *************************/

static float **alloc_net_slack();

static void compute_net_slacks(float **net_slack);

static void build_cb_tnodes(int iblk);

static void alloc_and_load_tnodes(t_timing_inf timing_inf);

static void alloc_and_load_tnodes_from_prepacked_netlist(float block_delay, float inter_cluster_net_delay);

static void load_tnode(INP t_pb_graph_pin *pb_graph_pin, INP int iblock, INOUTP int *inode, INP t_timing_inf timing_inf);

static void normalize_costs(float t_crit, long max_critical_input_paths, long max_critical_output_paths);

static void print_primitive_as_blif (FILE *fpout, int iblk);



/********************* Subroutine definitions *******************************/


float **
alloc_and_load_timing_graph(t_timing_inf timing_inf)
{

/* This routine builds the graph used for timing analysis.  Every cb pin is a 
 * timing node (tnode).  The connectivity between pins is *
 * represented by timing edges (tedges).  All delay is marked on edges, not *
 * on nodes.  This routine returns an array that will store slack values:   *
 * net_slack[0..num_nets-1][1..num_pins-1].                                 */
/* The are below are valid only for CBs, not pads.                  */
    
/* Array for mapping from a pin on a block to a tnode index. For pads, only *
 * the first two pin locations are used (input to pad is first, output of   *
 * pad is second).  For CLBs, all OPEN pins on the cb have their mapping   *
 * set to OPEN so I won't use it by mistake.                                */

    int num_sinks;
    float **net_slack;		/* [0..num_nets-1][1..num_pins-1]. */

/************* End of variable declarations ********************************/

    if(tedge_ch_list_head != NULL)
	{
	    printf("Error in alloc_and_load_timing_graph:\n"
		   "\tAn old timing graph still exists.\n");
	    exit(1);
	}
	num_timing_nets = num_nets;
	timing_nets = clb_net;

	alloc_and_load_tnodes(timing_inf);

    num_sinks = alloc_and_load_timing_graph_levels();

	#ifdef CREATE_ECHO_FILES
		print_timing_graph("initial_timing_graph.echo");
	#endif

	check_timing_graph(num_sinks);
	
    net_slack = alloc_net_slack();

	return (net_slack);
}


float** alloc_and_load_pre_packing_timing_graph(float block_delay, float inter_cluster_net_delay, t_model *models)
{

/* This routine builds the graph used for timing analysis.  Every technology mapped netlist pin is a 
 * timing node (tnode).  The connectivity between pins is *
 * represented by timing edges (tedges).  All delay is marked on edges, not *
 * on nodes.  This routine returns an array that will store slack values:   *
 * net_slack[0..num_nets-1][1..num_pins-1].                                 */
/* The are below are valid only for CBs, not pads.                  */
    
/* Array for mapping from a pin on a block to a tnode index. For pads, only *
 * the first two pin locations are used (input to pad is first, output of   *
 * pad is second).  For CLBs, all OPEN pins on the cb have their mapping   *
 * set to OPEN so I won't use it by mistake.                                */

    int num_sinks;

	float **net_slack;

/************* End of variable declarations ********************************/

    if(tedge_ch_list_head != NULL)
	{
	    printf("Error in alloc_and_load_timing_graph:\n"
		   "\tAn old timing graph still exists.\n");
	    exit(1);
	}

	num_timing_nets = num_logical_nets;
	timing_nets = vpack_net;

	alloc_and_load_tnodes_from_prepacked_netlist(block_delay, inter_cluster_net_delay);

    num_sinks = alloc_and_load_timing_graph_levels();

	net_slack = alloc_net_slack();

	#ifdef CREATE_ECHO_FILES
		print_timing_graph("pre_packing_timing_graph.echo");
		print_timing_graph_as_blif("pre_packing_timing_graph_as_blif.blif", models);
	#endif

	check_timing_graph(num_sinks);

	return net_slack;
}


static float **
alloc_net_slack()
{

/* Allocates the net_slack structure.  Chunk allocated to save space.      */

    float **net_slack;		/* [0..num_nets-1][1..num_pins-1]  */
    int inet, j;

    net_slack = (float **)my_malloc(num_timing_nets * sizeof(float *));

    for(inet = 0; inet < num_timing_nets; inet++)
	{
	    net_slack[inet] = (float *)my_chunk_malloc((timing_nets[inet].num_sinks + 1) *
					 sizeof(float), &tedge_ch_list_head,
					 &tedge_ch_bytes_avail,
					 &tedge_ch_next_avail);
		for(j = 0; j <= timing_nets[inet].num_sinks; j++) {
			net_slack[inet][j] = UNDEFINED;
		}
	}

    return (net_slack);
}

void
load_timing_graph_net_delays(float **net_delay)
{

/* Sets the delays of the inter-CLB nets to the values specified by          *
 * net_delay[0..num_nets-1][1..num_pins-1].  These net delays should have    *
 * been allocated and loaded with the net_delay routines.  This routine      *
 * marks the corresponding edges in the timing graph with the proper delay.  */

    int inet, ipin, inode;
    t_tedge *tedge;

    for(inet = 0; inet < num_timing_nets; inet++)
	{
	    inode = net_to_driver_tnode[inet];
	    tedge = tnode[inode].out_edges;

/* Note that the edges of a tnode corresponding to a CLB or INPAD opin must  *
 * be in the same order as the pins of the net driven by the tnode.          */

	    for(ipin = 1; ipin < (timing_nets[inet].num_sinks + 1); ipin++)
		tedge[ipin - 1].Tdel = net_delay[inet][ipin];
	}
}


void
free_timing_graph(float **net_slack)
{

/* Frees the timing graph data. */

    if(tedge_ch_list_head == NULL)
	{
	    printf("Error in free_timing_graph: No timing graph to free.\n");
	    exit(1);
	}

    free_chunk_memory(tedge_ch_list_head);
    free(tnode);
    free(net_to_driver_tnode);
    free_ivec_vector(tnodes_at_level, 0, num_tnode_levels - 1);
    free(net_slack);

    tedge_ch_list_head = NULL;
    tedge_ch_bytes_avail = 0;
    tedge_ch_next_avail = NULL;

    tnode = NULL;
    num_tnodes = 0;
    net_to_driver_tnode = NULL;
    tnodes_at_level = NULL;
    num_tnode_levels = 0;
}


void
print_net_slack(char *fname,
		float **net_slack)
{

/* Prints the net slacks into a file.                                     */

    int inet, ipin;
    FILE *fp;

    fp = my_fopen(fname, "w", 0);

    fprintf(fp, "Net #\tSlacks\n\n");

    for(inet = 0; inet < num_timing_nets; inet++)
	{
	    fprintf(fp, "%5d", inet);
	    for(ipin = 1; ipin < (timing_nets[inet].num_sinks + 1); ipin++)
		{
		    fprintf(fp, "\t%g", net_slack[inet][ipin]);
		}
	    fprintf(fp, "\n");
	}
}

/* Count # of tnodes, allocates space, and loads the tnodes and its associated edges */
static void alloc_and_load_tnodes(t_timing_inf timing_inf) {
	int i, j, k;
	int inode;
	int num_nodes_in_block;
	int count;
	int iblock, irr_node;
	int inet, dport, dpin, dblock, dnode;
	int normalized_pin, normalization;
	t_pb_graph_pin *ipb_graph_pin;
	t_rr_node *local_rr_graph, *d_rr_graph;

	net_to_driver_tnode = my_malloc(num_timing_nets * sizeof(int));

	for(i = 0; i < num_timing_nets; i++) {
		net_to_driver_tnode[i] = OPEN;
	}

	/* allocate space for tnodes */
	num_tnodes = 0;
	for(i = 0; i < num_blocks; i++) {
		num_nodes_in_block = 0;
		for(j = 0; j < block[i].pb->pb_graph_node->total_pb_pins; j++) {
			if(block[i].pb->rr_graph[j].net_num != OPEN) {
				if(block[i].pb->rr_graph[j].pb_graph_pin->type == PB_PIN_INPAD ||
				   block[i].pb->rr_graph[j].pb_graph_pin->type == PB_PIN_OUTPAD ||
				   block[i].pb->rr_graph[j].pb_graph_pin->type == PB_PIN_SEQUENTIAL) {
					num_nodes_in_block += 2;
				} else {
					num_nodes_in_block++;
				}
			}
		}
		num_tnodes += num_nodes_in_block;
	}
	tnode = my_calloc(num_tnodes, sizeof(t_tnode));

	/* load tnodes with all info except edge info */
	/* populate tnode lookups for edge info */
	inode = 0;
	for(i = 0; i < num_blocks; i++) {
		for(j = 0; j < block[i].pb->pb_graph_node->total_pb_pins; j++) {
			if(block[i].pb->rr_graph[j].net_num != OPEN) {
				assert(tnode[inode].pb_graph_pin == NULL);
				load_tnode(block[i].pb->rr_graph[j].pb_graph_pin, i, &inode, timing_inf);			
			}
		}
	}
	assert(inode == num_tnodes);

	/* load edge delays */
	for(i = 0; i < num_tnodes; i++) {
		/* 3 primary scenarios for edge delays
		1.  Point-to-point delays inside block
		2.  
		*/
		count = 0;
		iblock = tnode[i].block;
		switch (tnode[i].type) {
			case INPAD_OPIN:
			case INTERMEDIATE_NODE:
			case PRIMITIVE_OPIN:
			case FF_OPIN:
			case CB_IPIN:
				/* fanout is determined by intra-cluster connections */
				/* Allocate space for edges  */
				irr_node = tnode[i].pb_graph_pin->pin_count_in_cluster;
				local_rr_graph = block[iblock].pb->rr_graph;
				ipb_graph_pin = local_rr_graph[irr_node].pb_graph_pin;

				if(ipb_graph_pin->parent_node->pb_type->max_internal_delay != UNDEFINED) {
					if(pb_max_internal_delay == UNDEFINED) {
						pb_max_internal_delay = ipb_graph_pin->parent_node->pb_type->max_internal_delay;
						pbtype_max_internal_delay = ipb_graph_pin->parent_node->pb_type;
					} else if(pb_max_internal_delay < ipb_graph_pin->parent_node->pb_type->max_internal_delay) {
						pb_max_internal_delay = ipb_graph_pin->parent_node->pb_type->max_internal_delay;
						pbtype_max_internal_delay = ipb_graph_pin->parent_node->pb_type;
					}
				}

				for(j = 0; j < block[iblock].pb->rr_graph[irr_node].num_edges; j++) {
					dnode = local_rr_graph[irr_node].edges[j];
					if((local_rr_graph[dnode].prev_node == irr_node) && (j == local_rr_graph[dnode].prev_edge)) {
						count++;
					}
				}
				assert(count > 0);
				tnode[i].num_edges = count;
				tnode[i].out_edges = (t_tedge *) my_chunk_malloc(count *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);

				/* Load edges */
				count = 0;
				for(j = 0; j < local_rr_graph[irr_node].num_edges; j++) {
					dnode = local_rr_graph[irr_node].edges[j];
					if((local_rr_graph[dnode].prev_node == irr_node) && (j == local_rr_graph[dnode].prev_edge)) {
						assert((ipb_graph_pin->output_edges[j]->num_output_pins == 1) &&
							(local_rr_graph[ipb_graph_pin->output_edges[j]->output_pins[0]->pin_count_in_cluster].net_num == local_rr_graph[irr_node].net_num));


						tnode[i].out_edges[count].Tdel = ipb_graph_pin->output_edges[j]->delay_max;
						tnode[i].out_edges[count].to_node = local_rr_graph[dnode].tnode->index;
						
						if(vpack_net[local_rr_graph[irr_node].net_num].is_const_gen == TRUE && tnode[i].type == PRIMITIVE_OPIN) {
							tnode[i].out_edges[count].Tdel = T_CONSTANT_GENERATOR;
							tnode[i].type = CONSTANT_GEN_SOURCE;
						}
						
						count++;
					}
				}
				assert(count > 0);

				break;
			case PRIMITIVE_IPIN:
				/* Pin info comes from pb_graph block delays
				*/
				irr_node = tnode[i].pb_graph_pin->pin_count_in_cluster;
				local_rr_graph = block[iblock].pb->rr_graph;
				ipb_graph_pin = local_rr_graph[irr_node].pb_graph_pin;
				tnode[i].num_edges = ipb_graph_pin->num_pin_timing;
				tnode[i].out_edges = (t_tedge *) my_chunk_malloc(ipb_graph_pin->num_pin_timing *
												sizeof(t_tedge),
												&tedge_ch_list_head,
												&tedge_ch_bytes_avail,
												&tedge_ch_next_avail);					
				k = 0;

				for(j = 0; j < tnode[i].num_edges; j++) {
					/* Some outpins aren't used, ignore these.  Only consider output pins that are used */
					if(local_rr_graph[ipb_graph_pin->pin_timing[j]->pin_count_in_cluster].net_num != OPEN) {
						tnode[i].out_edges[k].Tdel = ipb_graph_pin->pin_timing_del_max[j];
						tnode[i].out_edges[k].to_node = local_rr_graph[ipb_graph_pin->pin_timing[j]->pin_count_in_cluster].tnode->index;
						assert(tnode[i].out_edges[k].to_node != OPEN);
						k++;
					}
				}
				tnode[i].num_edges -= (j - k); /* remove unused edges */
				if(tnode[i].num_edges == 0) {
					printf(ERRTAG "No timing information for pin %s.%s[%d]\n", tnode[i].pb_graph_pin->parent_node->pb_type->name, tnode[i].pb_graph_pin->port->name,tnode[i].pb_graph_pin->pin_number);
					exit(1);
				}
				break;
			case CB_OPIN:
				/* load up net info */
				irr_node = tnode[i].pb_graph_pin->pin_count_in_cluster;
				local_rr_graph = block[iblock].pb->rr_graph;
				ipb_graph_pin = local_rr_graph[irr_node].pb_graph_pin;
				assert(local_rr_graph[irr_node].net_num != OPEN);
				inet = vpack_to_clb_net_mapping[local_rr_graph[irr_node].net_num];
				assert(inet != OPEN);
				net_to_driver_tnode[inet] = i;
				tnode[i].num_edges = clb_net[inet].num_sinks;
				tnode[i].out_edges = (t_tedge *) my_chunk_malloc(clb_net[inet].num_sinks *
												sizeof(t_tedge),
												&tedge_ch_list_head,
												&tedge_ch_bytes_avail,
												&tedge_ch_next_avail);					
				for(j = 1; j <= clb_net[inet].num_sinks; j++) {
					dblock = clb_net[inet].node_block[j];
					normalization = block[dblock].type->num_pins / block[dblock].type->capacity;
					normalized_pin = clb_net[inet].node_block_pin[j] % normalization;
					d_rr_graph = block[dblock].pb->rr_graph;
					dpin = OPEN;
					dport = OPEN;
					count = 0;

					for(k = 0; k < block[dblock].pb->pb_graph_node->num_input_ports && dpin == OPEN; k++) {
						if(normalized_pin >= count && (count + block[dblock].pb->pb_graph_node->num_input_pins[k] > normalized_pin)) {
							dpin = normalized_pin - count;
							dport = k;
							break;
						}
						count += block[dblock].pb->pb_graph_node->num_input_pins[k];
					}
					if(dpin == OPEN) {
						for(k = 0; k < block[dblock].pb->pb_graph_node->num_output_ports && dpin == OPEN; k++) {
							count += block[dblock].pb->pb_graph_node->num_output_pins[k];
						}
						for(k = 0; k < block[dblock].pb->pb_graph_node->num_clock_ports && dpin == OPEN; k++) {
							if(normalized_pin >= count && (count + block[dblock].pb->pb_graph_node->num_clock_pins[k] > normalized_pin)) {
								dpin = normalized_pin - count;
								dport = k;								
							}
							count += block[dblock].pb->pb_graph_node->num_clock_pins[k];
						}
						assert(dpin != OPEN);
						assert(inet == vpack_to_clb_net_mapping[d_rr_graph[block[dblock].pb->pb_graph_node->clock_pins[dport][dpin].pin_count_in_cluster].net_num]);						
						tnode[i].out_edges[j-1].to_node = d_rr_graph[block[dblock].pb->pb_graph_node->clock_pins[dport][dpin].pin_count_in_cluster].tnode->index;
					} else {
						assert(dpin != OPEN);
						assert(inet == vpack_to_clb_net_mapping[d_rr_graph[block[dblock].pb->pb_graph_node->input_pins[dport][dpin].pin_count_in_cluster].net_num]);
						/* delays are assigned post routing */
						tnode[i].out_edges[j-1].to_node = d_rr_graph[block[dblock].pb->pb_graph_node->input_pins[dport][dpin].pin_count_in_cluster].tnode->index;
					}
					assert(inet != OPEN);
				}
				break;
			case OUTPAD_IPIN:
			case INPAD_SOURCE:
			case OUTPAD_SINK:
			case FF_SINK:
			case FF_SOURCE:
			case FF_IPIN:
				break;
			default:
				printf(ERRTAG "Consistency check failed: Unknown tnode type %d\n", tnode[i].type);
				assert(0);
			break;
		}
	}
}

/* Allocate timing graph for pre packed netlist
  Count number of tnodes first
  Then connect up tnodes with edges
*/
static void alloc_and_load_tnodes_from_prepacked_netlist(float block_delay, float inter_cluster_net_delay) {
	int i, j, k;
	t_model *model;
	t_model_ports *model_port;
	int inode, inet, iblock;
	int incr;
	int count;

	net_to_driver_tnode = my_malloc(num_logical_nets * sizeof(int));

	for(i = 0; i < num_logical_nets; i++) {
		net_to_driver_tnode[i] = OPEN;
	}

	
	/* allocate space for tnodes */
	num_tnodes = 0;
	for(i = 0; i < num_logical_blocks; i++) {
		model = logical_block[i].model;
		logical_block[i].clock_net_tnode = NULL;
		if(logical_block[i].type == VPACK_INPAD) {
			logical_block[i].output_net_tnodes = my_calloc(1, sizeof(t_tnode**));
			num_tnodes += 2;
		} else if(logical_block[i].type == VPACK_OUTPAD) {
			logical_block[i].input_net_tnodes = my_calloc(1, sizeof(t_tnode**));
			num_tnodes += 2;
		} else {		
			if(logical_block[i].clock_net == OPEN) {
				incr = 1;
			} else {
				incr = 2;
			}
			j = 0;
			model_port = model->inputs;
			while(model_port) {
				if(model_port->is_clock == FALSE) {
					for(k = 0; k < model_port->size; k++) {
						if(logical_block[i].input_nets[j][k] != OPEN) {
							num_tnodes += incr;
						}
					}
					j++;
				} else {
					num_tnodes++;
				}				
				model_port = model_port->next;
			}
			logical_block[i].input_net_tnodes = my_calloc(j, sizeof(t_tnode**));
			
			j = 0;
			model_port = model->outputs;
			while(model_port) {
				for(k = 0; k < model_port->size; k++) {
					if(logical_block[i].output_nets[j][k] != OPEN) {
						num_tnodes += incr;
					}
				}
				j++;
				model_port = model_port->next;
			}
			logical_block[i].output_net_tnodes = my_calloc(j, sizeof(t_tnode**));
		}
	}
	tnode = my_calloc(num_tnodes, sizeof(t_tnode));
	for(i = 0; i < num_tnodes; i++) {
		tnode[i].index = i;
	}

	/* load tnodes, alloc edges for tnodes, load all known tnodes */
	inode = 0;
	for(i = 0; i < num_logical_blocks; i++) {
		model = logical_block[i].model;
		if(logical_block[i].type == VPACK_INPAD) {
			logical_block[i].output_net_tnodes[0] = my_calloc(1, sizeof(t_tnode*));
			logical_block[i].output_net_tnodes[0][0] = &tnode[inode];
			net_to_driver_tnode[logical_block[i].output_nets[0][0]] = inode;
			tnode[inode].model_pin = 0;
			tnode[inode].model_port = 0;
			tnode[inode].block = i;
			tnode[inode].type = INPAD_OPIN;
			
			tnode[inode].num_edges = vpack_net[logical_block[i].output_nets[0][0]].num_sinks;
			tnode[inode].out_edges = 
								(t_tedge *) my_chunk_malloc(tnode[inode].num_edges *
												sizeof(t_tedge),
												&tedge_ch_list_head,
												&tedge_ch_bytes_avail,
												&tedge_ch_next_avail);
			tnode[inode + 1].num_edges = 1;
			tnode[inode + 1].out_edges = 
				(t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
			tnode[inode + 1].out_edges->Tdel = 0;
			tnode[inode + 1].out_edges->to_node = inode;
			tnode[inode + 1].T_req = 0;
			tnode[inode + 1].T_arr = 0;
			tnode[inode + 1].type = INPAD_SOURCE;
			tnode[inode + 1].block = i;
			inode += 2;
		} else if (logical_block[i].type == VPACK_OUTPAD) {
			logical_block[i].input_net_tnodes[0] = my_calloc(1, sizeof(t_tnode*));
			logical_block[i].input_net_tnodes[0][0] = &tnode[inode];
			tnode[inode].model_pin = 0;
			tnode[inode].model_port = 0;
			tnode[inode].block = i;
			tnode[inode].type = OUTPAD_IPIN;
			tnode[inode].num_edges = 1;
			tnode[inode].out_edges = 
				(t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
			tnode[inode].out_edges->Tdel = 0;
			tnode[inode].out_edges->to_node = inode + 1;
			tnode[inode + 1].T_req = 0;
			tnode[inode + 1].T_arr = 0;
			tnode[inode + 1].type = OUTPAD_SINK;
			tnode[inode + 1].block = i;
			tnode[inode + 1].num_edges = 0;
			tnode[inode + 1].out_edges = NULL;
			tnode[inode + 1].index = inode + 1;
			inode += 2;
		} else {		
			j = 0;
			model_port = model->outputs;
			count = 0;
			while(model_port) {
				logical_block[i].output_net_tnodes[j] = my_calloc(model_port->size, sizeof(t_tnode*));
				for(k = 0; k < model_port->size; k++) {
					if(logical_block[i].output_nets[j][k] != OPEN) {
						count++;
						tnode[inode].model_pin = k;
						tnode[inode].model_port = j;
						tnode[inode].block = i;
						net_to_driver_tnode[logical_block[i].output_nets[j][k]] = inode;
						logical_block[i].output_net_tnodes[j][k] = &tnode[inode];
							
						tnode[inode].num_edges = vpack_net[logical_block[i].output_nets[j][k]].num_sinks;
						tnode[inode].out_edges = 
								(t_tedge *) my_chunk_malloc(tnode[inode].num_edges *
												sizeof(t_tedge),
												&tedge_ch_list_head,
												&tedge_ch_bytes_avail,
												&tedge_ch_next_avail);
						
						if (logical_block[i].clock_net == OPEN) {
							tnode[inode].type = PRIMITIVE_OPIN;
							inode++;
						} else {
							tnode[inode].type = FF_OPIN;
							tnode[inode + 1].num_edges = 1;
							tnode[inode + 1].out_edges = 
								(t_tedge *) my_chunk_malloc(1 *
												sizeof(t_tedge),
												&tedge_ch_list_head,
												&tedge_ch_bytes_avail,
												&tedge_ch_next_avail);
							tnode[inode + 1].out_edges->to_node = inode;
							tnode[inode + 1].out_edges->Tdel = 0;
							tnode[inode + 1].type = FF_SOURCE;
							tnode[inode + 1].block = i;
							inode += 2;
						}
					}
				}
				j++;
				model_port = model_port->next;
			}

			j = 0;			
			model_port = model->inputs;
			while(model_port) {
				if(model_port->is_clock == FALSE) {
					logical_block[i].input_net_tnodes[j] = my_calloc(model_port->size, sizeof(t_tnode*));
					for(k = 0; k < model_port->size; k++) {
						if(logical_block[i].input_nets[j][k] != OPEN) {
							tnode[inode].model_pin = k;
							tnode[inode].model_port = j;
							tnode[inode].block = i;
							logical_block[i].input_net_tnodes[j][k] = &tnode[inode];
								
							if (logical_block[i].clock_net == OPEN) {
								tnode[inode].type = PRIMITIVE_IPIN;
								tnode[inode].out_edges = 
										(t_tedge *) my_chunk_malloc(count *
														sizeof(t_tedge),
														&tedge_ch_list_head,
														&tedge_ch_bytes_avail,
														&tedge_ch_next_avail);
								tnode[inode].num_edges = count;
								inode++;
							} else {
								tnode[inode].type = FF_IPIN;
								tnode[inode].num_edges = 1;
								tnode[inode].out_edges = 
									(t_tedge *) my_chunk_malloc(1 *
													sizeof(t_tedge),
													&tedge_ch_list_head,
													&tedge_ch_bytes_avail,
													&tedge_ch_next_avail);
								tnode[inode].out_edges->to_node = inode + 1;
								tnode[inode].out_edges->Tdel = 0;
								tnode[inode + 1].type = FF_SINK;
								tnode[inode + 1].num_edges = 0;
								tnode[inode + 1].out_edges = NULL;
								inode += 2;
							}
						}
					}					
					j++;
				} else {
					if(logical_block[i].clock_net != OPEN) {
						assert(logical_block[i].clock_net_tnode == NULL);
						logical_block[i].clock_net_tnode = &tnode[inode];
						tnode[inode].block = i;
						tnode[inode].model_pin = 0;
						tnode[inode].model_port = 0;
						tnode[inode].num_edges = 0;
						tnode[inode].out_edges = NULL;
						tnode[inode].type = FF_SINK;
						inode++;
					}
				}
				model_port = model_port->next;
			}
		}
	}
	assert(inode == num_tnodes);

	/* load edge delays */
	for(i = 0; i < num_tnodes; i++) {
		/* 3 primary scenarios for edge delays
		1.  Point-to-point delays inside block
		2.  
		*/
		count = 0;
		iblock = tnode[i].block;
		switch (tnode[i].type) {
			case INPAD_OPIN:
			case PRIMITIVE_OPIN:
			case FF_OPIN:
				/* fanout is determined by intra-cluster connections */
				/* Allocate space for edges  */
				inet = logical_block[tnode[i].block].output_nets[tnode[i].model_port][tnode[i].model_pin];
				assert(inet != OPEN);
		
				for(j = 1; j <= vpack_net[inet].num_sinks; j++) {
					if(vpack_net[inet].is_const_gen) {
						tnode[i].out_edges[j - 1].Tdel = T_CONSTANT_GENERATOR;
						tnode[i].type = CONSTANT_GEN_SOURCE;
					} else {
						tnode[i].out_edges[j - 1].Tdel = inter_cluster_net_delay;						
					}
					assert(logical_block[vpack_net[inet].node_block[j]].input_net_tnodes[vpack_net[inet].node_block_port[j]][vpack_net[inet].node_block_pin[j]] != NULL);
					if(vpack_net[inet].is_global) {
						assert(logical_block[vpack_net[inet].node_block[j]].clock_net == inet);
						tnode[i].out_edges[j - 1].to_node = logical_block[vpack_net[inet].node_block[j]].clock_net_tnode->index;
					} else {
						tnode[i].out_edges[j - 1].to_node = logical_block[vpack_net[inet].node_block[j]].input_net_tnodes[vpack_net[inet].node_block_port[j]][vpack_net[inet].node_block_pin[j]]->index;
					}
				}
				assert(tnode[i].num_edges == vpack_net[inet].num_sinks);
				break;
			case PRIMITIVE_IPIN:
				model_port = logical_block[iblock].model->outputs;
				count = 0;
				j = 0;
				while(model_port) {
					for(k = 0; k < model_port->size; k++) {
						if(logical_block[iblock].output_nets[j][k] != OPEN) {
							tnode[i].out_edges[count].Tdel = block_delay;
							tnode[i].out_edges[count].to_node = logical_block[iblock].output_net_tnodes[j][k]->index;
							count++;							
						}
						else {
							assert(logical_block[iblock].output_net_tnodes[j][k] == NULL);
						}
					}
					j++;
					model_port = model_port->next;
				}
				assert(count == tnode[i].num_edges);
				break;
			case OUTPAD_IPIN:
			case INPAD_SOURCE:
			case OUTPAD_SINK:
			case FF_SINK:
			case FF_SOURCE:
			case FF_IPIN:
				break;
			default:
				printf(ERRTAG "Consistency check failed: Unknown tnode type %d\n", tnode[i].type);
				assert(0);
			break;
		}
	}

	for(i = 0; i < num_logical_nets; i++) {
		assert(net_to_driver_tnode[i] != OPEN);
	}
}

static void load_tnode(INP t_pb_graph_pin *pb_graph_pin, INP int iblock, INOUTP int *inode, INP t_timing_inf timing_inf) {
	int i;
	i = *inode;
	tnode[i].pb_graph_pin = pb_graph_pin;
	tnode[i].block = iblock;
	tnode[i].index = i;
	block[iblock].pb->rr_graph[pb_graph_pin->pin_count_in_cluster].tnode = &tnode[i];
	if(tnode[i].pb_graph_pin->parent_node->pb_type->blif_model == NULL) {
		assert(tnode[i].pb_graph_pin->type == PB_PIN_NORMAL);
		if(tnode[i].pb_graph_pin->parent_node->parent_pb_graph_node == NULL) {
			if(tnode[i].pb_graph_pin->port->type == IN_PORT) {
				tnode[i].type = CB_IPIN;				
			} else {
				assert(tnode[i].pb_graph_pin->port->type == OUT_PORT);
				tnode[i].type = CB_OPIN;
			}
		} else {
			tnode[i].type = INTERMEDIATE_NODE;
		}
	} else {
		if(tnode[i].pb_graph_pin->type == PB_PIN_INPAD) {
			assert(tnode[i].pb_graph_pin->port->type == OUT_PORT);
			tnode[i].type = INPAD_OPIN;
			tnode[i + 1].num_edges = 1;
			tnode[i + 1].out_edges = 
				(t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
			tnode[i + 1].out_edges->Tdel = 0;
			tnode[i + 1].out_edges->to_node = i;
			tnode[i + 1].pb_graph_pin = NULL;
			tnode[i + 1].T_req = 0;
			tnode[i + 1].T_arr = 0;
			tnode[i + 1].type = INPAD_SOURCE;
			tnode[i + 1].block = iblock;
			tnode[i + 1].index = i + 1;
			(*inode)++;
		} else if(tnode[i].pb_graph_pin->type == PB_PIN_OUTPAD) {
			assert(tnode[i].pb_graph_pin->port->type == IN_PORT);
			tnode[i].type = OUTPAD_IPIN;
			tnode[i].num_edges = 1;
			tnode[i].out_edges = 
				(t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
			tnode[i].out_edges->Tdel = 0;
			tnode[i].out_edges->to_node = i + 1;
			tnode[i + 1].pb_graph_pin = NULL;
			tnode[i + 1].T_req = 0;
			tnode[i + 1].T_arr = 0;
			tnode[i + 1].type = OUTPAD_SINK;
			tnode[i + 1].block = iblock;
			tnode[i + 1].num_edges = 0;
			tnode[i + 1].out_edges = NULL;
			tnode[i + 1].index = i + 1;
			(*inode)++;
		} else if(tnode[i].pb_graph_pin->type == PB_PIN_SEQUENTIAL) {
			if(tnode[i].pb_graph_pin->port->type == IN_PORT) {
				tnode[i].type = FF_IPIN;
				tnode[i].num_edges = 1;
				tnode[i].out_edges = (t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
				tnode[i].out_edges->Tdel = pb_graph_pin->tsu_tco;
				tnode[i].out_edges->to_node = i + 1;
				tnode[i + 1].pb_graph_pin = NULL;
				tnode[i + 1].T_req = 0;
				tnode[i + 1].T_arr = 0;
				tnode[i + 1].type = FF_SINK;
				tnode[i + 1].block = iblock;
				tnode[i + 1].num_edges = 0;
				tnode[i + 1].out_edges = NULL;
				tnode[i + 1].index = i + 1;
			} else {
				assert(tnode[i].pb_graph_pin->port->type == OUT_PORT);
				tnode[i].type = FF_OPIN;
				tnode[i + 1].num_edges = 1;
				tnode[i + 1].out_edges = (t_tedge *) my_chunk_malloc(1 *
							    sizeof(t_tedge),
							    &tedge_ch_list_head,
							    &tedge_ch_bytes_avail,
							    &tedge_ch_next_avail);
				tnode[i + 1].out_edges->Tdel = pb_graph_pin->tsu_tco;
				tnode[i + 1].out_edges->to_node = i;
				tnode[i + 1].pb_graph_pin = NULL;
				tnode[i + 1].T_req = 0;
				tnode[i + 1].T_arr = 0;
				tnode[i + 1].type = FF_SOURCE;
				tnode[i + 1].block = iblock;
				tnode[i + 1].index = i + 1;
			}
			(*inode)++;
		} else if (tnode[i].pb_graph_pin->type == PB_PIN_CLOCK) {
			tnode[i].type = FF_SINK;
			tnode[i].num_edges = 0;
			tnode[i].out_edges = NULL;				
		} else {
			if(tnode[i].pb_graph_pin->port->type == IN_PORT) {
				assert(tnode[i].pb_graph_pin->type == PB_PIN_TERMINAL);
				tnode[i].type = PRIMITIVE_IPIN;
			} else {
				assert(tnode[i].pb_graph_pin->port->type == OUT_PORT);
				assert(tnode[i].pb_graph_pin->type == PB_PIN_TERMINAL);
				tnode[i].type = PRIMITIVE_OPIN;
			}
		}
	}
	(*inode)++;
}

void
print_timing_graph(char *fname)
{

/* Prints the timing graph into a file.           */

    FILE *fp;
    int inode, iedge, ilevel, i;
    t_tedge *tedge;
    t_tnode_type itype;
    char *tnode_type_names[] = { "INPAD_SOURCE", "INPAD_OPIN", "OUTPAD_IPIN", 
		"OUTPAD_SINK", "CB_IPIN", "CB_OPIN", "INTERMEDIATE_NODE", "PRIMITIVE_IPIN", "PRIMITIVE_OPIN", 
		"FF_IPIN", "FF_OPIN",
		"FF_SINK", "FF_SOURCE",
		"CONSTANT_GEN_SOURCE"
    };


    fp = my_fopen(fname, "w", 0);

    fprintf(fp, "num_tnodes: %d\n", num_tnodes);
    fprintf(fp, "Node #\tType\t\tipin\tiblk\t# edges\t"
	    "Edges (to_node, Tdel)\n\n");

	
    for(inode = 0; inode < num_tnodes; inode++)
	{
	    fprintf(fp, "%d\t", inode);

	    itype = tnode[inode].type;
	    fprintf(fp, "%-15.15s\t", tnode_type_names[itype]);

		if(tnode[inode].pb_graph_pin != NULL) {
			fprintf(fp, "%d\t%d\t", tnode[inode].pb_graph_pin->pin_count_in_cluster,
		    tnode[inode].block);
		} else {
			fprintf(fp, "%d\t",  tnode[inode].block);
		}

	    fprintf(fp, "%d\t", tnode[inode].num_edges);

		
	    tedge = tnode[inode].out_edges;
		for(iedge = 0; iedge < tnode[inode].num_edges; iedge++)
		{
			fprintf(fp, "\t(%4d,%7.3g)", tedge[iedge].to_node,
			    tedge[iedge].Tdel);
		}
	    fprintf(fp, "\n");
	}

    fprintf(fp, "\n\nnum_tnode_levels: %d\n", num_tnode_levels);

    for(ilevel = 0; ilevel < num_tnode_levels; ilevel++)
	{
	    fprintf(fp, "\n\nLevel: %d  Num_nodes: %d\nNodes:", ilevel,
		    tnodes_at_level[ilevel].nelem);
	    for(i = 0; i < tnodes_at_level[ilevel].nelem; i++)
		fprintf(fp, "\t%d", tnodes_at_level[ilevel].list[i]);
	}

    fprintf(fp, "\n");
    fprintf(fp, "\n\nNet #\tNet_to_driver_tnode\n");

    for(i = 0; i < num_nets; i++)
	fprintf(fp, "%4d\t%6d\n", i, net_to_driver_tnode[i]);

    fprintf(fp, "\n\nNode #\t\tT_arr\t\tT_req\n\n");

	for(inode = 0; inode < num_tnodes; inode++) {
		fprintf(fp, "%d\t%12g\t%12g\n", inode, tnode[inode].T_arr,
			tnode[inode].T_req);
	}

    fclose(fp);
}


float
load_net_slack(float **net_slack,
	       float target_cycle_time)
{

/* Determines the slack of every source-sink pair of block pins in the      *
 * circuit.  The timing graph must have already been built.  target_cycle_  *
 * time is the target delay for the circuit -- if 0, the target_cycle_time  *
 * is set to the critical path found in the timing graph.  This routine     *
 * loads net_slack, and returns the current critical path delay.            */

    float T_crit, T_arr, Tdel, T_cycle, T_req;
    int inode, ilevel, num_at_level, i, num_edges, iedge, to_node;
	int total;
    t_tedge *tedge;

/* Reset all arrival times to -ve infinity.  Can't just set to zero or the   *
 * constant propagation (constant generators work at -ve infinity) won't     *
 * work.                                                                     */

	long max_critical_input_paths = 0;
	long max_critical_output_paths = 0;

    for(inode = 0; inode < num_tnodes; inode++)
	tnode[inode].T_arr = T_CONSTANT_GENERATOR;

/* Compute all arrival times with a breadth-first analysis from inputs to   *
 * outputs.  Also compute critical path (T_crit).                           */

    T_crit = 0.;

/* Primary inputs arrive at T = 0. */

    num_at_level = tnodes_at_level[0].nelem;
    for(i = 0; i < num_at_level; i++)
	{
	    inode = tnodes_at_level[0].list[i];
	    tnode[inode].T_arr = 0.;
	}

	total = 0;
    for(ilevel = 0; ilevel < num_tnode_levels; ilevel++)
	{
	    num_at_level = tnodes_at_level[ilevel].nelem;
		total += num_at_level;

	    for(i = 0; i < num_at_level; i++)
		{
		    inode = tnodes_at_level[ilevel].list[i];
			if(i == 0) {
				tnode[i].num_critical_input_paths = 1;
			}
		    T_arr = tnode[inode].T_arr;
		    num_edges = tnode[inode].num_edges;
		    tedge = tnode[inode].out_edges;
		    T_crit = max(T_crit, T_arr);

		    for(iedge = 0; iedge < num_edges; iedge++)
			{
			    to_node = tedge[iedge].to_node;
			    Tdel = tedge[iedge].Tdel;

				/* Update number of near critical paths entering tnode */
					/*check for approximate equality*/
				if (fabs(tnode[to_node].T_arr - (T_arr + Tdel)) < EQUAL_DEF){
					tnode[to_node].num_critical_input_paths += tnode[inode].num_critical_input_paths;
				}
				else if (tnode[to_node].T_arr < T_arr + Tdel) {
					tnode[to_node].num_critical_input_paths = tnode[inode].num_critical_input_paths;
				}

				if (tnode[to_node].num_critical_input_paths > max_critical_input_paths)
					max_critical_input_paths = tnode[to_node].num_critical_input_paths;


			    tnode[to_node].T_arr =
				max(tnode[to_node].T_arr, T_arr + Tdel);
			}
		}

	}
	assert(total == num_tnodes);

    if(target_cycle_time > 0.)	/* User specified target cycle time */
	T_cycle = target_cycle_time;
    else			/* Otherwise, target = critical path */
	T_cycle = T_crit;

/* Compute the required arrival times with a backward breadth-first analysis *
 * from sinks (output pads, etc.) to primary inputs.                         */

    for(ilevel = num_tnode_levels - 1; ilevel >= 0; ilevel--)
	{
	    num_at_level = tnodes_at_level[ilevel].nelem;

	    for(i = 0; i < num_at_level; i++)
		{
		    inode = tnodes_at_level[ilevel].list[i];
		    num_edges = tnode[inode].num_edges;

			if(ilevel == 0) {				
				assert(tnode[inode].type == INPAD_SOURCE || tnode[inode].type == FF_SOURCE || tnode[inode].type == CONSTANT_GEN_SOURCE);
			} else {
				assert(!(tnode[inode].type == INPAD_SOURCE || tnode[inode].type == FF_SOURCE || tnode[inode].type == CONSTANT_GEN_SOURCE));
			}

		    if(num_edges == 0)
			{	/* sink */
				assert(tnode[inode].type == OUTPAD_SINK || tnode[inode].type == FF_SINK);
			    tnode[inode].T_req = T_cycle;
				tnode[inode].num_critical_output_paths = 1;
			}
		    else
			{
				assert(!(tnode[inode].type == OUTPAD_SINK || tnode[inode].type == FF_SINK));
			    tedge = tnode[inode].out_edges;
			    to_node = tedge[0].to_node;
			    Tdel = tedge[0].Tdel;
			    T_req = tnode[to_node].T_req - Tdel;

				tnode[inode].num_critical_output_paths = tnode[to_node].num_critical_output_paths;
				if (tnode[to_node].num_critical_output_paths > max_critical_output_paths)
					max_critical_output_paths = tnode[to_node].num_critical_output_paths;

			    for(iedge = 1; iedge < num_edges; iedge++)
				{
				    to_node = tedge[iedge].to_node;
				    Tdel = tedge[iedge].Tdel;

					/* Update number of near critical paths affected by output of tnode */
						/*check for approximate equality*/
					if (fabs(tnode[to_node].T_req - Tdel - T_req) < EQUAL_DEF){
						tnode[inode].num_critical_output_paths += tnode[to_node].num_critical_output_paths;
					}
					else if (tnode[to_node].T_req - Tdel < T_req) {
						tnode[inode].num_critical_output_paths = tnode[to_node].num_critical_output_paths;
					}

					if (tnode[to_node].num_critical_output_paths > max_critical_output_paths)
						max_critical_output_paths = tnode[to_node].num_critical_output_paths;

				    T_req =
					min(T_req,
					    tnode[to_node].T_req - Tdel);
				}

			    tnode[inode].T_req = T_req;
			}
		}
	}

	normalize_costs(T_crit, max_critical_input_paths, max_critical_output_paths);

    compute_net_slacks(net_slack);

    return (T_crit);
}


static void
compute_net_slacks(float **net_slack)
{

/* Puts the slack of each source-sink pair of block pins in net_slack.     */

    int inet, iedge, inode, to_node, num_edges;
    t_tedge *tedge;
    float T_arr, Tdel, T_req;

    for(inet = 0; inet < num_timing_nets; inet++)
	{
	    inode = net_to_driver_tnode[inet];
	    T_arr = tnode[inode].T_arr;
	    num_edges = tnode[inode].num_edges;
	    tedge = tnode[inode].out_edges;

	    for(iedge = 0; iedge < num_edges; iedge++)
		{
		    to_node = tedge[iedge].to_node;
		    Tdel = tedge[iedge].Tdel;
		    T_req = tnode[to_node].T_req;
		    net_slack[inet][iedge + 1] = T_req - T_arr - Tdel;
		}
	}
}


void
print_critical_path(char *fname)
{

/* Prints out the critical path to a file.  */

    t_linked_int *critical_path_head, *critical_path_node;
    FILE *fp;
    int non_global_nets_on_crit_path, global_nets_on_crit_path;
    int tnodes_on_crit_path, inode, iblk, inet;
    t_tnode_type type;
    float total_net_delay, total_logic_delay, Tdel;

    critical_path_head = allocate_and_load_critical_path();
    critical_path_node = critical_path_head;

    fp = my_fopen(fname, "w", 0);

    non_global_nets_on_crit_path = 0;
    global_nets_on_crit_path = 0;
    tnodes_on_crit_path = 0;
    total_net_delay = 0.;
    total_logic_delay = 0.;

    while(critical_path_node != NULL)
	{
	    Tdel =
		print_critical_path_node(fp, critical_path_node);
	    inode = critical_path_node->data;
	    type = tnode[inode].type;
	    tnodes_on_crit_path++;

	    if(type == CB_OPIN)
		{
		    get_tnode_block_and_output_net(inode, &iblk, &inet);

		    if(!timing_nets[inet].is_global)
			non_global_nets_on_crit_path++;
		    else
			global_nets_on_crit_path++;

		    total_net_delay += Tdel;
		}
	    else
		{
		    total_logic_delay += Tdel;
		}

	    critical_path_node = critical_path_node->next;
	}

    fprintf(fp,
	    "\nTnodes on crit. path: %d  Non-global nets on crit. path: %d."
	    "\n", tnodes_on_crit_path, non_global_nets_on_crit_path);
    fprintf(fp, "Global nets on crit. path: %d.\n", global_nets_on_crit_path);
    fprintf(fp, "Total logic delay: %g (s)  Total net delay: %g (s)\n",
	    total_logic_delay, total_net_delay);

    printf("Nets on crit. path: %d normal, %d global.\n",
	   non_global_nets_on_crit_path, global_nets_on_crit_path);

    printf("Total logic delay: %g (s)  Total net delay: %g (s)\n",
	   total_logic_delay, total_net_delay);

    fclose(fp);
    free_int_list(&critical_path_head);
}


t_linked_int *
allocate_and_load_critical_path(void)
{

/* Finds the critical path and puts a list of the tnodes on the critical    *
 * path in a linked list, from the path SOURCE to the path SINK.            */

    t_linked_int *critical_path_head, *curr_crit_node, *prev_crit_node;
    int inode, iedge, to_node, num_at_level, i, crit_node, num_edges;
    float min_slack, slack;
    t_tedge *tedge;

    num_at_level = tnodes_at_level[0].nelem;
    min_slack = HUGE_FLOAT;
    crit_node = OPEN;		/* Stops compiler warnings. */

    for(i = 0; i < num_at_level; i++)
	{			/* Path must start at SOURCE (no inputs) */
	    inode = tnodes_at_level[0].list[i];
	    slack = tnode[inode].T_req - tnode[inode].T_arr;

	    if(slack < min_slack)
		{
		    crit_node = inode;
		    min_slack = slack;
		}
	}

    critical_path_head = (t_linked_int *) my_malloc(sizeof(t_linked_int));
    critical_path_head->data = crit_node;
    prev_crit_node = critical_path_head;
    num_edges = tnode[crit_node].num_edges;

    while(num_edges != 0)
	{			/* Path will end at SINK (no fanout) */
	    curr_crit_node = (t_linked_int *) my_malloc(sizeof(t_linked_int));
	    prev_crit_node->next = curr_crit_node;
	    tedge = tnode[crit_node].out_edges;
	    min_slack = HUGE_FLOAT;

	    for(iedge = 0; iedge < num_edges; iedge++)
		{
		    to_node = tedge[iedge].to_node;
		    slack = tnode[to_node].T_req - tnode[to_node].T_arr;

		    if(slack < min_slack)
			{
			    crit_node = to_node;
			    min_slack = slack;
			}
		}

	    curr_crit_node->data = crit_node;
	    prev_crit_node = curr_crit_node;
	    num_edges = tnode[crit_node].num_edges;
	}

    prev_crit_node->next = NULL;
    return (critical_path_head);
}


void
get_tnode_block_and_output_net(int inode,
			       int *iblk_ptr,
			       int *inet_ptr)
{

/* Returns the index of the block that this tnode is part of.  If the tnode *
 * is a CB_OPIN or INPAD_OPIN (i.e. if it drives a net), the net index is  *
 * returned via inet_ptr.  Otherwise inet_ptr points at OPEN.               */

    int inet, ipin, iblk;
    t_tnode_type tnode_type;

    iblk = tnode[inode].block;
    tnode_type = tnode[inode].type;

    if(tnode_type == CB_OPIN)
	{
	    ipin = tnode[inode].pb_graph_pin->pin_count_in_cluster;
		inet = block[iblk].pb->rr_graph[ipin].net_num;
		assert(inet != OPEN);
		inet = vpack_to_clb_net_mapping[inet];
	}
    else
	{
	    inet = OPEN;
	}

    *iblk_ptr = iblk;
    *inet_ptr = inet;
}


void
do_constant_net_delay_timing_analysis(t_timing_inf timing_inf,
				      float constant_net_delay_value)
{

/* Does a timing analysis (simple) where it assumes that each net has a      *
 * constant delay value.  Used only when operation == TIMING_ANALYSIS_ONLY.  */

    struct s_linked_vptr *net_delay_chunk_list_head;
    float **net_delay, **net_slack;

    float T_crit;

    net_slack = alloc_and_load_timing_graph(timing_inf);
    net_delay = alloc_net_delay(&net_delay_chunk_list_head, timing_nets, num_timing_nets);

    load_constant_net_delay(net_delay, constant_net_delay_value, timing_nets, num_timing_nets);
    load_timing_graph_net_delays(net_delay);
    T_crit = load_net_slack(net_slack, 0);

    printf("\n");
    printf("\nCritical Path: %g (s)\n", T_crit);

#ifdef CREATE_ECHO_FILES
    print_critical_path("critical_path.echo");
    print_timing_graph("timing_graph.echo");
    print_net_slack("net_slack.echo", net_slack);
    print_net_delay(net_delay, "net_delay.echo", timing_nets, num_timing_nets);
#endif /* CREATE_ECHO_FILES */

    free_timing_graph(net_slack);
    free_net_delay(net_delay, &net_delay_chunk_list_head);
}

static void normalize_costs(float t_crit, long max_critical_input_paths, long max_critical_output_paths) {
	int i;
	for(i = 0; i < num_tnodes; i++) {
		tnode[i].normalized_slack = ((float)tnode[i].T_req - tnode[i].T_arr) / t_crit;
		tnode[i].normalized_T_arr = (float)tnode[i].T_arr/(float)t_crit;
		tnode[i].normalized_total_critical_paths = ((float)tnode[i].num_critical_input_paths + tnode[i].num_critical_output_paths) / ((float)max_critical_input_paths + max_critical_output_paths);
	}
}




void
print_timing_graph_as_blif(char *fname, t_model *models)
{
	struct s_model_ports *port;
	struct s_linked_vptr *p_io_removed;
/* Prints out the critical path to a file.  */

    FILE *fp;
	int i, j;

    fp = my_fopen(fname, "w", 0);

	fprintf(fp, ".model %s\n", blif_circuit_name);
	
	fprintf(fp, ".inputs ");
	for(i = 0; i < num_logical_blocks; i++) {
		if(logical_block[i].type == VPACK_INPAD) {
			fprintf(fp, "\\\n%s ", logical_block[i].name);
		}
	}
	p_io_removed = circuit_p_io_removed;
	while(p_io_removed) {
		fprintf(fp, "\\\n%s ", (char *) p_io_removed->data_vptr);
		p_io_removed = p_io_removed->next;
	}

	fprintf(fp, "\n");
	
	fprintf(fp, ".outputs ");
	for(i = 0; i < num_logical_blocks; i++) {
		if(logical_block[i].type == VPACK_OUTPAD) {
			/* Outputs have a "out:" prepended to them, must remove */
			fprintf(fp, "\\\n%s ", &logical_block[i].name[4]);
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, ".names unconn\n");
	fprintf(fp, " 0\n\n");

	/* Print out primitives */
	for(i = 0; i < num_logical_blocks; i++) {
		print_primitive_as_blif(fp, i);
	}

	/* Print out tnode connections */
	for(i = 0; i < num_tnodes; i++) {
		if(tnode[i].type != PRIMITIVE_IPIN && tnode[i].type != FF_SOURCE && tnode[i].type != INPAD_SOURCE && tnode[i].type != OUTPAD_IPIN) {
			for(j = 0; j < tnode[i].num_edges; j++) {
				fprintf(fp, ".names tnode_%d tnode_%d\n", i, tnode[i].out_edges[j]);
				fprintf(fp, "1 1\n\n");
			}
		}
	}
	
	fprintf(fp, ".end\n\n");

	/* Print out .subckt models */
	while(models) {
		fprintf(fp, ".model %s\n", models->name);
		fprintf(fp, ".inputs ");
		port = models->inputs;
		while(port) {
			if(port->size > 1) {
				for(j = 0; j < port->size; j++) {
					fprintf(fp, "%s[%d] ", port->name, j);
				}
			} else {
				fprintf(fp, "%s ", port->name);
			}
			port = port->next;
		}
		fprintf(fp, "\n");
		fprintf(fp, ".outputs ");
		port = models->outputs;
		while(port) {
			if(port->size > 1) {
				for(j = 0; j < port->size; j++) {
					fprintf(fp, "%s[%d] ", port->name, j);
				}
			} else {
				fprintf(fp, "%s ", port->name);
			}
			port = port->next;
		}
		fprintf(fp, "\n.blackbox\n.end\n\n");
		fprintf(fp, "\n\n");
		models = models->next;
	}
    fclose(fp);
}

static void print_primitive_as_blif (FILE *fpout, int iblk) {
	int i, j;
	struct s_model_ports *port;
	struct s_linked_vptr *truth_table;
	t_rr_node *irr_graph;
	t_pb_graph_node *pb_graph_node;
	int node;

	/* Print primitives found in timing graph in blif format based on whether this is a logical primitive or a physical primitive */
	
	if(logical_block[iblk].type == VPACK_INPAD) {
		if(logical_block[iblk].pb == NULL) {
			fprintf(fpout, ".names %s tnode_%d\n", logical_block[iblk].name, logical_block[iblk].output_net_tnodes[0][0]->index);
		} else {
			fprintf(fpout, ".names %s tnode_%d\n", logical_block[iblk].name, 
				logical_block[iblk].pb->rr_graph[logical_block[iblk].pb->pb_graph_node->output_pins[0][0].pin_count_in_cluster].tnode->index);
		}
		fprintf(fpout, "1 1\n\n");
	} else if(logical_block[iblk].type == VPACK_OUTPAD) {
		/* outputs have the symbol out: automatically prepended to it, must remove */
		if(logical_block[iblk].pb == NULL) {
			fprintf(fpout, ".names tnode_%d %s\n", logical_block[iblk].input_net_tnodes[0][0]->index, &logical_block[iblk].name[4]);
		} else {
			/* avoid the out: from output pad naming */
			fprintf(fpout, ".names tnode_%d %s\n", 
				logical_block[iblk].pb->rr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][0].pin_count_in_cluster].tnode->index,
				(logical_block[iblk].name + 4));
		}
		fprintf(fpout, "1 1\n\n");
	} else if(strcmp(logical_block[iblk].model->name, "latch") == 0) {
		fprintf(fpout, ".latch ");
		node = OPEN;
		
		if(logical_block[iblk].pb == NULL) {
			i = 0;
			port = logical_block[iblk].model->inputs;
			while(port) {
				if(!port->is_clock) {
					assert(port->size == 1);
					for(j = 0; j < port->size; j++) {
						if(logical_block[iblk].input_net_tnodes[i][j] != NULL) {
							fprintf(fpout, "tnode_%d ", logical_block[iblk].input_net_tnodes[i][j]->index);
						} else {
							assert(0);
						}
					}
					i++;
				}
				port = port->next;
			}
			assert(i == 1);

			i = 0;
			port = logical_block[iblk].model->outputs;
			while(port) {
				assert(port->size == 1);
				for(j = 0; j < port->size; j++) {
					if(logical_block[iblk].output_net_tnodes[i][j] != NULL) {
						node = logical_block[iblk].output_net_tnodes[i][j]->index;
						fprintf(fpout, "latch_%s re ", logical_block[iblk].name);
					} else {
						assert(0);
					}
				}
				i++;
				port = port->next;
			}
			assert(i == 1);

			i = 0;
			port = logical_block[iblk].model->inputs;
			while(port) {
				if(port->is_clock) {
					for(j = 0; j < port->size; j++) {
						if(logical_block[iblk].clock_net_tnode != NULL) {
							fprintf(fpout, "tnode_%d 0\n\n", logical_block[iblk].clock_net_tnode->index);
						} else {
							assert(0);
						}
					}
					i++;
				}
				port = port->next;
			}
			assert(i == 1);
		} else {
			irr_graph = logical_block[iblk].pb->rr_graph;
			assert(irr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][0].pin_count_in_cluster].net_num != OPEN);
			fprintf(fpout, "tnode_%d ", irr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][0].pin_count_in_cluster].tnode->index);
			node = irr_graph[logical_block[iblk].pb->pb_graph_node->output_pins[0][0].pin_count_in_cluster].tnode->index;
			fprintf(fpout, "latch_%s re ", logical_block[iblk].name);
			assert(irr_graph[logical_block[iblk].pb->pb_graph_node->clock_pins[0][0].pin_count_in_cluster].net_num != OPEN);
			fprintf(fpout, "tnode_%d 0\n\n", irr_graph[logical_block[iblk].pb->pb_graph_node->clock_pins[0][0].pin_count_in_cluster].tnode->index);
		}
		assert(node != OPEN);
		fprintf(fpout, ".names latch_%s tnode_%d\n", logical_block[iblk].name, node);
		fprintf(fpout, "1 1\n\n");
	} else if(strcmp(logical_block[iblk].model->name, "names") == 0) {
		fprintf(fpout, ".names ");
		node = OPEN;

		if(logical_block[iblk].pb == NULL) {
			i = 0;
			port = logical_block[iblk].model->inputs;
			while(port) {
				assert(!port->is_clock);
				for(j = 0; j < port->size; j++) {
					if(logical_block[iblk].input_net_tnodes[i][j] != NULL) {
						fprintf(fpout, "tnode_%d ", logical_block[iblk].input_net_tnodes[i][j]->index);
					} else {
						break;
					}
				}
				i++;
				port = port->next;
			}
			assert(i == 1);

			i = 0;
			port = logical_block[iblk].model->outputs;
			while(port) {
				assert(port->size == 1);
				fprintf(fpout, "lut_%s\n", logical_block[iblk].name);
				node = logical_block[iblk].output_net_tnodes[0][0]->index;
				assert(node != OPEN);			
				i++;
				port = port->next;
			}
			assert(i == 1);
		} else {
			irr_graph = logical_block[iblk].pb->rr_graph;
			assert(logical_block[iblk].pb->pb_graph_node->num_input_ports == 1);
			for(i = 0; i < logical_block[iblk].pb->pb_graph_node->num_input_pins[0]; i++) {
				if(irr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][i].pin_count_in_cluster].net_num != OPEN) {
					fprintf(fpout, "tnode_%d ", irr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][i].pin_count_in_cluster].tnode->index);
				} else {
					if(i > 0 && i < logical_block[iblk].pb->pb_graph_node->num_input_pins[0] - 1) {
						assert(irr_graph[logical_block[iblk].pb->pb_graph_node->input_pins[0][i + 1].pin_count_in_cluster].net_num == OPEN);
					}
				}
			}
			assert(logical_block[iblk].pb->pb_graph_node->num_output_ports == 1);
			assert(logical_block[iblk].pb->pb_graph_node->num_output_pins[0] == 1);
			fprintf(fpout, "lut_%s\n", logical_block[iblk].name);
			node = irr_graph[logical_block[iblk].pb->pb_graph_node->output_pins[0][0].pin_count_in_cluster].tnode->index;
		}
		assert(node != OPEN);
		truth_table = logical_block[iblk].truth_table;
		while(truth_table) {
			fprintf(fpout, "%s\n", (char*)truth_table->data_vptr);
			truth_table = truth_table->next;
		}
		fprintf(fpout, "\n");
		fprintf(fpout, ".names lut_%s tnode_%d\n", logical_block[iblk].name, node);
		fprintf(fpout, "1 1\n\n");
	} else {
		/* This is a standard .subckt blif structure */
		fprintf(fpout, ".subckt %s ", logical_block[iblk].model->name);
		if(logical_block[iblk].pb == NULL) {
			i = 0;
			port = logical_block[iblk].model->inputs;
			while(port) {
				if(!port->is_clock) {
					for(j = 0; j < port->size; j++) {
						if(logical_block[iblk].input_net_tnodes[i][j] != NULL) {
							if(port->size > 1) {
								fprintf(fpout, "\\\n%s[%d]=tnode_%d ", port->name, j, logical_block[iblk].input_net_tnodes[i][j]->index);
							} else {
								fprintf(fpout, "\\\n%s=tnode_%d ", port->name, logical_block[iblk].input_net_tnodes[i][j]->index);
							}
						} else {
							if(port->size > 1) {
								fprintf(fpout, "\\\n%s[%d]=unconn ", port->name, j);
							} else {
								fprintf(fpout, "\\\n%s=unconn ", port->name);
							}
						}
					}
					i++;
				}		
				port = port->next;
			}

			i = 0;
			port = logical_block[iblk].model->outputs;
			while(port) {
				for(j = 0; j < port->size; j++) {
					if(logical_block[iblk].output_net_tnodes[i][j] != NULL) {
						if(port->size > 1) {
							fprintf(fpout, "\\\n%s[%d]=%s ", port->name, j, vpack_net[logical_block[iblk].output_nets[i][j]].name);
						} else {
							fprintf(fpout, "\\\n%s=%s ", port->name, vpack_net[logical_block[iblk].output_nets[i][j]].name);
						}
					} else {
						if(port->size > 1) {
							fprintf(fpout, "\\\n%s[%d]=unconn_%d_%s_%d ", port->name, j, iblk, port->name, j);
						} else {
							fprintf(fpout, "\\\n%s=unconn_%d_%s_%d ", port->name, iblk, port->name);
						}
					}
				}
				i++;
				port = port->next;
			}


			i = 0;
			port = logical_block[iblk].model->inputs;
			while(port) {
				if(port->is_clock) {
					assert(port->size == 1);
					if(logical_block[iblk].clock_net_tnode != NULL) {
						fprintf(fpout, "\\\n%s=tnode_%d ", port->name, logical_block[iblk].clock_net_tnode->index);
					} else {
						fprintf(fpout, "\\\n%s=unconn ", port->name);
					}
					i++;
				}		
				port = port->next;
			}

			fprintf(fpout, "\n\n");

			
			i = 0;
			port = logical_block[iblk].model->outputs;
			while(port) {
				for(j = 0; j < port->size; j++) {
					if(logical_block[iblk].output_net_tnodes[i][j] != NULL) {
						fprintf(fpout, ".names %s tnode_%d\n", vpack_net[logical_block[iblk].output_nets[i][j]].name, logical_block[iblk].output_net_tnodes[i][j]->index);
						fprintf(fpout, "1 1\n\n");
					}
				}
				i++;
				port = port->next;
			}
		} else {
			irr_graph = logical_block[iblk].pb->rr_graph;
			pb_graph_node = logical_block[iblk].pb->pb_graph_node;
			for(i = 0; i < pb_graph_node->num_input_ports; i++) {
				for(j = 0; j < pb_graph_node->num_input_pins[i]; j++) {
					if(irr_graph[pb_graph_node->input_pins[i][j].pin_count_in_cluster].net_num != OPEN) {
						if(pb_graph_node->num_input_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=tnode_%d ", pb_graph_node->input_pins[i][j].port->name, j, irr_graph[pb_graph_node->input_pins[i][j].pin_count_in_cluster].tnode->index);
						} else {
							fprintf(fpout, "\\\n%s=tnode_%d ", pb_graph_node->input_pins[i][j].port->name, irr_graph[pb_graph_node->input_pins[i][j].pin_count_in_cluster].tnode->index);
						}
					} else {
						if(pb_graph_node->num_input_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=unconn ", pb_graph_node->input_pins[i][j].port->name, j);
						} else {
							fprintf(fpout, "\\\n%s=unconn ", pb_graph_node->input_pins[i][j].port->name);
						}
					}
				}
			}
			for(i = 0; i < pb_graph_node->num_output_ports; i++) {
				for(j = 0; j < pb_graph_node->num_output_pins[i]; j++) {
					if(irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].net_num != OPEN) {
						if(pb_graph_node->num_output_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=%s ", pb_graph_node->output_pins[i][j].port->name, j, 
								vpack_net[irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].net_num].name);
						} else {
							fprintf(fpout, "\\\n%s=%s ", pb_graph_node->output_pins[i][j].port->name, 
								vpack_net[irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].tnode->index].name);
						}
					} else {
						if(pb_graph_node->num_output_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=unconn ", pb_graph_node->output_pins[i][j].port->name, j);
						} else {
							fprintf(fpout, "\\\n%s=unconn ", pb_graph_node->output_pins[i][j].port->name);
						}
					}
				}
			}
			for(i = 0; i < pb_graph_node->num_clock_ports; i++) {
				for(j = 0; j < pb_graph_node->num_clock_pins[i]; j++) {
					if(irr_graph[pb_graph_node->clock_pins[i][j].pin_count_in_cluster].net_num != OPEN) {
						if(pb_graph_node->num_clock_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=tnode_%d ", pb_graph_node->clock_pins[i][j].port->name, j, irr_graph[pb_graph_node->clock_pins[i][j].pin_count_in_cluster].tnode->index);
						} else {
							fprintf(fpout, "\\\n%s=tnode_%d ", pb_graph_node->clock_pins[i][j].port->name, irr_graph[pb_graph_node->clock_pins[i][j].pin_count_in_cluster].tnode->index);
						}
					} else {
						if(pb_graph_node->num_clock_pins[i] > 1) {
							fprintf(fpout, "\\\n%s[%d]=unconn ", pb_graph_node->clock_pins[i][j].port->name, j);
						} else {
							fprintf(fpout, "\\\n%s=unconn ", pb_graph_node->clock_pins[i][j].port->name);
						}
					}
				}
			}

			fprintf(fpout, "\n\n");
			/* connect up output port names to output tnodes */
			for(i = 0; i < pb_graph_node->num_output_ports; i++) {
				for(j = 0; j < pb_graph_node->num_output_pins[i]; j++) {
					if(irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].net_num != OPEN) {
						fprintf(fpout, ".names %s tnode_%d\n", vpack_net[irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].net_num].name, irr_graph[pb_graph_node->output_pins[i][j].pin_count_in_cluster].tnode->index);
						fprintf(fpout, "1 1\n\n");
					}
				}
			}
		}
	}
}
