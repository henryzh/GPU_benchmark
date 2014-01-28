#ifndef _GPU_PLACE_KERNEL_H_
#define _GPU_PLACE_KERNEL_H_

#include <stdio.h>
#include <string.h>
#include "vpr_types.h"
#include <assert.h>
#include "my_cutil.h"

//#define COPY_EVERYTHING_DEVICE_TO_HOST                // copy back everything from device to host, even read only data
//#define GPU_VERBOSE

#define NO_KERNEL_MALLOC                                // For CUDA 3.1 which does not support dynamic memory allocation
#define MAX_PINS_PER_BLOCK 200                          // Used if NO_KERNEL_BLOCK is enabled

#define WARP_SIZE 32

#define d_max(a,b) (((a) > (b))? (a) : (b))
#define d_min(a,b) ((a) > (b)? (b) : (a))

// Copied from VPR place.c
__device__ static const float cross_count[50] = {  /* [0..49] */
    1.0, 1.0, 1.0, 1.0828, 1.1536, 1.2206, 1.2823, 1.3385, 1.3991, 1.4493,
    1.4974, 1.5455, 1.5937, 1.6418, 1.6899, 1.7304, 1.7709, 1.8114, 1.8519,
    1.8924,
    1.9288, 1.9652, 2.0015, 2.0379, 2.0743, 2.1061, 2.1379, 2.1698, 2.2016,
    2.2334,
    2.2646, 2.2958, 2.3271, 2.3583, 2.3895, 2.4187, 2.4479, 2.4772, 2.5064,
    2.5356,
    2.5610, 2.5864, 2.6117, 2.6371, 2.6625, 2.6887, 2.7148, 2.7410, 2.7671,
    2.7933
};

// Struct to hold data for a grid of single type of cells
struct s_g_grid_t {
    int type;
    int num_cells;                // number of cells in this grid
    int* usage;                    // array holding usage for each cell
    int* blocks;                // array holding block index for each cell, array layout is
                                //             [z_index][cell #] (where cell# is in column major order, i.e. 1,1=0; 1,2=1; ...
                                //            the maximum z_index is given by type.capacity
    int* x;                     // store the real x,y location, needed because we skip columns of different types
    int* y;

    int* lock;                   // locks for grid cells

    int nx;                     // # of columns in this grid
    int ny;                     // # of rows in this grid, should be the same as universal ny
};
typedef struct s_g_grid_t g_grid_t;

// Struct to hold mapping from g_grid index back to grid[x][y]
struct s_g_grid_map_t {
    int num_cells;
    int* x;
    int* y;
};
typedef struct s_g_grid_map_t g_grid_map_t;


// Struct to hold block information
// The nets for each block are stored in a separate contiguous array.
// Since the number of nets (pins) per block depends on the type of block,
// we need to store an index into the shared block_nets array.
struct s_g_block_t {
    int type;
    int index_start_net;        // stores the start index for this block's net-list
    int x;
    int y;
    int z;
};
typedef struct s_g_block_t g_block_t;

// Struct to hold net information
// The blocks for each net are stored in a separate shared array
// Since the number of blocks per net are dynamically determined, we need to
// store an index specifying where this net's block array starts
struct s_g_net_t {
    int num_blocks;
    int index_start_block;        // stores the start index for this net's block-list
    //int *node_block;
    boolean is_global;
    boolean is_const_gen;
};
typedef struct s_g_net_t g_net_t;

// Struct to hold all the type information
struct s_g_type_t {
    int index;
    int num_cells;
    int capacity;
    int num_pins;
};
typedef struct s_g_type_t g_type_t;


////////////////////////////////////////
// Declarations of local functions
////////////////////////////////////////
__global__ void gpu_place_kernel(
        g_type_t* d_types, g_grid_t* d_grid, g_block_t* d_block, int* d_block_nets, g_net_t* d_net, float* d_net_cost, int* d_net_blocks,
        int num_blocks, int num_nets, int global_nx, int global_ny,
        unsigned* seeds,
        float** d_chanx_place_cost_fac, float** d_chany_place_cost_fac,
        float t, float rlim, int n_moves_per_warp, int* d_success_sum
        );

void gpu_transform_data_from_vpr (
        int num_types, struct s_type_descriptor * type_descriptors,
        g_type_t** g_type_p,
        struct s_grid_tile** grid, int nx, int ny,
        g_grid_t** g_grid_p, g_grid_map_t* g_grid_map,
        t_block* block, int num_blocks,
        g_block_t** g_block_p, int** g_block_nets_p, int* net_list_size,
        struct s_net* clb_net, int num_nets,
        g_net_t** g_net_p, int** g_net_blocks_p, int* block_list_size
        );

void gpu_transform_data_to_vpr (
        g_type_t* g_type, int num_types,
        struct s_type_descriptor * type_descriptors,
        g_grid_t* g_grid, g_grid_map_t* g_grid_map,
        struct s_grid_tile** grid,
        g_block_t* g_block, int* g_block_nets, int num_blocks,
        t_block* block,
        g_net_t* g_net, int* g_net_blocks, int num_nets,
        struct s_net* clb_net
        );

void gpu_copy_data_to_device (
        g_type_t* g_type, g_grid_t* g_grid, g_block_t* g_block, int* g_block_nets, g_net_t* g_net, float* g_net_cost, int* g_net_blocks,
        g_type_t** d_type_p, g_grid_t** d_grid_p, g_block_t** d_block_p, int** d_block_nets_p, g_net_t** d_net_p, float** d_net_cost_p, int** d_net_blocks_p,
        int num_types, int num_blocks, int num_nets, int net_list_size, int block_list_size,
        float **g_chanx, float **g_chany, float*** d_chanx, float*** d_chany,
        int nx, int ny
        );

void gpu_copy_data_to_host (
        g_type_t* d_type, g_grid_t* d_grid, g_block_t* d_block, int* d_block_nets, g_net_t* d_net, float* d_net_cost, int* d_net_blocks,
        g_type_t* g_type, g_grid_t* g_grid, g_block_t* g_block, int* g_block_nets, g_net_t* g_net, float* g_net_cost, int* g_net_blocks,
        int num_types, int num_blocks, int num_nets, int net_list_size, int block_list_size
        );
////////////////////////////////////////


/*
 * Helper functions for kernel
 */
struct g_bb_t{
    int m_nx_start;
    int m_nx_end;
    int m_ny_start;
    int m_ny_end;
    __device__ g_bb_t(int nx_start, int nx_end, int ny_start, int ny_end)
    : m_nx_start(nx_start), m_nx_end(nx_end), m_ny_start(ny_start), m_ny_end(ny_end) {}
};  // bounding box struct

// LCG psuedo random number generator
__device__ unsigned rand(unsigned* old) {
    *old = (1664525 * *old + 1013904223);
    return *old;
}

