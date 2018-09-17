#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hats.hpp"
#include <sstream>
#include <dirent.h>
#include <iostream>
#include "time.h"
// #include <hls_opencv.h>
// using namespace cv;

void computeHATS(aer data[],int_t size){
//	 printf("",());

comp_t weights[n];
char *filename= "weights.bin";
FILE *infile = fopen(filename, "rb");
if (!infile) {
 printf("ERROR: File %s could not be opened!\n", filename);
 exit(-1);
}
fread(weights, sizeof(comp_t),n, infile);
fclose(infile);
hats(data, size,weights);
}

void readdata(aer data[],int size)
{
FILE *infile = fopen("input.bin", "rb");
  if (!infile) {
    printf("ERROR: File could not be opened!\n");
    exit(-1);
  }
  fread(data, sizeof(aer), size, infile);
  fclose(infile);
}

int main(int argc, char *argv[]) {
const int size =3418;
cout<<sizeof(aer);
aer data[size];
readdata(data,size);
computeHATS(data,size);
return 0;
}

