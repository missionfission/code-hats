#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hats_1.hpp"
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <string>
#include "time.h"
// #include <hls_opencv.h>
// using namespace cv;
sum_t computetest(aer data_test[],int size){

sum_t result=0;
result+=hats(data_test,size);
return result;
}
sum_t computeHATS(aer data_q[][6000],int_t q_size[],int size){
//comp_t weights[n];
//double w_temp[n];
//char *filename= "weights.bin";
//FILE *infile = fopen(filename, "rb");
//if (!infile) {
// printf("ERROR: File %s could not be opened!\n", filename);
// exit(-1);
//}
//fread(w_temp, sizeof(double),n, infile);
//fclose(infile);
//for(int i=0;i<n;i++)
//{
//weights[i]=comp_t(w_temp[i]);
//}

sum_t result=0;
//for(int i=0;i<P;i++)
//	{
//	result+=hats(data_q[i], q_size[i]);
//	}


return result;
}

void readdata(aer data_test[],aer data_q[][6000],int_t q_size[],int size, string filename)
{
int data[size][4];
FILE *infile = fopen(filename.c_str(), "rb");
  if (!infile) {
    printf("ERROR: File could not be opened!\n");
    exit(-1);
  }
  fread(data, 4*sizeof(int)*size, 1, infile);
  fclose(infile);
for(int j=0;j<size;j++)
{
//int cell_id= ((data[j][0])/10)*10+(data[j][1])/10;
//if((cell_id/15)%2==0)
//{int k = data[j][0]-(cell_id/15)*15;
//data[j][1]=(data[j][1]+(k/10)*100);}
//else
//{int k = data[j][0]-(((cell_id/15)*15)/10)*10;
//data[j][1]=(data[j][1]+(k/10)*100-50);}
//data[j][0]=data[j][0]%10;
//data_q[cell_id/p_factor][q_size[cell_id/p_factor]].x=data[j][0];
//data_q[cell_id/p_factor][q_size[cell_id/p_factor]].y=data[j][1];
////data_q[cell_id/p_factor][q_size[cell_id/p_factor]].t=data[j][3];
//data_q[cell_id/p_factor][q_size[cell_id/p_factor]].p=data[j][2];
data_test[j].x=data[j][0];
data_test[j].y=data[j][1];
data_test[j].p=data[j][2];
//data_test[j].t=data[j][3];
//q_size[cell_id/p_factor]++;
}
}
long int printSize(const std::string& address) {
  std::fstream motd(address.c_str(), std::ios::binary|std::ios::in|std::ios::ate);
  if(motd) {
    std::fstream::pos_type size = motd.tellg();
//    std::cout << address << " " << size << "\n";
    return size;
  } else {
    perror(address.c_str());
    return -1;
  }
}
int main(int argc, char *argv[]) {
int_t q_size[P];
for(int i=0;i<P;i++)
	q_size[i]=0;
aer data_q[P][6000];
aer data_test[8000];
sum_t result;
int i=0;
float results[100];
//std::string filename="files/input0.bin";
while(i<100)
{
if(i!=21)
{
string s;
std::stringstream out;
out << i;
s = out.str();
std::string filename=(std::string)"files/input"+s+".bin";
int size=printSize(filename)/4/sizeof(int);
cout<<filename<<endl;
readdata(data_test,data_q,q_size,size,filename);
results[i]=computetest(data_test,size);
cout<<results[i]<<endl;
//computeHATS(data_q,q_size,size);
}
i++;
}
return 0;
}

