/* This file contains the major data types used by VPR

This document is divided into generally 4 major sections:

1.  Global data types and constants
2.  Packing specific data types
3.  Placement specific data types
4.  Routing specific data types

*/


#ifndef VPR_TYPES_H
#define VPR_TYPES_H

#include "arch_types.h"

/*******************************************************************************
 * Global data types and constants
 ******************************************************************************/

#ifndef SPEC
#define DEBUG 1			/* Echoes input & checks error conditions */
		    /* Only causes about a 1% speed degradation in V 3.10 */
#endif


/*#define CREATE_ECHO_FILES*/ /* prints echo files */
/*#define DEBUG_FAILED_PACKING_CANDIDATES*//*Displays candidates during packing that failed */
/*#define PRINT_SINK_DELAYS*//*prints the sink delays to files */
/*#define PRINT_NET_SLACKS*//*prints out all slacks in the circuit */
/*#define PRINT_PLACE_CRIT_PATH*//*prints out placement estimated critical path */
/*#define PRINT_NET_DELAYS*//*prints out delays for all connections */
/*#define PRINT_TIMING_GRAPH*//*prints out the timing graph */
/*#define PRINT_REL_POS_DISTR *//*prints out the relative distribution graph for placements */
/*#define DUMP_BLIF_ECHO *//*dump blif of internal representation of user circuit.  Useful for ensuring functional correctness via logical equivalence with input blif*/


#ifdef SPEC
#define NO_GRAPHICS		/* Rips out graphics (for non-X11 systems)      */
#define NDEBUG			/* Turns off assertion checking for extra speed */
#endif

#define TOKENS " \t\n"		/* Input file parsing. */

/*#define VERBOSE 1*//* Prints all sorts of intermediate data */

typedef size_t bitfield;

#define MINOR 0			/* For update_screen.  Denotes importance of update. */
#define MAJOR 1

#define HUGE_FLOAT 1.e30

#define MAX_SHORT 32767

#define EQUAL_DEF 1e-6            /*used in some if == equations to allow very       *
				   *close values to be considered equal              */

#define HIGH_FANOUT_NET_LIM 64 /* All nets with this number of sinks or more are considered high fanout nets */

#define FIRST_ITER_WIRELENTH_LIMIT 0.85 /* If used wirelength exceeds this value in first iteration of routing, do not route */

#define EMPTY -1

/*******************************************************************************
 * Packing specific data types and constants
 * Packing takes the circuit described in the technology mapped user netlist
 * and maps it to the complex logic blocks found in the arhictecture
 ******************************************************************************/

#define NO_CLUSTER -1
#define NEVER_CLUSTER -2
#define NOT_VALID -10000  /* Marks gains that aren't valid */
						  /* Ensure no gain can ever be this negative! */
#ifndef UNDEFINED						 
#define UNDEFINED -1    
#endif


/* netlist blocks are assigned one of these types */
enum logical_block_types {
	VPACK_INPAD = -2, 
	VPACK_OUTPAD, 
	VPACK_COMB, 
	VPACK_LATCH, 
	VPACK_EMPTY};

/* Selection algorithm for selecting next seed  */
enum e_cluster_seed {
	VPACK_TIMING, 
	VPACK_MAX_INPUTS};

/* Data structure to track nets during blif parsing */
struct hash_logical_nets {
	char *name; /* net name */
	int index; /* Array index for net */
	int count; /* count is the number of pins on this vpack_net so far. */
	struct hash_logical_nets *next; /* Linked list pointer for net */
}; 


enum e_block_pack_status {BLK_PASSED, BLK_FAILED_FEASIBLE, BLK_FAILED_ROUTE, BLK_STATUS_UNDEFINED};

struct s_rr_node; /* defined later, but need to declare here because it is used */

/* Stores statistical information for pb such as cost information */
struct s_pb_stats {
	/* Packing statistics */
	float *gain; /* Attraction (inverse of cost) function */

	/* [0..num_logical_blocks-1]. The timing criticality score of this logical_block. Determined by the most 
	critical vpack_net between this logical_block and any logical_block in the current pb */
	float *lengthgain;
	float *connectiongain; /* [0..num_logical_blocks-1] Weighted sum of connections to attraction function */
	float *prevconnectiongainincr; /* [0..num_logical_blocks-1] Prev sum to weighted sum of connections to attraction function */
	float *sharinggain; /* [0..num_logical_blocks-1]. How many nets on this logical_block are already in the pb under consideration */

