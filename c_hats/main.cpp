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

comp_t computeHATS(aer data[],int_t size){
comp_t weights[n];
double w_temp[n];
char *filename= "weights.bin";
FILE *infile = fopen(filename, "rb");
if (!infile) {
 printf("ERROR: File %s could not be opened!\n", filename);
 exit(-1);
}
fread(w_temp, sizeof(double),n, infile);
fclose(infile);
for(int i=0;i<n;i++)
{  
weights[i]=comp_t(w_temp[i]);
}
int_t q_size[P]={0};
aer data_q[P][1500];
for(int_t j=0;j<size;j++)
{
int cell_id= ((data[j].x)/10)*10+(data[j].y)/10;
if((cell_id/15)%2==0)
{int k = data[j].x-(cell_id/15)*15;
data[j].y=(data[j].y+(k/10)*100);}
else
{int k = data[j].x-(((cell_id/15)*15)/10)*10;
data[j].y=(data[j].y+(k/10)*100-50);}
data[j].x=data[j].x%10;
data_q[cell_id/p_factor][q_size[cell_id/p_factor]]=data[j];
q_size[cell_id/p_factor]++;
}

comp_t result=0;
for(int_t i=0;i<P;i++)
{ 	comp_t *ptr=weights+i*rho*rho*tot_cell;
	result+=hats(data_q[i], q_size[i]);

}
return result;
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
}}

int main(int argc, char *argv[]) {
const int size =3418;
aer data[size];
readdata(data,size);
float result=computeHATS(data,size);
cout<<result;
if(abs(result-2.212)<0.22)
{cout<<"correct";
return 0;}
else
{cout<<"incorrect";
return -1;
}}

