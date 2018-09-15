#ifndef _FPGA_SIMULATOR_H_
#define _FPGA_SIMULATOR_H_

// ========================
// = Standard C Libraries =
// ========================
#include "hog.hpp"
#include <cstdio>     // printf
#include <ctime>      // time() for random seed
#include <cmath>      // fabs, fmax, ...
#include <vector>     // std::vector for softmax calculation
#include <algorithm>  // sort, reverse (on std::vector)

// ==================
// = FPGA Algorithm =
// ==================
 // top-level FPGA module
void set_fpga_config(int row,int col, int cell_row,int cell_col, int bloc_row,int bloc_col,int ori);
void load_prepared_input_image(data_t *input_image, const char *filename,int win, int hin);
void copy_input_image_to_FPGA(data_t *image);
void copy_results_from_FPGA(data_t *results);
int main();
#endif