	/* [0..num_logical_blocks-1]. This is the gain used for hill-climbing. It stores*
	 * the reduction in the number of pins that adding this logical_block to the the*
	 * current pb will have. This reflects the fact that sometimes the *
	 * addition of a logical_block to a pb may reduce the number of inputs     *
	 * required if it shares inputs with all other BLEs and it's output is  *
	 * used by all other child pbs in this parent pb.                               */
	float *hillgain;

	/* [0..num_marked_nets] and [0..num_marked_blocks] respectively.  List  *
	 * the indices of the nets and blocks that have had their num_pins_of_  *
	 * net_in_pb and gain entries altered.                             */
	int *marked_nets, *marked_blocks;
	int num_marked_nets, num_marked_blocks;

	/* [0..num_logical_nets-1].  How many pins of each vpack_net are contained in the *
	 * currently open pb?                                          */
	int *num_pins_of_net_in_pb;

	/* [0..num_logical_nets-1].  Is the driver for this vpack_net in the open pb? */
	boolean *net_output_in_pb;

	/* Basic constraint checking */
	int inputs_avail;
	int outputs_avail;
	int clocks_avail;

	/* Array of feasible blocks to select from [0..num_marked_models-1][0..num_blocks-1] 
	   Sorted in ascending gain order so that the last block is the most desirable (this makes it easy to pop blocks off the list
	*/
	int **feasible_blocks;
	int *num_feasible_blocks; /* [0..num_marked_models-1] */
	int num_marked_models;
	int cur_marked_model; /* current model to consider, if NOT_VALID, refresh list */
}; 
typedef struct s_pb_stats t_pb_stats;

/* An FPGA complex block is represented by a hierarchy of physical blocks.  
   These include leaf physical blocks that a netlist block can map to (such as LUTs, flip-flops, memory slices, etc),
   parent physical blocks that contain children physical blocks (such as a BLE) that may be leaves or parents of other physical blocks,
   and the top-level phyiscal block which represents the complex block itself (such as a clustered logic block).

   All physical blocks are represented by this s_pb data structure.
 */
struct s_pb
{
    char *name;						/* Name of this physical block */
	t_pb_graph_node *pb_graph_node; /* pointer to pb_graph_node this pb corresponds to */
	int logical_block;				/* If this is a terminating pb, gives the logical (netlist) block that it contains */

	int mode;						/* mode that this pb is set to */
	
	struct s_pb **child_pbs;		/* children pbs attached to this pb [0..num_child_pb_types - 1][0..child_type->num_pb - 1] */
	struct s_pb *parent_pb;			/* pointer to parent node */

	struct s_rr_node *rr_graph;		/* pointer to rr_graph connecting pbs of cluster */
	struct s_pb_stats pb_stats;		/* statistics for current pb */

	struct s_net *local_nets;		/* Records post-packing connections, valid only for top-level */
	int num_local_nets;				/* Records post-packing connections, valid only for top-level */
};
typedef struct s_pb t_pb;

struct s_tnode;


/* Technology-mapped user netlist block */
struct s_logical_block {
	char *name;						/* Taken from the first vpack_net which it drives. */
	enum logical_block_types type;  /* I/O, combinational logic, or latch */
	t_model* model;                 /* Technology-mapped type (eg. LUT, Flip-flop, memory slice, inpad, etc) */

	int **input_nets;				/* [0..num_input_ports-1][0..num_port_pins-1] List of input nets connected to this logical_block. */
	int **output_nets;				/* [0..num_output_ports-1][0..num_port_pins-1] List of output nets connected to this logical_block. */
	int clock_net;					/* List of clock net connected to this logical_block.  		*/

	int used_input_pins;			/* Number of used input pins */

	int clb_index;					/* Complex block index that this logical block got mapped to */

	int index;						/* Index in array that this block can be found */
	t_pb* pb;						/* pb primitive that this block is packed into */

