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

void computeHATS(aer *data[],int size){
// for(int i=0;i<size;i++)
// 	hats(data[i]);
}

void readdata(aer *data[],int size)
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
aer * data[size];
readdata(data,size);
computeHATS(data,size);
return 0;
}

