#ifndef hats_HPP_
#define hats_HPP_

#include <iostream>
#include <string.h>
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ap_int.h"
#include "ap_fixed.h"
//
//typedef ap_int<10> addr_t;
//typedef ap_int<18> tm_t;
//typedef ap_int<12> int_t;
typedef int addr_t;
typedef int  tm_t;
typedef int int_t;
typedef float comp_t;
typedef float hist_t;
typedef float sum_t;
//typedef ap_fixed<24,12> comp_t;
//typedef ap_int<12>  hist_t;
//typedef ap_fixed<24,12>  sum_t;
using namespace std;
struct aer{
addr_t x,y;
tm_t t;
bool p;
bool reset;
};
const int P=8;
const int p_factor=15;
const int rho = 7;
const int N_PE=7;
const int n = 5880;
const long int tau=1000000;
const int tot_cell=120/P;
sum_t hats(aer events[] ,int_t n);
void computeHistogram(comp_t hist[rho][rho],aer event,aer memory[],int_t size);
sum_t svm(comp_t hist[rho][rho], int_t offset);
#endif 