// Randomly select two swap canditates
// nx/ny values are the stored locations, not real locations
// bb_from/to give swap-from and swap-to regions
__device__ void select_swap_candidates(
        g_grid_t* d_grid,
        unsigned* seed, float rlim,
        int* nx_from, int* ny_from, int* nx_to, int* ny_to,
        g_bb_t bb_from
        )
{
    // Select from candidate from the given region
    *nx_from = bb_from.m_nx_start + ( rand(seed) % (bb_from.m_nx_end - bb_from.m_nx_start + 1) );
    *ny_from = bb_from.m_ny_start + ( rand(seed) % (bb_from.m_ny_end - bb_from.m_ny_start + 1) );

    // Select to candidate in the rlim region
    const int rlx = d_min(d_grid->nx-1, rlim);
    const int rly = d_min(d_grid->ny-1, rlim);
    const int min_x = d_max(0, *nx_from - rlx);
    const int max_x = d_min(d_grid->nx-1, *nx_from + rlx);
    const int min_y = d_max(0, *ny_from - rly);
    const int max_y = d_min(d_grid->ny-1, *ny_from + rly);

    *nx_to = min_x + ( rand(seed) % (max_x - min_x + 1) );
    *ny_to = min_y + ( rand(seed) % (max_y - min_y + 1) );
}

// Return true is the swap canditates are valid
// Swap is valid is at least one of the canditates is non-empty and there are different candidates
__device__ bool is_swap_valid(
        int nx_from, int ny_from, int nx_to, int ny_to,
        g_grid_t* d_grid, g_block_t* d_block
        )
{
    if(nx_from == nx_to && ny_from == ny_to)
        return false;

    int cell_from_index = nx_from * d_grid->ny + ny_from;
    int cell_to_index = nx_to * d_grid->ny + ny_to;
    int block_from_usage = d_grid->usage[cell_from_index];
    int block_to_usage = d_grid->usage[cell_to_index];

    return (block_from_usage>=1 || block_to_usage>=1);
}

// Do a swap
// Input nx/ny values are the stored locations, not real locations
// Locations must have been validated before being passed into this function
__device__ void do_swap(
        int nx_from, int ny_from, int nx_to, int ny_to,
        g_grid_t* d_grid, g_block_t* d_block
        )
{
    // TODO: handle z-locations
    int cell_from_index = nx_from * d_grid->ny + ny_from;
    int cell_to_index = nx_to * d_grid->ny + ny_to;

    // Undocumented hack: use volatile keyword to enforce coherence for shared writeable locations
    volatile int* blocks = d_grid->blocks;
    volatile int* usage = d_grid->usage;
    int block_from_id = blocks[cell_from_index];
    int block_to_id = blocks[cell_to_index];

    if(block_from_id >= 0) {
        volatile int* block_from_x = &d_block[block_from_id].x;
        volatile int* block_from_y = &d_block[block_from_id].y;
        *block_from_x = d_grid->x[cell_to_index];
        *block_from_y = d_grid->y[cell_to_index];
        usage[cell_from_index]--;
        usage[cell_to_index]++;
    }
    if(block_to_id >= 0) {
        volatile int* block_to_x = &d_block[block_to_id].x;
        volatile int* block_to_y = &d_block[block_to_id].y;
        *block_to_x = d_grid->x[cell_from_index];
        *block_to_y = d_grid->y[cell_from_index];
        usage[cell_from_index]++;
        usage[cell_to_index]--;
    }

    // Update grid
    blocks[cell_from_index] = block_to_id;
    blocks[cell_to_index] = block_from_id;

    /*
    printf("do_swap from:%d,%d to:%d:%d (from:%d,%d to:%d:%d)\n",
            d_grid->x[cell_to_index], d_grid->y[cell_to_index], d_grid->x[cell_from_index], d_grid->y[cell_from_index],
            nx_from, ny_from, nx_to, ny_to
          );
    */
}

// Compute the cost of a net given a bounding box
// Copied from VPR place.c
__device__ float get_net_bb_cost(
        g_net_t* net, g_bb_t bb_p,
        float** d_chanx_place_cost_fac, float** d_chany_place_cost_fac
)
{
    /* Finds the cost due to one net by looking at its coordinate bounding  *
     * box.                                                                 */
    float ncost, crossing;

    /* Get the expected "crossing count" of a net, based on its number *
     * of pins.  Extrapolate for very large nets.                      */
    if(net->num_blocks > 50)
    {
        crossing = 2.7933 + 0.02616 * ((net->num_blocks) - 50);
        /*    crossing = 3.0;    Old value  */
    }
    else
    {
        crossing = cross_count[(net->num_blocks) - 1];
    }

    ncost = (bb_p.m_nx_end - bb_p.m_nx_start + 1) * crossing *
    d_chanx_place_cost_fac[bb_p.m_ny_end][bb_p.m_ny_start - 1];

    ncost += (bb_p.m_ny_end - bb_p.m_ny_start + 1) * crossing *
    d_chany_place_cost_fac[bb_p.m_nx_end][bb_p.m_nx_start - 1];

    return (ncost);
}