	/* timing information */
	struct s_tnode ***input_net_tnodes;	 /* [0..num_input_ports-1][0..num_pins -1] correspnding input net tnode */
	struct s_tnode ***output_net_tnodes; /* [0..num_output_ports-1][0..num_pins -1] correspnding output net tnode */
	struct s_tnode *clock_net_tnode;	 /* correspnding clock net tnode */

	struct s_linked_vptr *truth_table;   /* If this is a LUT (.names), then this is the logic that the LUT implements */
};
typedef struct s_logical_block t_logical_block;

/* Built-in library models */
#define MODEL_LOGIC "names"
#define MODEL_LATCH "latch"
#define MODEL_INPUT "input"
#define MODEL_OUTPUT "output"


/******************************************************************
* Timing data structures begin 
*******************************************************************/

/* Timing graph information */
typedef struct
{
    int to_node;
    float Tdel;
}
t_tedge;

/* to_node: index of node at the sink end of this edge.                      *
 * Tdel: delay to go to to_node along this edge.                             */


typedef enum
{ INPAD_SOURCE, INPAD_OPIN, OUTPAD_IPIN, OUTPAD_SINK,
    CB_IPIN, CB_OPIN, INTERMEDIATE_NODE, PRIMITIVE_IPIN, PRIMITIVE_OPIN, 
	FF_IPIN, FF_OPIN,
	FF_SINK, FF_SOURCE,
    CONSTANT_GEN_SOURCE
}
t_tnode_type;
/* type:  What is this tnode? (Pad pin, clb pin, subblock pin, etc.)         *
 * ipin:  Number of the CLB or subblock pin this tnode represents, if        *
 *        applicable.                                                        *
 * isubblk: Number of the subblock this tnode is part of, if applicable.     *
 * iblk:  Number of the block (CLB or PAD) this tnode is part of.            */


/* tnode data structure for a node in a timing graph
 * out_edges: [0..num_edges - 1].  Array of the edges leaving this tnode.    *
 * num_edges: Number of edges leaving this node.                             *
 * T_arr:  Arrival time of the last input signal to this node.               *
 * T_req:  Required arrival time of the last input signal to this node if    *
 *         the critical path is not to be lengthened.                        *
 * type:  What is this tnode? (Pad pin, clb pin, subblock pin, etc.)         *
 * pb_graph_pin:  pb pin that this block is connected to                     *
 * block: Which block this pin is connected to
 * index: index of array this tnode belongs to
 * num_critical_input_paths, num_critical_output_paths: Count total number of near critical paths that go through this node *
 */
struct s_tnode
{
    t_tedge *out_edges;
    int num_edges;
    float T_arr;
    float T_req;	
	int block;

	/* post-packing timing graph */
	t_tnode_type type;
	t_pb_graph_pin *pb_graph_pin;
	
	/* pre-packing timing graph */
	int model_port, model_pin;									/* technology mapped model port/pin */
	long num_critical_input_paths, num_critical_output_paths;   /* count of critical paths passing through this tnode */
	float normalized_slack;										/* slack (normalized with respect to max slack) */
	float normalized_total_critical_paths;						/* critical path count (normalized with respect to max count) */
	float normalized_T_arr;										/* arrival time (normalized with respect to max time) */

	int index;
};
typedef struct s_tnode t_tnode;


/***************************************************************************
* Placement and routing data types
****************************************************************************/

/* Timing data structures end */
enum sched_type
{ AUTO_SCHED, USER_SCHED };	/* Annealing schedule */

enum pic_type
{ NO_PICTURE, PLACEMENT, ROUTING };	/* What's on screen? */

/* For the placer.  Different types of cost functions that can be used. */
enum place_c_types
{ LINEAR_CONG, NONLINEAR_CONG }; /* Nonlinear placement is deprecated */

/* Map netlist to FPGA or timing analyze only */
enum e_operation
{ RUN_FLOW, TIMING_ANALYSIS_ONLY
};

enum pfreq
{ PLACE_NEVER, PLACE_ONCE, PLACE_ALWAYS };


/* Are the pads free to be moved, locked in a random configuration, or *
 * locked in user-specified positions?                                 */
enum e_pad_loc_type
{ FREE, RANDOM, USER };

