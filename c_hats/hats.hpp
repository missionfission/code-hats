#ifndef hats_HPP_
#define hats_HPP_

#include <iostream>
#include <string.h>
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ap_int.h"
//#define NBITS2(n) ((n & 2) ? 1 : 0)
//#define NBITS4(n) ((n & (0xC)) ? (2 + NBITS2(n >> 2)) : (NBITS2(n)))
//#define NBITS8(n) ((n & 0xF0) ? (4 + NBITS4(n >> 4)) : (NBITS4(n)))
//#define NBITS16(n) ((n & 0xFF00) ? (8 + NBITS8(n >> 8)) : (NBITS8(n)))
//#define NBITS32(n) ((n & 0xFFFF0000) ? (16 + NBITS16(n >> 16)) : (NBITS16(n)))
//#define NBITS(n) ((n) == 0 ? 1 : NBITS32((n)) + 1)
typedef ap_uint<6> addr_t;  
typedef ap_uint<6> int_t;  
typedef ap_uint<10> tm_t;
typedef ap_fixed<8,4> data_t;
typedef ap_fixed<8,4> comp_t;

using namespace std;
struct aer{
addr_t x,y;
tm_t t;
bool p;
};
const int rho = 7;
const int ents = 50;
const int n = 5880;
const int tau=100000;
const int tot_cell=120;
comp_t hats(aer event[n],int_t n,comp_t *weights);

#endif 