// Function to compute the delta_cost for all nets in a given block
// Net ids and new costs are stored in the provided buffer
// valid_nets indicates the head pointer into the provided buffer
__device__ float get_delta_cost_of_block(
        int warp_tid,
        int nx_cell, int ny_cell,
        int* bb_nx_start, int* bb_nx_end, int* bb_ny_start, int* bb_ny_end,
        g_grid_t* d_grid, g_block_t* d_block, int* d_block_nets, g_net_t* d_net, float* d_net_cost, int* d_net_blocks,
        int num_pins,
        int global_nx, int global_ny,
        float** d_chanx_place_cost_fac, float** d_chany_place_cost_fac,
        float* temp_net_costs, int* temp_net_ids, int* valid_nets           // <--- output
        )
{
    // Loop through all the nets for both blocks and compute the new cost of each net
    // Don't build a unique set of nets like VPR does as we don't want to do searches
    // Potential problems:
    //      * redundant computation of shared nets (where the cost doesn't change)
    //      * nets occurring multiple times per block are double counted in cost
    // Also, we want to temporarily store each net's recomputed cost so that we can
    // update it if the move is accepted in the end. I use dynamically allocated global
    // memory here because shared memory usage would scale with num_pins, workload dependent = bad

    // TODO: handle z-locations
    const int cell_index = nx_cell * d_grid->ny + ny_cell;
    const int block_id = d_grid->blocks[cell_index];

    float delta_cost = 0;                     // aggregate delta cost

    // From block
    if(block_id >= 0) {
        const int net_list_start = d_block[block_id].index_start_net;
        /*
        if(warp_tid == 0)
            printf("warp_tid=%d net_list_start=%d num_pins=%d block_id=%d\n",
                    warp_tid, net_list_start, num_pins, block_id);
        */
        for(unsigned n=0; n<num_pins; n++) {
            const int inet = d_block_nets[net_list_start+n];                        // get the number of net
            if(inet >= 0 and !d_net[inet].is_global) {
                // Valid net that we need to compute the cost for
                g_net_t* net = &d_net[inet];                                        // pointer to net for convenience

                // Each thread in warp independently computes its own bounding box
                // We combine the bounding boxes using atomicMin and atomicMax
                const int num_blocks_in_net = net->num_blocks;                       // number of blocks net connects to
                const int block_list_start = net->index_start_block;
                const int n_iterations = (num_blocks_in_net / WARP_SIZE)
                                           + (num_blocks_in_net%WARP_SIZE?1:0);     // number of iterations that we need to do to cover all blocks

                // bounding box local to each thread
                // initialize it such that it doesn't affect min and max operations
                int* local_bb_nx_start = &bb_nx_start[warp_tid];
                int* local_bb_nx_end = &bb_nx_end[warp_tid];
                int* local_bb_ny_start = &bb_ny_start[warp_tid];
                int* local_bb_ny_end = &bb_ny_end[warp_tid];
                *local_bb_nx_start = global_nx+1;
                *local_bb_nx_end = 0;
                *local_bb_ny_start = global_ny+1;
                *local_bb_ny_end = 0;

                for(int b=0; b<n_iterations; b++) {
                    const int block_list_offset = b*WARP_SIZE + warp_tid;
                    if(block_list_offset < num_blocks_in_net) {                     // make sure we don't overflow in the block list
                        const int local_block_num = d_net_blocks[block_list_start+block_list_offset];
                        // Get the block and add it to local bounding box
                        g_block_t* local_block = &d_block[local_block_num];
                        *local_bb_nx_start = d_min(*local_bb_nx_start, local_block->x);
                        *local_bb_nx_end = d_max(*local_bb_nx_end, local_block->x);
                        *local_bb_ny_start = d_min(*local_bb_ny_start, local_block->y);
                        *local_bb_ny_end = d_max(*local_bb_ny_end, local_block->y);
                    }
                }

                // Combine all the bounding boxes using a reduction operation
                // The final result will be at the start of each shared memory array
                int total_warp_threads = WARP_SIZE;
                while(total_warp_threads > 1) {
                    int half_point = (total_warp_threads >> 1);     // divide by two
                    if(warp_tid < half_point) {
                        bb_nx_start[warp_tid] = d_min(bb_nx_start[warp_tid], bb_nx_start[warp_tid+half_point]);
                        bb_nx_end[warp_tid] = d_max(bb_nx_end[warp_tid], bb_nx_end[warp_tid+half_point]);
                        bb_ny_start[warp_tid] = d_min(bb_ny_start[warp_tid], bb_ny_start[warp_tid+half_point]);
                        bb_ny_end[warp_tid] = d_max(bb_ny_end[warp_tid], bb_ny_end[warp_tid+half_point]);
                    }
                    total_warp_threads = total_warp_threads >> 1;
                }

                // Now first thread needs to calculate the new cost and update the delta cost
                if(warp_tid == 0) {
                    // VPR does a final clipping of the bounding box (to remove IO tracks?)
                    const int bb_final_nx_start = d_max(d_min(*bb_nx_start, global_nx), 1);
                    const int bb_final_nx_end = d_max(d_min(*bb_nx_end, global_nx), 1);
                    const int bb_final_ny_start = d_max(d_min(*bb_ny_start, global_ny), 1);
                    const int bb_final_ny_end = d_max(d_min(*bb_ny_end, global_ny), 1);
                    // Store the net cost and id in a buffer
                    temp_net_costs[*valid_nets] = get_net_bb_cost(net, g_bb_t(bb_final_nx_start,bb_final_nx_end,bb_final_ny_start,bb_final_ny_end),
                                                                 d_chanx_place_cost_fac, d_chany_place_cost_fac);
                    temp_net_ids[*valid_nets] = inet;
                    // Compute the delta cost
                    delta_cost += temp_net_costs[*valid_nets] - d_net_cost[inet];
                    /*
                    printf("warp_tid=%d net_id=%5d \tbb_nx:%2d-%2d   bb_ny:%2d-%2d  cost=%f\n", warp_tid, inet,
                            bb_final_nx_start, bb_final_nx_end, bb_final_ny_start, bb_final_ny_end, temp_net_costs[*valid_nets]
                           );
                    */
                }

                *valid_nets += 1;
            }
        }

        return delta_cost;
    } else {
        return 0.0;
    }
}


// Check if move should be accepted
__device__ bool accept_swap(float delta_cost, float t, unsigned* seed) {
    // Always accept good moves
    if(delta_cost <= 0)
        return true;

    // Never accept bad moves at t=0
    if(t<=0)
        return false;

    // Accept bad moves with some probability
    int rand_int = rand(seed);
    float fnum = ((float) rand_int / powf(2,32)) + 0.5;      // float between 0 and 1
    float prob_fac = exp(-delta_cost / t);
    //printf("fnum=%f\n", fnum);
    return prob_fac > fnum;
}



// Dynamic shared memory array
extern __shared__ int dynamicSMEM[];

/*
 * Kernel
 */
