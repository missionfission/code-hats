#include "cpu.hpp"

// ======================================
// = Global Variables (Memory Pointers) =
// ======================================
// Pointers to Shared DRAM Memory
data_t *SHARED_DRAM;


int main()
{

int result_size = n_blocks_col*n_blocks_row*b_col*b_row*orient;
int image_size=s_row*s_col;
int total_size=image_size+result_size;
SHARED_DRAM = (data_t *)malloc(total_size);
int win =s_row;
int hin = s_col;
printf("CPU: FPGA DRAM Memory Allocation:\n");
printf("     region: %lu – %lu\n", (long)SHARED_DRAM, (long)(SHARED_DRAM + total_size));
data_t *input_image = (data_t *)malloc(win * hin * sizeof(data_t));
load_prepared_input_image(input_image, "input.bin", win, hin);
copy_input_image_to_FPGA(input_image);
printf("Entering FPGA \n");
fflush(stdout);
hog((data_t *)SHARED_DRAM, 0);
data_t *results = (data_t *)malloc(result_size);
copy_results_from_FPGA(results);
return 0;
}

void copy_input_image_to_FPGA(data_t *image) {
  int win =s_row;
  int hin = s_col;
  int input_img_size = win * hin * sizeof(data_t);
// Info:
  printf("CPU: Copy Input Data: %dKB (input image)\n", input_img_size / 1024);
  // Copy Input Data:
  memcpy(SHARED_DRAM, image, input_img_size);
}

void load_prepared_input_image(data_t *input_image, const char *filename,int win, int hin) {
  // calculate size of input data
  int num_pixels = win * hin;
  printf("CPU: Loading Input from File %s, %lu kBytes.\n", filename,num_pixels * sizeof(data_t) / 1024);

  // load binary data from file
  FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("ERROR: File %s could not be opened!\n", filename);
    exit(-1);
  }
  fread(input_image, sizeof(data_t), num_pixels, infile);
  fclose(infile);
}
void copy_results_from_FPGA(data_t *results) {
//TODO Fill size here
int result_offset = 0;
int result_size = n_blocks_col*n_blocks_row*b_col*b_row*orient;
  printf("CPU: Copy Results from FPGA DRAM: %d Bytes\n", result_size);
  memcpy(results, SHARED_DRAM + result_offset, result_size);
}