/* name:  ASCII net name for informative annotations in the output.          *
 * num_sinks:  Number of sinks on this net.                                  *
 * node_block: [0..num_sinks]. Contains the blocks to which the nodes of this 
 *         net connect.  The source block is node_block[0] and the sink blocks
 *         are the remaining nodes.
 * node_block_port: [0..num_sinks]. Contains port index (on a block) to 
 *          which each net terminal connects. 
 * node_block_pin: [0..num_sinks]. Contains the index of the pin (on a block) to 
 *          which each net terminal connects. 
 * is_global: not routed
 * is_const_gen: constant generator (does not affect timing) */
struct s_net
{
    char *name;
    int num_sinks;
    int *node_block;
	int *node_block_port;
    int *node_block_pin;
    boolean is_global;
	boolean is_const_gen;
};

/* s_grid_tile is the minimum tile of the fpga                         
 * type:  Pointer to type descriptor, NULL for illegal, IO_TYPE for io 
 * offset: Number of grid tiles above the bottom location of a block 
 * usage: Number of blocks used in this grid tile
 * blocks[]: Array of logical blocks placed in a physical position, EMPTY means
             no block at that index */
struct s_grid_tile
{
    t_type_ptr type;
    int offset;
    int usage;
    int *blocks;
};

/* Stores the bounding box of a net in terms of the minimum and  *
 * maximum coordinates of the blocks forming the net, clipped to *
 * the region (1..nx, 1..ny).                                    */
struct s_bb
{
    int xmin;
    int xmax;
    int ymin;
    int ymax;
};


/* capacity:   Capacity of this region, in tracks.               *
 * occupancy:  Expected number of tracks that will be occupied.  *
 * cost:       Current cost of this usage.                       */
struct s_place_region
{
    float capacity;
    float inv_capacity;
    float occupancy;
    float cost;
};


/*
 Represents a clustered logic block of a user circuit that fits into one unit of space in an FPGA grid block
 name: identifier for this block
 type: the type of physical block this user circuit block can map into
 nets: nets that connect to other user circuit blocks
 x: x-coordinate
 y: y-coordinate
 z: occupancy coordinate
 pb: Physical block representing the clustering of this CLB
 */
struct s_block
{
    char *name;
    t_type_ptr type;
    int *nets;
    int x;
    int y;
    int z;

	t_pb *pb;
	
};
typedef struct s_block t_block;

/* Names of various files */
struct s_file_name_opts
{
    char *ArchFile;
	char *CircuitName;
	char *BlifFile;
	char *NetFile;
	char *PlaceFile;
	char *RouteFile;
	char *OutFilePrefix;	
};

/* Options for packing
 * TODO: document each packing parameter         */
enum e_packer_algorithm
{ PACK_GREEDY, PACK_BRUTE_FORCE};

struct s_packer_opts
{
    char *blif_file_name;
	char *output_file;
	boolean global_clocks;
	int clocks_per_cluster;
	boolean hill_climbing_flag;
	boolean sweep_hanging_nets_and_inputs;
	boolean timing_driven;
	enum e_cluster_seed cluster_seed_type;
	float alpha;
	float beta;
	int recompute_timing_after;
	float block_delay;
	float intra_cluster_net_delay;
	float inter_cluster_net_delay;
	boolean skip_clustering;
	boolean allow_unrelated_clustering;
	boolean allow_early_exit;
	boolean connection_driven;
	boolean doPacking;
	boolean hack_no_legal_frac_lut;
	boolean hack_safe_latch;
	enum e_packer_algorithm packer_algorithm;
	float aspect;
};


/* Annealing schedule information for the placer.  The schedule type      *
 * is either USER_SCHED or AUTO_SCHED.  Inner_num is multiplied by        *
 * num_blocks^4/3 to find the number of moves per temperature.  The       *
 * remaining information is used only for USER_SCHED, and have the        *
 * obvious meanings.                                                      */
struct s_annealing_sched
{
    enum sched_type type;
    float inner_num;
    float init_t;
    float alpha_t;
    float exit_t;
};