__global__ void gpu_place_kernel(
        g_type_t* d_types, g_grid_t* d_grid, g_block_t* d_block, int* d_block_nets, g_net_t* d_net, float* d_net_cost, int* d_net_blocks,
        int num_blocks, int num_nets, int global_nx, int global_ny,
        unsigned* seeds,
        float** d_chanx_place_cost_fac, float** d_chany_place_cost_fac,
        float t, float rlim, int n_moves_per_warp, int* d_success_sum,
        float* d_nomalloc_net_costs, int* d_nomalloc_net_ids
        )
{
    // access thread id
    const int block_tid = threadIdx.x;
    const int block_wid = block_tid / WARP_SIZE;
    const int warp_tid = block_tid % WARP_SIZE;
    const int global_tid = blockIdx.y * (gridDim.x*blockDim.x) +
                           blockIdx.x * blockDim.x +
                           threadIdx.x;
    const int global_wid = global_tid / WARP_SIZE;
    //const int global_bid = blockIdx.y*gridDim.x + blockIdx.x;
    //const int num_thread_blocks = gridDim.x;
    //const int num_threads_per_block = blockDim.x;
    const int n_warps_per_block = blockDim.x/WARP_SIZE + (blockDim.x%WARP_SIZE?1:0);

    //const int nx = d_grid->nx;
    //const int ny = d_grid->ny;

    // Get the seed
    unsigned* seed = &seeds[global_tid];

    // Set up the array that first thread in warp uses to communicate locked cells to rest of the warp
    int* nx_from_array = (int*)dynamicSMEM;
    int* ny_from_array = (int*)&dynamicSMEM[n_warps_per_block];
    int* nx_to_array = (int*)&dynamicSMEM[n_warps_per_block*2];
    int* ny_to_array = (int*)&dynamicSMEM[n_warps_per_block*3];
    int* nx_from = &nx_from_array[block_wid];
    int* ny_from = &ny_from_array[block_wid];
    int* nx_to = &nx_to_array[block_wid];
    int* ny_to = &ny_to_array[block_wid];

    // Set up the array that warps use to combine bounding boxes
    const int bb_smem_start_index = n_warps_per_block*4;
    const int bb_smem_array_size = n_warps_per_block*WARP_SIZE;
    int* bb_nx_start_array = (int*)&dynamicSMEM[bb_smem_start_index];
    int* bb_nx_end_array = (int*)&dynamicSMEM[bb_smem_start_index+bb_smem_array_size*1];
    int* bb_ny_start_array = (int*)&dynamicSMEM[bb_smem_start_index+bb_smem_array_size*2];
    int* bb_ny_end_array = (int*)&dynamicSMEM[bb_smem_start_index+bb_smem_array_size*3];
    int* bb_nx_start = &bb_nx_start_array[block_wid*WARP_SIZE];
    int* bb_nx_end = &bb_nx_end_array[block_wid*WARP_SIZE];
    int* bb_ny_start = &bb_ny_start_array[block_wid*WARP_SIZE];
    int* bb_ny_end = &bb_ny_end_array[block_wid*WARP_SIZE];

    // Dynamically allocate the temporary buffers used for storing temporary net costs
    // Need 2, one for costs and one for net ids. Each is 2*num_pin because of two blocks
    // Only first thread in each warp reads/writes the buffers
    int num_pins = d_types[d_grid->type].num_pins;
    float* temp_net_costs;
    int* temp_net_ids;
    if(warp_tid == 0) {
#ifdef NO_KERNEL_MALLOC
        temp_net_costs = &d_nomalloc_net_costs[global_wid*2*MAX_PINS_PER_BLOCK];
        temp_net_ids = &d_nomalloc_net_ids[global_wid*2*MAX_PINS_PER_BLOCK];
#else
        temp_net_costs = (float*) malloc(2*num_pins*sizeof(float));
        temp_net_ids = (int*) malloc(2*num_pins*sizeof(int));
#endif
    }

    int local_success_sum = 0;                      // Keep track of local success rate

    // Do the swap tries
    for(unsigned i=0; i<n_moves_per_warp; i++) {

        if(warp_tid == 0) {     // only the first thread per warp acquires the lock

            bool lock_acquired = false;

            while(!lock_acquired) {
                // Select two valid locations to swap
                do {
                select_swap_candidates(
                        d_grid,
                        seed, rlim,
                        nx_from, ny_from, nx_to, ny_to,
                        g_bb_t(0,d_grid->nx-1,0,d_grid->ny-1)
                        );
                } while(!is_swap_valid(*nx_from, *ny_from, *nx_to, *ny_to, d_grid, d_block ));


                // Try to acquire locks on both cells and swap
                // If we can't acquire locks, select new candidates instead of retrying the lock
                // we don't want to wait a long time for the lock to be released
                // Note: since only one thread per warp is accessing the locks, we don't have to worry about SIMD stack related issues
                const int cell_from_index = *nx_from * d_grid->ny + *ny_from;
                const int cell_to_index = *nx_to * d_grid->ny + *ny_to;
                int* lock1 = &d_grid->lock[cell_from_index];
                int* lock2 = &d_grid->lock[cell_to_index];
                if(atomicCAS(lock1, 0, 1) == 0) {
                    if(atomicCAS(lock2, 0, 1) == 0) {

                        lock_acquired = true;
                    } else {
                        *lock1 = 0; // release the first lock
                    }
                }
            } // while not lock acquired

        } // first thread per warp only

        //__threadfence_block();  // make sure shared memory values are visible

        //  Do the swap
        if(warp_tid == 0) {
            do_swap(*nx_from, *ny_from, *nx_to, *ny_to,
                    d_grid, d_block);
        }
        //__threadfence_block();  // make sure the swap is visible to all threads in the warp


        int valid_nets = 0;
        float delta_cost = 0.0;

        // Get the delta cost from both the blocks
        // Only the first thread in the warp will get the valid result
        delta_cost += get_delta_cost_of_block(
                            warp_tid,
                            *nx_from, *ny_from,
                            bb_nx_start, bb_nx_end, bb_ny_start, bb_ny_end,
                            d_grid, d_block, d_block_nets, d_net, d_net_cost, d_net_blocks,
                            num_pins,
                            global_nx, global_ny,
                            d_chanx_place_cost_fac, d_chany_place_cost_fac,
                            temp_net_costs, temp_net_ids, &valid_nets
                       );
        delta_cost += get_delta_cost_of_block(
                            warp_tid,
                            *nx_to, *ny_to,
                            bb_nx_start, bb_nx_end, bb_ny_start, bb_ny_end,
                            d_grid, d_block, d_block_nets, d_net, d_net_cost, d_net_blocks,
                            num_pins,
                            global_nx, global_ny,
                            d_chanx_place_cost_fac, d_chany_place_cost_fac,
                            temp_net_costs, temp_net_ids, &valid_nets
                       );

        // If the swap is to be accepted, write out the new net costs
        // If not, call do_swap again to reverse the swap
        if(warp_tid == 0) {
            //printf("global_tid=%d delta_cost=%f\n", global_tid, delta_cost);
            if( accept_swap(delta_cost, t, seed) ) {
                // Swap accepted, write out the new costs
                for(int n=0; n<valid_nets; n++) {
                    const int inet = temp_net_ids[n];
                    d_net_cost[inet] = temp_net_costs[n];
                    //printf("global_tid=%d inet=%5d cost=%f\n", global_tid, inet, temp_net_costs[n]);
                }

                local_success_sum += 1;             // increment local success counter
            } else {
                // Swap rejected, call do_swap to undo it
                do_swap(*nx_from, *ny_from, *nx_to, *ny_to,
                                    d_grid, d_block);
                //__threadfence_block();  // make sure the swap is visible to all threads in the warp
            }
        }

        // Use threadfence to ensure writes are visible to all threads
        // Hardware doesn't require this before shared data is already marked volatile, but simulator needs this
        __threadfence();

        // Release the locks
        if(warp_tid == 0) {
            const int cell_from_index = *nx_from * d_grid->ny + *ny_from;
            const int cell_to_index = *nx_to * d_grid->ny + *ny_to;
            int* lock1 = &d_grid->lock[cell_from_index];
            int* lock2 = &d_grid->lock[cell_to_index];

            *lock1 = 0;
            *lock2 = 0;
        }

    }   // another swap

    // End of block processing
    if(warp_tid == 0) {
        // Atomically add the local success rate
        atomicAdd(d_success_sum, local_success_sum);

        // Free the dynamically allocated buffers
#ifdef NO_KERNEL_MALLOC
#else
        free(temp_net_costs);
        free(temp_net_ids);
#endif
    }

}

/*
 * Interface function between vpr and cuda kernel
 * Copy data structs received from vpr into required internal format
 */

// Host pointers
g_grid_t* g_grid_CLBs = NULL;           // Grid of CLBs
g_block_t* g_block = NULL;              // AOS holding block information
int* g_block_nets = NULL;               // Shared array of nets, each chunk corresponds to one block
g_net_t* g_net = NULL;                  // AOS holding net information
int* g_net_blocks = NULL;               // Shared array of blocks, each chunk corresponds to one net
g_type_t* g_types = NULL;
g_grid_map_t g_grid_map_CLBs;           // Host-only, used for mapping VPR's grid cells to our own grid cells

int net_list_size;                      // total size of shared net-list (used by blocks)
int block_list_size;                    // total size of shared block-list (used by nets)

// Device pointers
g_grid_t* d_grid_CLBs = NULL;
g_block_t* d_block = NULL;
int* d_block_nets = NULL;
g_net_t* d_net = NULL;
int* d_net_blocks = NULL;
float* d_net_cost = NULL;
g_type_t* d_types = NULL;

