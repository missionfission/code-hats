
#ifdef __SYNTHESIS__
#include <ap_utils.h>
#include <hls_math.h>
#endif

typedef  float data_t;
typedef  int dimension_t;
typedef  int var_t;

///////////////////////////////////////////////////////////////////////////////////
extern const var_t s_row =128;
extern const var_t s_col=64;
extern const var_t c_row=6;
extern const var_t c_col=6;
extern const var_t b_row=2;
extern const var_t b_col=2;
extern const var_t n_cells_row=21;
extern const var_t n_cells_col=10;
extern const var_t orient=9;
extern const var_t n_blocks_row=20;
extern const var_t n_blocks_col=9;
extern const int DRAM_DEPTH = 11000;
extern const int N_PE=8;


//Variable Bit Implementation

//#define NBITS2(n) ((n & 2) ? 1 : 0)
//#define NBITS4(n) ((n & (0xC)) ? (2 + NBITS2(n >> 2)) : (NBITS2(n)))
//#define NBITS8(n) ((n & 0xF0) ? (4 + NBITS4(n >> 4)) : (NBITS4(n)))
//#define NBITS16(n) ((n & 0xFF00) ? (8 + NBITS8(n >> 8)) : (NBITS8(n)))
//#define NBITS32(n) ((n & 0xFFFF0000) ? (16 + NBITS16(n >> 16)) : (NBITS16(n)))
//#define NBITS(n) ((n) == 0 ? 1 : NBITS32((n)) + 1)

//const int NUM_IMG_CACHE_LINES = 4;
//const int N_PE = 8; // Number of Processing Elements

void hog(data_t *SHARED_DRAM, unsigned int input_offset);
void load_image(data_t *SHARED_DRAM);
void secondstage();
void compute_magnitude();
void thirdstage();
void fourthstage();
data_t cell_hog(int r,int c, int start,int end);