enum e_place_algorithm
{ BOUNDING_BOX_PLACE, NET_TIMING_DRIVEN_PLACE,
    PATH_TIMING_DRIVEN_PLACE
};
struct s_placer_opts
{
    enum e_place_algorithm place_algorithm;
    float timing_tradeoff;
    int block_dist;
    enum place_c_types place_cost_type;
    float place_cost_exp;
    int place_chan_width;
    enum e_pad_loc_type pad_loc_type;
    char *pad_loc_file;
    enum pfreq place_freq;
    int num_regions;
    int recompute_crit_iter;
    boolean enable_timing_computations;
    int inner_loop_recompute_divider;
    float td_place_exp_first;
    int seed;
    float td_place_exp_last;
	boolean doPlacement;
	boolean gpu_placement;
};

/* Various options for the placer.                                           *
 * place_algorithm:  BOUNDING_BOX_PLACE or NET_TIMING_DRIVEN_PLACE, or       *
 *                   PATH_TIMING_DRIVEN_PLACE                                *
 * timing_tradeoff:  When TIMING_DRIVEN_PLACE mode, what is the tradeoff *
 *                   timing driven and BOUNDING_BOX_PLACE.                   *
 * block_dist:  Initial guess of how far apart blocks on the critical path   *
 *              This is used to compute the initial slacks and criticalities *
 * place_cost_type:  LINEAR_CONG or NONLINEAR_CONG.                          *
 * place_cost_exp:  Power to which denominator is raised for linear_cong.    *
 * place_chan_width:  The channel width assumed if only one placement is     *
 *                    performed.                                             *
 * pad_loc_type:  Are pins FREE, fixed randomly, or fixed from a file.  *
 * pad_loc_file:  File to read pin locations form if pad_loc_type  *
 *                     is USER.                                              *
 * place_freq:  Should the placement be skipped, done once, or done for each *
 *              channel width in the binary search.                          *
 * num_regions:  Used only with NONLINEAR_CONG; in that case, congestion is  *
 *               computed on an array of num_regions x num_regions basis.    *
 * recompute_crit_iter: how many temperature stages pass before we recompute *
 *               criticalities based on average point to point delay         *
 * enable_timing_computations: in bounding_box mode, normally, timing        *
 *               information is not produced, this causes the information    *
 *               to be computed. in *_TIMING_DRIVEN modes, this has no effect*
 * inner_loop_crit_divider: (move_lim/inner_loop_crit_divider) determines how*
 *               many inner_loop iterations pass before a recompute of       *
 *               criticalities is done.                                      *
 * td_place_exp_first: exponent that is used on the timing_driven criticlity *
 *               it is the value that the exponent starts at.                *
 * td_place_exp_last: value that the criticality exponent will be at the end *
 * doPlacement: TRUE if placement is supposed to be done in the CAD flow, FALSE otherwise */

enum e_route_type
{ GLOBAL, DETAILED };
enum e_router_algorithm
{ BREADTH_FIRST, TIMING_DRIVEN, DIRECTED_SEARCH };
enum e_base_cost_type
{ INTRINSIC_DELAY, DELAY_NORMALIZED, DEMAND_ONLY };

#define NO_FIXED_CHANNEL_WIDTH -1

struct s_router_opts
{
    float first_iter_pres_fac;
    float initial_pres_fac;
    float pres_fac_mult;
    float acc_fac;
    float bend_cost;
    int max_router_iterations;
    int bb_factor;
    enum e_route_type route_type;
    int fixed_channel_width;
    enum e_router_algorithm router_algorithm;
    enum e_base_cost_type base_cost_type;
    float astar_fac;
    float max_criticality;
    float criticality_exp;
	boolean verify_binary_search;
	boolean full_stats;
	boolean doRouting;
};