__constant__ float **d_chanx_place_cost_fac = NULL;
__constant__ float **d_chany_place_cost_fac = NULL;  // net cost factors

unsigned* d_seeds = NULL;
bool seeds_initialized = false;  // we want to initialize the seeds only once

extern "C"
void gpu_place_launch_kernel (
        int nx, int ny,
        int num_blocks, int num_nets,
        float t, float rlim, int* move_lim, int* success_sum
        )
{
    // Set up the grid
    const int n_warps_per_block = 16;        // 16 warps = 512 threads per block
    //const int n_x_nodes_per_block = 256;    // each thread block responsible for n_x x n_y sized grid of nodes
    //const int n_y_nodes_per_block = 256;

    const int grid_dim_x = 16;
    const int grid_dim_y = 1;

    const int n_threads_per_block = n_warps_per_block * WARP_SIZE;
    const int n_total_warps = n_warps_per_block * grid_dim_x * grid_dim_y;

    // Divide up move_lim among all warps, and report back how many moves we actually tried
    printf("\tmove_lim_requested=%d\n",*move_lim);
    // hack to override moves per warp
    // TODO: make this an option
    const int n_moves_per_warp = 1;     //*move_lim / n_total_warps;
    *move_lim = n_moves_per_warp * n_total_warps;


    printf("\tn_warps_per_block=%d\n",n_warps_per_block);
    printf("\tn_threads_per_block=%d\n",n_threads_per_block);
    printf("\tgrid_dim_x=%d\n",grid_dim_x);
    printf("\tgrid_dim_y=%d\n",grid_dim_y);
    printf("\tn_total_warps=%d\n",n_total_warps);
    printf("\tg_grid_CLBs->nx=%d\n",g_grid_CLBs->nx);
    printf("\tg_grid_CLBs->ny=%d\n",g_grid_CLBs->ny);

    printf("\tn_moves_per_warp=%d\n",n_moves_per_warp);


    dim3 dimBlock(n_threads_per_block, 1, 1);
    dim3 dimGrid(grid_dim_x, grid_dim_y, 1);
    int smemSize = 0;
    smemSize += sizeof(int)*n_warps_per_block*4;            // this chunk is for passing nx/ny_from/to values among threads in a warp after acquiring a lock
    smemSize += sizeof(int)*n_warps_per_block*4*WARP_SIZE;  // this chunk is for computing the combined bounding box for each warp, each thread needs 4 words (xmin, xmax, ymin, ymax)

    // Set up the seeds - we do it here because we need to know how many threads there are
    const int n_total_threads = n_threads_per_block*grid_dim_x*grid_dim_y;
    if(!seeds_initialized) {
        int* h_seed = (int*) malloc(n_total_threads * sizeof(int));
        for(int t=0; t<n_total_threads; t++) {
            h_seed[t] = t;
        }
        cutilSafeCall( cudaMalloc( (void**) &d_seeds, n_total_threads*sizeof(unsigned) ) );
        cutilSafeCall( cudaMemcpy( d_seeds, h_seed, n_total_threads*sizeof(unsigned), cudaMemcpyHostToDevice) );
        seeds_initialized = true;
    }

    // Set up device space and copy over:
    //      success_sum
    //      bb_cost
    int* d_success_sum;
    cutilSafeCall( cudaMalloc( (void**) &d_success_sum, sizeof(int) ) );
    cutilSafeCall( cudaMemcpy( d_success_sum, success_sum, sizeof(int), cudaMemcpyHostToDevice) );
    float* d_bb_cost;
    cutilSafeCall( cudaMalloc( (void**) &d_bb_cost, sizeof(int) ) );

    // Setup up preallocated device memory if dynamic allocation is disabled
    float* d_nomalloc_net_costs;
    int* d_nomalloc_net_ids;
#ifdef NO_KERNEL_MALLOC
    cutilSafeCall( cudaMalloc( (void**) &d_nomalloc_net_costs, n_total_warps*2*MAX_PINS_PER_BLOCK*sizeof(float) ) );
    cutilSafeCall( cudaMalloc( (void**) &d_nomalloc_net_ids, n_total_warps*2*MAX_PINS_PER_BLOCK*sizeof(int) ) );
#endif

    // LAUNCH KERNEL HERE
#ifdef GPU_VERBOSE
    printf("GPU: RUNNING KERNEL...");
#endif
    gpu_place_kernel<<< dimGrid, dimBlock, smemSize >>>(
            d_types, d_grid_CLBs, d_block, d_block_nets, d_net, d_net_cost, d_net_blocks,
            num_blocks, num_nets, nx, ny,
            d_seeds,
            d_chanx_place_cost_fac, d_chany_place_cost_fac,
            t, rlim, n_moves_per_warp, d_success_sum,
            d_nomalloc_net_costs, d_nomalloc_net_ids
            );
#ifdef GPU_VERBOSE
    printf(" done\n");
#endif

    // Copy back
    //      success_sum
    //      bb_cost
    cutilSafeCall( cudaMemcpy( success_sum, d_success_sum, sizeof(int), cudaMemcpyDeviceToHost) );
    cudaFree(d_success_sum);

#ifdef NO_KERNEL_MALLOC
    cudaFree(d_nomalloc_net_costs);
    cudaFree(d_nomalloc_net_ids);
#endif

#ifdef GPU_VERBOSE
    printf("success_sum=%d\n", *success_sum);
#endif

}


// This function updates the net costs on gpu
// This is needed because VPR may recompute the net costs
// This assumes that d_net_cost has been already allocated
extern "C"
void gpu_update_net_costs_on_gpu(
        float* net_cost, int num_nets
        )
{
    // Copy data to device
    cutilSafeCall( cudaMemcpy( d_net_cost, net_cost, num_nets*sizeof(float), cudaMemcpyHostToDevice) );
}

// This function is to copy only the net_costs from gpu back to VPR
// This is used to recompute the cost on CPU
// Note that net_costs will be inaccurate due to races
extern "C"
void gpu_update_net_costs_on_vpr(
        float* net_cost, int num_nets
        )
{
    // Copy data to host
    cutilSafeCall( cudaMemcpy( net_cost, d_net_cost, num_nets*sizeof(float), cudaMemcpyDeviceToHost) );
}

extern "C"
void gpu_place_copy_data_to_gpu(
        int num_types, struct s_type_descriptor * type_descriptors,
        struct s_grid_tile** grid, int nx, int ny,
        t_block* block, int num_blocks,
        struct s_net* clb_net, float* net_cost, int num_nets,
        float **chanx_place_cost_fac, float **chany_place_cost_fac
        )
{
    // Copy data from VPR into internal format
    gpu_transform_data_from_vpr(num_types, type_descriptors,
                                &g_types,
                                grid, nx, ny,
                                &g_grid_CLBs, &g_grid_map_CLBs,
                                block, num_blocks,
                                &g_block, &g_block_nets, &net_list_size,
                                clb_net, num_nets,
                                &g_net, &g_net_blocks, &block_list_size
                                );


    gpu_copy_data_to_device(g_types, g_grid_CLBs, g_block, g_block_nets, g_net, net_cost, g_net_blocks,
                            &d_types, &d_grid_CLBs, &d_block, &d_block_nets, &d_net, &d_net_cost, &d_net_blocks,
                            num_types, num_blocks, num_nets, net_list_size, block_list_size,
                            chanx_place_cost_fac, chany_place_cost_fac, &d_chanx_place_cost_fac, &d_chany_place_cost_fac,
                            nx, ny);
}

