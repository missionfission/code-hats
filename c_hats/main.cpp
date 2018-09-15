#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hats.hpp"
#include <sstream>
#include <dirent.h>
#include <iostream>
#include "time.h"
#include <hls_opencv.h>
using namespace cv;
const int size =1000;
aer * data[size];
void computeHATS(){
for(int i=0;i<size;i++)
	hats(data[i]);
}

void main() {
readdata();
computeHATS();
}

void readdata()
{
char *filename="data.mat";
FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("ERROR: File %s could not be opened!\n", filename);
    exit(-1);
  }
  fread(data, sizeof(aer), size, infile);
  fclose(infile);
}