/* All the parameters controlling the router's operation are in this        *
 * structure.                                                               *
 * first_iter_pres_fac:  Present sharing penalty factor used for the        *
 *                 very first (congestion mapping) Pathfinder iteration.    *
 * initial_pres_fac:  Initial present sharing penalty factor for            *
 *                    Pathfinder; used to set pres_fac on 2nd iteration.    *
 * pres_fac_mult:  Amount by which pres_fac is multiplied each              *
 *                 routing iteration.                                       *
 * acc_fac:  Historical congestion cost multiplier.  Used unchanged         *
 *           for all iterations.                                            *
 * bend_cost:  Cost of a bend (usually non-zero only for global routing).   *
 * max_router_iterations:  Maximum number of iterations before giving       *
 *                up.                                                       *
 * bb_factor:  Linear distance a route can go outside the net bounding      *
 *             box.                                                         *
 * route_type:  GLOBAL or DETAILED.                                         *
 * fixed_channel_width:  Only attempt to route the design once, with the    *
 *                       channel width given.  If this variable is          *
 *                       == NO_FIXED_CHANNEL_WIDTH, do a binary search      *
 *                       on channel width.                                  *
 * router_algorithm:  BREADTH_FIRST or TIMING_DRIVEN.  Selects the desired  *
 *                    routing algorithm.                                    *
 * base_cost_type: Specifies how to compute the base cost of each type of   *
 *                 rr_node.  INTRINSIC_DELAY -> base_cost = intrinsic delay *
 *                 of each node.  DELAY_NORMALIZED -> base_cost = "demand"  *
 *                 x average delay to route past 1 CLB.  DEMAND_ONLY ->     *
 *                 expected demand of this node (old breadth-first costs).  *
 *                                                                          *
 * The following parameters are used only by the timing-driven router.      *
 *                                                                          *
 * astar_fac:  Factor (alpha) used to weight expected future costs to       *
 *             target in the timing_driven router.  astar_fac = 0 leads to  *
 *             an essentially breadth-first search, astar_fac = 1 is near   *
 *             the usual astar algorithm and astar_fac > 1 are more         *
 *             aggressive.                                                  *
 * max_criticality: The maximum criticality factor (from 0 to 1) any sink   *
 *                  will ever have (i.e. clip criticality to this number).  *
 * criticality_exp: Set criticality to (path_length(sink) / longest_path) ^ *
 *                  criticality_exp (then clip to max_criticality).         
 * doRouting: True if routing is supposed to be done, FALSE otherwise */

struct s_det_routing_arch
{
    enum e_directionality directionality;	/* UDSD by AY */
    int Fs;
    enum e_switch_block_type switch_block_type;
    int num_segment;
    short num_switch;
    short global_route_switch;
    short delayless_switch;
    short wire_to_ipin_switch;
    float R_minW_nmos;
    float R_minW_pmos;
};

/* Defines the detailed routing architecture of the FPGA.  Only important   *
 * if the route_type is DETAILED.                                           *
 * (UDSD by AY) directionality: Should the tracks be uni-directional or     *
 *                            bi-directional?                               *
 * Fc_type:   Are the Fc values below absolute numbers, or fractions of W?  *
 * Fc_output:  Number of tracks to which each clb output pin connect in     *
 *             each channel to which it is adjacent.                        *
 * Fc_input:  Number of tracks to which each clb input pin connects.        *
 * Fc_pad:    Number of tracks to which each I/O pad connects.              *
 * switch_block_type:  Pattern of switches at each switch block.  I         *
 *           assume Fs is always 3.  If the type is SUBSET, I use a         *
 *           Xilinx-like switch block where track i in one channel always   *
 *           connects to track i in other channels.  If type is WILTON,     *
 *           I use a switch block where track i does not always connect     *
 *           to track i in other channels.  See Steve Wilton, Phd Thesis,   *
 *           University of Toronto, 1996.  The UNIVERSAL switch block is    *
 *           from Y. W. Chang et al, TODAES, Jan. 1996, pp. 80 - 101.       *
 * num_segment:  Number of distinct segment types in the FPGA.              *
 * num_switch:  Number of distinct switch types (pass transistors or        *
 *              buffers) in the FPGA.                                       *
 * delayless_switch:  Index of a zero delay switch (used to connect things  *
 *                    that should have no delay).                           *
 * wire_to_ipin_switch:  Index of a switch used to connect wire segments    *
 *                       to clb or pad input pins (IPINs).                  *
 * R_minW_nmos:  Resistance (in Ohms) of a minimum width nmos transistor.   *
 *               Used only in the FPGA area model.                          *
 * R_minW_pmos:  Resistance (in Ohms) of a minimum width pmos transistor.   */


enum e_drivers
{ MULTI_BUFFERED, SINGLE }; /* legacy routing drivers by Andy Ye (remove or integrate in future) */

enum e_direction
{
    INC_DIRECTION = 0,
    DEC_DIRECTION = 1,
    BI_DIRECTION = 2
};				/* UDSD by AY */