extern "C"
void gpu_place_copy_data_to_vpr(
        int num_types, struct s_type_descriptor * type_descriptors,
        struct s_grid_tile** grid, int nx, int ny,
        t_block* block, int num_blocks,
        struct s_net* clb_net, float* net_cost, int num_nets
        )
{
    gpu_copy_data_to_host(d_types, d_grid_CLBs, d_block, d_block_nets, d_net, d_net_cost, d_net_blocks,
                          g_types, g_grid_CLBs, g_block, g_block_nets, g_net, net_cost, g_net_blocks,
                          num_types, num_blocks, num_nets, net_list_size, block_list_size);

    // Copy data back to vpr
    gpu_transform_data_to_vpr(g_types, num_types,
                              type_descriptors,
                              g_grid_CLBs, &g_grid_map_CLBs,
                              grid,
                              g_block, g_block_nets, num_blocks,
                              block,
                              g_net, g_net_blocks, num_nets,
                              clb_net
                              );
}


/*
 * Copy vpr data into required representation
 *
 * Assumptions:
 *     1. IO blocks are on the outside of grid
 *     2. Each column can only contain blocks on 1 type, plus empty blocks
 *     3. CLB columns don't have empty blocks (at least not on the periphery)
 */
void gpu_transform_data_from_vpr (
        int num_types, struct s_type_descriptor * type_descriptors,
        g_type_t** g_type_p,
        struct s_grid_tile** grid, int nx, int ny,
        g_grid_t** g_grid_p, g_grid_map_t* g_grid_map,
        t_block* block, int num_blocks,
        g_block_t** g_block_p, int** g_block_nets_p, int* net_list_size,
        struct s_net* clb_net, int num_nets,
        g_net_t** g_net_p, int** g_net_blocks_p, int* block_list_size
        )
{

#ifdef GPU_VERBOSE
    printf("GPU: Copy data from VPR to interface\n");
#endif

    // Copy all the types
    *g_type_p = (g_type_t*) malloc(num_types*sizeof(g_type_t));
    g_type_t* g_type = *g_type_p;
    for(int i=0; i<num_types; i++) {
        g_type[i].index = i;
        g_type[i].num_cells = type_descriptors[i].num_instances_type;
        g_type[i].capacity = type_descriptors[i].capacity;
        g_type[i].num_pins = type_descriptors[i].num_pins;
    }

    // Copy all the CLBs into grid
    // TODO: For now, use the string to find clbs

    // Find CLB info and allocate space for copying
    *g_grid_p = (g_grid_t*) malloc(sizeof(g_grid_t));
    g_grid_t* g_grid = *g_grid_p;
    for(int i = 0; i < num_types; i++)
    {
        if(strcmp(type_descriptors[i].name,"clb")==0) {
            // Found clb, allocate members of g_grid
            g_grid->type = g_type[i].index;
            g_grid->num_cells = g_type[g_grid->type].num_cells;
            g_grid->usage = (int*) malloc(g_grid->num_cells * sizeof(int));
            g_grid->blocks = (int*) malloc(g_grid->num_cells * g_type[g_grid->type].capacity * sizeof(int));
            g_grid->x = (int*) malloc(g_grid->num_cells * sizeof(int));
            g_grid->y = (int*) malloc(g_grid->num_cells * sizeof(int));
            g_grid->lock = (int*) calloc(g_grid->num_cells, sizeof(int));

            g_grid_map->num_cells = g_grid->num_cells;
            g_grid_map->x = (int*) malloc(g_grid->num_cells * sizeof(int));
            g_grid_map->y = (int*) malloc(g_grid->num_cells * sizeof(int));
        }
    }
    assert(g_grid->num_cells > 0);

    // Copy the CLBs in
    int cells_copied = 0;
    g_grid->ny = ny;            // # of rows are the same
    g_grid->nx = 0;
    for(int x=1; x<=nx; x++) {
        if(strcmp(grid[x][1].type->name,"clb")==0) {
            // Column belongs to this CLB
            g_grid->nx += 1;
            for(int y=1; y<=ny; y++) {
                // Copy usage
                g_grid->usage[cells_copied] = grid[x][y].usage;

                // Copy each block id
                for(int z=0; z<g_type[g_grid->type].capacity; z++)
                    g_grid->blocks[z*g_grid->num_cells + cells_copied] = grid[x][y].blocks[z];

                // Record the x,y we copied from
                g_grid->x[cells_copied] = x;
                g_grid->y[cells_copied] = y;
                g_grid_map->x[cells_copied] = x;
                g_grid_map->y[cells_copied] = y;

                cells_copied++;
            }
        }
    }
    assert(cells_copied == g_grid->num_cells);
    assert(g_grid->nx*g_grid->ny == cells_copied);


    // Copy the blocks in
    // Since we have a single array for the blocks' net-list, let's count the total number of nets all the blocks need to store
    *net_list_size = 0;
    for(int b=0; b<num_blocks; b++) {
        *net_list_size += block[b].type->num_pins;
    }

    *g_block_p = (g_block_t*) malloc(num_blocks * sizeof(g_block_t));
    g_block_t* g_block = *g_block_p;
    *g_block_nets_p = (int*) malloc(*net_list_size * sizeof(int));
    int* g_block_nets = *g_block_nets_p;

    int block_net_list_index = 0;
    for(int b=0; b<num_blocks; b++) {
        g_block[b].x = block[b].x;
        g_block[b].y = block[b].y;
        g_block[b].z = block[b].z;
        g_block[b].type = block[b].type->index;
        g_block[b].index_start_net = block_net_list_index;
        for(int n=0; n<g_type[g_block[b].type].num_pins; n++) {
            assert(block_net_list_index < *net_list_size);
            g_block_nets[block_net_list_index] = block[b].nets[n];
            block_net_list_index++;
        }
    }
    assert(block_net_list_index==*net_list_size);

    // Copy nets in
    // Since we have a single array for the nets' block-list, let's count the total number of blocks all the nets need to store
    *block_list_size = 0;
    for(int n=0; n<num_nets; n++)
        // align each net's block_list to WARP_SIZE to ensure coalescing
        *block_list_size += (clb_net[n].num_sinks+1) + (WARP_SIZE - ((clb_net[n].num_sinks+1)%WARP_SIZE));

    // Allocate and fill the net structs and net_block list
    *g_net_p = (g_net_t*) malloc(num_nets * sizeof(g_net_t));
    *g_net_blocks_p = (int*) malloc(*block_list_size * sizeof(int));
    g_net_t* g_net = *g_net_p;
    int* g_net_blocks = *g_net_blocks_p;

    int net_block_list_index = 0;
    for(int n=0; n<num_nets; n++) {
        g_net[n].num_blocks = (clb_net[n].num_sinks+1);
        g_net[n].is_global = clb_net[n].is_global;
        g_net[n].is_const_gen = clb_net[n].is_const_gen;
        g_net[n].index_start_block = net_block_list_index;
        for(int b=0; b<g_net[n].num_blocks; b++) {
            g_net_blocks[net_block_list_index+b] = clb_net[n].node_block[b];
        }
        net_block_list_index += (clb_net[n].num_sinks+1) + (WARP_SIZE - ((clb_net[n].num_sinks+1)%WARP_SIZE));
    }
    assert(net_block_list_index == *block_list_size);
}

