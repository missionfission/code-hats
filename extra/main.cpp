#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hats_1.hpp"
#include <sstream>
#include <dirent.h>
#include <iostream>
#include "time.h"
// #include <hls_opencv.h>
// using namespace cv;

void computeHATS(aer data[],int_t size){
comp_t weights2[n];
double weights[n];
char *filename= "weights.bin";
FILE *infile = fopen(filename, "rb");
if (!infile) {
 printf("ERROR: File %s could not be opened!\n", filename);
 exit(-1);
}
fread(weights, sizeof(double),n, infile);
fclose(infile);
for(int i=0;i<n;i++)
{  
weights2[i]=comp_t(weights[i]);
// cout<<weights[i]<<"i is"<<i<<"and conversion is"<<weights2[i]<<endl;
}
for(int i=0;i<size;i++){  
cout<<data[i].x<<"y is"<<data[i].y;
}
cout<<hats(data, size,weights2);
}

void readdata(aer data[],int size)
{
int data2[size][4];
FILE *infile = fopen("input.bin", "rb");
  if (!infile) {
    printf("ERROR: File could not be opened!\n");
    exit(-1);
  }
  fread(data2, 4*sizeof(int)*size, 1, infile);
  fclose(infile);
for(int i=0;i<size;i++)
{
data[i].x=data2[i][0];
data[i].y=data2[i][1];
data[i].p=data2[i][2];
data[i].t=data2[i][3];
// cout<<data[i].x<<"x is"<<data2[i][0]<<endl;
// cout<<data[i].p<<"p is"<<data2[i][2]<<endl;
}}

int main(int argc, char *argv[]) {
const int size =3418;
aer data[size];
readdata(data,size);
computeHATS(data,size);
return 0;
}