typedef struct s_seg_details
{
    int length;
    int start;
    boolean longline;
    boolean *sb;
    boolean *cb;
    short wire_switch;
    short opin_switch;
    float Rmetal;
    float Cmetal;
    boolean twisted;
    enum e_direction direction;	/* UDSD by AY */
    enum e_drivers drivers;	/* UDSD by AY */
    int group_start;
    int group_size;
    int index;
}
t_seg_details;

/* Lists detailed information about segmentation.  [0 .. W-1].              *
 * length:  length of segment.                                              *
 * start:  index at which a segment starts in channel 0.                    *
 * longline:  TRUE if this segment spans the entire channel.                *
 * sb:  [0..length]:  TRUE for every channel intersection, relative to the  *
 *      segment start, at which there is a switch box.                      *
 * cb:  [0..length-1]:  TRUE for every logic block along the segment at     *
 *      which there is a connection box.                                    *
 * wire_switch:  Index of the switch type that connects other wires *to*    *
 *               this segment.                                              *
 * opin_switch:  Index of the switch type that connects output pins (OPINs) *
 *               *to* this segment.                                         *
 * Cmetal: Capacitance of a routing track, per unit logic block length.     *
 * Rmetal: Resistance of a routing track, per unit logic block length.      *
 * (UDSD by AY) direction: The direction of a routing track.                *
 * (UDSD by AY) drivers: How do signals driving a routing track connect to  *
 *                       the track?                                         *
 * index: index of the segment type used for this track.                    */

struct s_linked_f_pointer
{
    struct s_linked_f_pointer *next;
    float *fptr;
};

/* A linked list of float pointers.  Used for keeping track of   *
 * which pathcosts in the router have been changed.              */


/* Uncomment lines below to save some memory, at the cost of debugging ease. */
/*enum e_rr_type {SOURCE, SINK, IPIN, OPIN, CHANX, CHANY}; */
/* typedef short t_rr_type */

typedef enum e_rr_type
{ SOURCE = 0, SINK, IPIN, OPIN, CHANX, CHANY, INTRA_CLUSTER_EDGE, NUM_RR_TYPES }
t_rr_type;

/* Type of a routing resource node.  x-directed channel segment,   *
 * y-directed channel segment, input pin to a clb to pad, output   *
 * from a clb or pad (i.e. output pin of a net) and:               *
 * SOURCE:  A dummy node that is a logical output within a block   *
 *          -- i.e., the gate that generates a signal.             *
 * SINK:    A dummy node that is a logical input within a block    *
 *          -- i.e. the gate that needs a signal.                  */


struct s_trace
{
    int index;
    short iswitch;
    struct s_trace *next;
};

/* Basic element used to store the traceback (routing) of each net.        *
 * index:   Array index (ID) of this routing resource node.                *
 * iswitch:  Index of the switch type used to go from this rr_node to      *
 *           the next one in the routing.  OPEN if there is no next node   *
 *           (i.e. this node is the last one (a SINK) in a branch of the   *
 *           net's routing).                                               *
 * next:    pointer to the next traceback element in this route.           */


#define NO_PREVIOUS -1