/*
 * Copy kernel modified data back to vpr
 * The grid is copied from g_grid to grid using the g_grid_map mapping
 * Blocks g_block and nets g_net storage is simply freed
 */
void gpu_transform_data_to_vpr (
        g_type_t* g_type, int num_types,
        struct s_type_descriptor * type_descriptors,
        g_grid_t* g_grid, g_grid_map_t* g_grid_map,
        struct s_grid_tile** grid,
        g_block_t* g_block, int* g_block_nets, int num_blocks,
        t_block* block,
        g_net_t* g_net, int* g_net_blocks, int num_nets,
        struct s_net* clb_net
        )
{

#ifdef GPU_VERBOSE
    printf("GPU: Copy data from interface to VPR\n");
#endif

    // Copy type data back to VPR
    // Read only data, check instead of copy
    for(int i=0; i<num_types; i++) {
        assert(type_descriptors[i].num_instances_type == g_type[i].num_cells);
        assert(type_descriptors[i].capacity == g_type[i].capacity);
        assert(type_descriptors[i].num_pins == g_type[i].num_pins);
        assert(type_descriptors[i].index == g_type[i].index);
    }

    // Copy grid data back to VPR
    for(int i=0; i<g_grid->num_cells; i++) {
        int x = g_grid_map->x[i];
        int y = g_grid_map->y[i];
        assert(g_grid->x[i] == x);
        assert(g_grid->y[i] == y);
        grid[x][y].usage = g_grid->usage[i];
        for(int z=0; z<g_type[g_grid->type].capacity; z++)
            grid[x][y].blocks[z] = g_grid->blocks[z*g_grid->num_cells + i];
    }

    // Copy block data back to VPR
    for(int b=0; b<num_blocks; b++) {
        block[b].x = g_block[b].x;
        block[b].y = g_block[b].y;
        block[b].z = g_block[b].z;
        assert( block[b].type->index == g_type[g_block[b].type].index);
        int block_net_index = g_block[b].index_start_net;
        for(int n=0; n<g_type[g_block[b].type].num_pins; n++) {
            // Read only data, check instead of copy
            assert(block[b].nets[n] == g_block_nets[block_net_index + n]);
        }
    }

    // Copy net data back to VPR
    // Read-only data, check instead of copy
    for(int n=0; n<num_nets; n++) {
        assert(clb_net[n].num_sinks+1 == g_net[n].num_blocks);
        assert(clb_net[n].is_global == g_net[n].is_global);
        assert(clb_net[n].is_const_gen == g_net[n].is_const_gen);
        int net_block_list_index = g_net[n].index_start_block;
        for(int b=0; b<g_net[n].num_blocks; b++) {
            assert(clb_net[n].node_block[b] == g_net_blocks[net_block_list_index + b]);
        }
    }
}

/*
 * Copy host data to device
 */
