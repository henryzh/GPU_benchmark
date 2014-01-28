#include "vpr_types.h"

void gpu_update_net_costs_on_gpu(
        float* net_cost, int num_nets
        );

void gpu_update_net_costs_on_vpr(
        float* net_cost, int num_nets
        );

void gpu_place_copy_data_to_gpu(
        int num_types, struct s_type_descriptor * type_descriptors,
        struct s_grid_tile** grid, int nx, int ny,
        t_block* block, int num_blocks,
        struct s_net* clb_net, float* net_cost, int num_nets,
        float **chanx_place_cost_fac, float **chany_place_cost_fac
        );

void gpu_place_copy_data_to_vpr(
        int num_types, struct s_type_descriptor * type_descriptors,
        struct s_grid_tile** grid, int nx, int ny,
        t_block* block, int num_blocks,
        struct s_net* clb_net, float* net_cost, int num_nets
        );

void gpu_free_data();

void gpu_place_launch_kernel(
        int nx, int ny,
        int num_blocks, int num_nets,
        float t, float rlim, int* move_lim, int* success_sum
        );