typedef struct s_rr_node
{
    short xlow;
    short xhigh;
    short ylow;
    short yhigh;

    short ptc_num;

    short cost_index;
    short occ;
    short capacity;
    short fan_in;
    short num_edges;
    t_rr_type type;
    int *edges;
    short *switches;

    float R;
    float C;

    enum e_direction direction;	/* UDSD by AY */
    enum e_drivers drivers;	/* UDSD by AY */
    int num_wire_drivers;	/* UDSD by WMF */
    int num_opin_drivers;	/* UDSD by WMF (could use "short") */

	/* Used by clustering only (TODO, may wish to extend to regular router) */
	int prev_node;
	int prev_edge; 
	int net_num;
	t_pb_graph_pin *pb_graph_pin;
	t_tnode *tnode;
	float pack_intrinsic_cost;
}
t_rr_node;
/* Main structure describing one routing resource node.  Everything in       *
 * this structure should describe the graph -- information needed only       *
 * to store algorithm-specific data should be stored in one of the           *
 * parallel rr_node_?? structures.                                           *
 *                                                                           *
 * xlow, xhigh, ylow, yhigh:  Integer coordinates (see route.c for           *
 *       coordinate system) of the ends of this routing resource.            *
 *       xlow = xhigh and ylow = yhigh for pins or for segments of           *
 *       length 1.  These values are used to decide whether or not this      *
 *       node should be added to the expansion heap, based on things         *
 *       like whether it's outside the net bounding box or is moving         *
 *       further away from the target, etc.                                  *
 * type:  What is this routing resource?                                     *
 * ptc_num:  Pin, track or class number, depending on rr_node type.          *
 *           Needed to properly draw.                                        *
 * cost_index: An integer index into the table of routing resource indexed   *
 *             data (this indirection allows quick dynamic changes of rr     *
 *             base costs, and some memory storage savings for fields that   *
 *             have only a few distinct values).                             *
 * occ:        Current occupancy (usage) of this node.                       *
 * capacity:   Capacity of this node (number of routes that can use it).     *
 * num_edges:  Number of edges exiting this node.  That is, the number       *
 *             of nodes to which it connects.                                *
 * edges[0..num_edges-1]:  Array of indices of the neighbours of this        *
 *                         node.                                             *
 * switches[0..num_edges-1]:  Array of switch indexes for each of the        *
 *                            edges leaving this node.                       *
 *                                                                           *
 * The following parameters are only needed for timing analysis.             *
 * R:  Resistance to go through this node.  This is only metal               *
 *     resistance (end to end, so conservative) -- it doesn't include the    *
 *     switch that leads to another rr_node.                                 *
 * C:  Total capacitance of this node.  Includes metal capacitance, the      *
 *     input capacitance of all switches hanging off the node, the           *
 *     output capacitance of all switches to the node, and the connection    *
 *     box buffer capacitances hanging off it.                               *
 * (UDSD by AY) direction: if the node represents a track, this field        *
 *                         indicates the direction of the track. Otherwise   *
 *                         the value contained in the field should be        *
 *                         ignored.                                          *
 * (UDSD by AY) drivers: if the node represents a track, this field          *
 *                       indicates the driving architecture of the track.    *
 *                       Otherwise the value contained in the field should   *
 *                       be ignored.                                         */


typedef struct s_rr_indexed_data
{
    float base_cost;
    float saved_base_cost;
    int ortho_cost_index;
    int seg_index;
    float inv_length;
    float T_linear;
    float T_quadratic;
    float C_load;
}
t_rr_indexed_data;

/* Data that is pointed to by the .cost_index member of t_rr_node.  It's     *
 * purpose is to store the base_cost so that it can be quickly changed       *
 * and to store fields that have only a few different values (like           *
 * seg_index) or whose values should be an average over all rr_nodes of a    *
 * certain type (like T_linear etc., which are used to predict remaining     *
 * delay in the timing_driven router).                                       *
 *                                                                           *
 * base_cost:  The basic cost of using an rr_node.                           *
 * ortho_cost_index:  The index of the type of rr_node that generally        *
 *                    connects to this type of rr_node, but runs in the      *
 *                    orthogonal direction (e.g. vertical if the direction   *
 *                    of this member is horizontal).                         *
 * seg_index:  Index into segment_inf of this segment type if this type of   *
 *             rr_node is an CHANX or CHANY; OPEN (-1) otherwise.            *
 * inv_length:  1/length of this type of segment.                            *
 * T_linear:  Delay through N segments of this type is N * T_linear + N^2 *  *
 *            T_quadratic.  For buffered segments all delay is T_linear.     *
 * T_quadratic:  Dominant delay for unbuffered segments, 0 for buffered      *
 *               segments.                                                   *
 * C_load:  Load capacitance seen by the driver for each segment added to    *
 *          the chain driven by the driver.  0 for buffered segments.        */


enum e_cost_indices
{ SOURCE_COST_INDEX = 0, SINK_COST_INDEX, OPIN_COST_INDEX,
    IPIN_COST_INDEX, CHANX_COST_INDEX_START
};

/* Gives the index of the SOURCE, SINK, OPIN, IPIN, etc. member of           *
 * rr_indexed_data.                                                          */

/* Type to store our list of token to enum pairings */
struct s_TokenPair
{
    char *Str;
    int Enum;
};


#endif