void gpu_copy_data_to_device (
        g_type_t* g_type, g_grid_t* g_grid, g_block_t* g_block, int* g_block_nets, g_net_t* g_net, float* g_net_cost, int* g_net_blocks,
        g_type_t** d_type_p, g_grid_t** d_grid_p, g_block_t** d_block_p, int** d_block_nets_p, g_net_t** d_net_p, float** d_net_cost_p, int** d_net_blocks_p,
        int num_types, int num_blocks, int num_nets, int net_list_size, int block_list_size,
        float **g_chanx, float **g_chany, float*** d_chanx, float*** d_chany,
        int nx, int ny
        )
{
#ifdef GPU_VERBOSE
    printf("GPU: Copy data from host to device\n");
#endif

    // Types
    // Simple AOS
    cutilSafeCall( cudaMalloc( (void**) d_type_p, num_types*sizeof(g_type_t)) );
    cutilSafeCall( cudaMemcpy( *d_type_p, g_type, num_types*sizeof(g_type_t), cudaMemcpyHostToDevice) );
    //printf("\t\t ...done copying types\n");


    // Grid - allocate and copy grid struct
    // Since this is a SOA, we have to do the following:
    //        1. Make a temporary copy of the host grid struct on the host
    //        2. Allocate all arrays on the device and update the grid copy to point to device arrays
    //        3. Copy arrays from host to device
    //        4. Allocate grid struct on device and copy host copy to device
    g_grid_t h_grid = *g_grid;        // 1. temporary copy of grid struct on host
    // 2. Allocate on device and update host grid copy
    cutilSafeCall( cudaMalloc( (void**) &(h_grid.usage), g_grid->num_cells * sizeof(int)) );
    cutilSafeCall( cudaMalloc( (void**) &(h_grid.x), g_grid->num_cells * sizeof(int)) );
    cutilSafeCall( cudaMalloc( (void**) &(h_grid.y), g_grid->num_cells * sizeof(int)) );
    cutilSafeCall( cudaMalloc( (void**) &(h_grid.blocks), g_grid->num_cells * g_type[g_grid->type].capacity * sizeof(int)) );
    cutilSafeCall( cudaMalloc( (void**) &(h_grid.lock), g_grid->num_cells * sizeof(int)) );
    // 3. Copy arrays from host to device
    cutilSafeCall( cudaMemcpy( h_grid.usage, g_grid->usage, g_grid->num_cells * sizeof(int), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMemcpy( h_grid.x, g_grid->x, g_grid->num_cells * sizeof(int), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMemcpy( h_grid.y, g_grid->y, g_grid->num_cells * sizeof(int), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMemcpy( h_grid.blocks, g_grid->blocks, g_grid->num_cells * g_type[g_grid->type].capacity * sizeof(int), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMemcpy( h_grid.lock, g_grid->lock, g_grid->num_cells * sizeof(int), cudaMemcpyHostToDevice) );
    // 4. Allocate grid on device and copy from host to device
    cutilSafeCall( cudaMalloc( (void**) d_grid_p, sizeof(g_grid_t)) );
    cutilSafeCall( cudaMemcpy( *d_grid_p, &h_grid, sizeof(g_grid_t), cudaMemcpyHostToDevice) );
    //printf("\t\t ...done copying grid\n");

    // Blocks and net-list
    // Simple AOS and array
    cutilSafeCall( cudaMalloc( (void**) d_block_p, num_blocks*sizeof(g_block_t)) );
    cutilSafeCall( cudaMemcpy( *d_block_p, g_block, num_blocks*sizeof(g_block_t), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMalloc( (void**) d_block_nets_p, net_list_size*sizeof(int)) );
    cutilSafeCall( cudaMemcpy( *d_block_nets_p, g_block_nets, net_list_size*sizeof(int), cudaMemcpyHostToDevice) );
    //printf("\t\t ...done copying blocks\n");

    // Nets and block-list
    // Simple AOS and array
    cutilSafeCall( cudaMalloc( (void**) d_net_p, num_nets*sizeof(g_net_t)) );
    cutilSafeCall( cudaMemcpy( *d_net_p, g_net, num_nets*sizeof(g_net_t), cudaMemcpyHostToDevice) );
    cutilSafeCall( cudaMalloc( (void**) d_net_blocks_p, block_list_size*sizeof(int)) );
    cutilSafeCall( cudaMemcpy( *d_net_blocks_p, g_net_blocks, block_list_size*sizeof(int), cudaMemcpyHostToDevice) );
    //printf("\t\t ...done copying nets\n");
    // Net costs
    cutilSafeCall( cudaMalloc( (void**) d_net_cost_p, num_nets*sizeof(float)) );
    cutilSafeCall( cudaMemcpy( *d_net_cost_p, g_net_cost, num_nets*sizeof(float), cudaMemcpyHostToDevice) );



    // chan_x/y arrays are tricky, they are triangular arrays
    cutilSafeCall( cudaMalloc( (void**) d_chanx, (ny+1)*sizeof(float *)) );
    float** h_chanx = (float**) malloc((ny+1)*sizeof(float *));
    for(int i = 0; i <= ny; i++) {
        float* temp;
        cutilSafeCall( cudaMalloc( (void**) &temp, (i+1)*sizeof(float)) );
        cutilSafeCall( cudaMemcpy( temp, g_chanx[i], (i+1)*sizeof(float), cudaMemcpyHostToDevice) );
        h_chanx[i] = temp;
    }
    cutilSafeCall( cudaMemcpy( *d_chanx, h_chanx, (ny+1)*sizeof(float *), cudaMemcpyHostToDevice) );
    free(h_chanx);

    cutilSafeCall( cudaMalloc( (void**) d_chany, (nx+1)*sizeof(float *)) );
    float** h_chany = (float**) malloc((nx+1)*sizeof(float *));
    for(int i = 0; i <= nx; i++) {
        float* temp;
        cutilSafeCall( cudaMalloc( (void**) &temp, (i+1)*sizeof(float)) );
        cutilSafeCall( cudaMemcpy( temp, g_chany[i], (i+1)*sizeof(float), cudaMemcpyHostToDevice) );
        h_chany[i] = temp;
    }
    cutilSafeCall( cudaMemcpy( *d_chany, h_chany, (nx+1)*sizeof(float *), cudaMemcpyHostToDevice) );
    free(h_chany);

}

/*
 * Copy data from device back to host (into internal structures)
 */
void gpu_copy_data_to_host (
        g_type_t* d_type, g_grid_t* d_grid, g_block_t* d_block, int* d_block_nets, g_net_t* d_net, float* d_net_cost, int* d_net_blocks,
        g_type_t* g_type, g_grid_t* g_grid, g_block_t* g_block, int* g_block_nets, g_net_t* g_net, float* g_net_cost, int* g_net_blocks,
        int num_types, int num_blocks, int num_nets, int net_list_size, int block_list_size
        )
{
    //printf("GPU: Copy data from device to host\n");

    // Types
    #ifdef COPY_EVERYTHING_DEVICE_TO_HOST
        cutilSafeCall( cudaMemcpy( g_type, d_type, num_types*sizeof(g_type_t), cudaMemcpyDeviceToHost) );
        //printf("\t\t ...done copying types\n");
    #endif

    // Grid
    g_grid_t h_grid;
    cutilSafeCall( cudaMemcpy( &h_grid, d_grid, sizeof(g_grid_t), cudaMemcpyDeviceToHost) );
    #ifdef COPY_EVERYTHING_DEVICE_TO_HOST
        g_grid->num_cells = h_grid.num_cells;
        cutilSafeCall( cudaMemcpy( g_grid->x, h_grid.x, g_grid->num_cells*sizeof(int), cudaMemcpyDeviceToHost) );
        cutilSafeCall( cudaMemcpy( g_grid->y, h_grid.y, g_grid->num_cells*sizeof(int), cudaMemcpyDeviceToHost) );
    #endif
    cutilSafeCall( cudaMemcpy( g_grid->usage, h_grid.usage, g_grid->num_cells*sizeof(int), cudaMemcpyDeviceToHost) );
    cutilSafeCall( cudaMemcpy( g_grid->blocks, h_grid.blocks, g_grid->num_cells*g_type[g_grid->type].capacity*sizeof(int), cudaMemcpyDeviceToHost) );
    //printf("\t\t ...done copying grid\n");

    // Block
    cutilSafeCall( cudaMemcpy( g_block, d_block, num_blocks*sizeof(g_block_t), cudaMemcpyDeviceToHost) );
    #ifdef COPY_EVERYTHING_DEVICE_TO_HOST
        cutilSafeCall( cudaMemcpy( g_block_nets, d_block_nets, net_list_size*sizeof(int), cudaMemcpyDeviceToHost) );
    #endif
        //printf("\t\t ...done copying blocks\n");

    // Nets
    #ifdef COPY_EVERYTHING_DEVICE_TO_HOST
        cutilSafeCall( cudaMemcpy( g_net, d_net, num_nets*sizeof(g_net_t), cudaMemcpyDeviceToHost) );
        cutilSafeCall( cudaMemcpy( g_net_blocks, d_net_blocks, block_list_size*sizeof(int), cudaMemcpyDeviceToHost) );
        //printf("\t\t ...done copying nets\n");
    #endif
    // Net costs
    cutilSafeCall( cudaMemcpy( g_net_cost, d_net_cost, num_nets*sizeof(float), cudaMemcpyDeviceToHost) );
}

// Free both the internal representation (g_*) and device allocated (d_*) data
extern "C"
void gpu_free_data() {

#ifdef GPU_VERBOSE
    printf("gpu_free_data\n");
#endif

    // Free internally allocated memory
    // Free every malloc'ed memory
    free(g_block);
    free(g_block_nets);

    free(g_net);
    free(g_net_blocks);

    free(g_grid_CLBs->usage);
    free(g_grid_CLBs->blocks);
    free(g_grid_CLBs->x);
    free(g_grid_CLBs->y);
    free(g_grid_map_CLBs.x);
    free(g_grid_map_CLBs.y);
    free(g_grid_CLBs);

    // Free memory on device
    // Grid
    g_grid_t h_grid_CLBs;
    cutilSafeCall( cudaMemcpy( &h_grid_CLBs, d_grid_CLBs, sizeof(g_grid_t), cudaMemcpyDeviceToHost) );
    cudaFree(h_grid_CLBs.x);
    cudaFree(h_grid_CLBs.y);
    cudaFree(h_grid_CLBs.usage);
    cudaFree(h_grid_CLBs.blocks);

    cudaFree(d_types);
    cudaFree(d_grid_CLBs);
    cudaFree(d_block);
    cudaFree(d_block_nets);
    cudaFree(d_net);
    cudaFree(d_net_cost);
    cudaFree(d_net_blocks);
    // TODO: free the chanx/y arrays
}

#endif // #ifndef _GPU_PLACE_KERNEL_H_
