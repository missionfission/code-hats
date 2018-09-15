#include "consts.h"
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ap_int.h"
// total rho*rho = 49
// make 10 accelerators in parallel
// each with 49*12 cell weights 
void svm(ap_int<6>  cell,int *classify){
	//SVM weights vector
	ap_int<6>  weights[n] = {};
#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
	// SVM's model initial bias
	int sum = -14;
    svm_loop:for(int i=0;i<n/16;i++){
    #pragma HLS PIPELINE II=1
		sum+=normalized0[i]*weights[i+offset];
		sum+=normalized1[i]*weights[i+offset2];
	}
	classify[0] = sum;
}

void hats(aer *events)
{
// #pragma HLS INTERFACE s_axilite depth=16 port=specs bundle=SPECS
// #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
// #pragma HLS INTERFACE m_axi port=hist0 offset=slave bundle=INPUT_IMAGE
// #pragma HLS RESOURCE variable=descriptor0 core=RAM_2P_BRAM
ap_int<15>  descriptor1[n/16];
// #pragma HLS ARRAY_PARTITION variable=image_buffer1 complete dim=1
computeHistogram0(descriptor0,timesurface,sum0);
svm(hist);
return features
}

void computeHistogram0(aer *event)
{
// make a timesurface
float hist[rho][rho];
int cnt=0;
float tmsurf[rho][rho];
aer *memory_0;
aer *memory_1;
for(int i=0;i<rho;i++)
    for(int j=0;j<rho;j++)
        hist[i][j]=0;
        tmsurf[i][j]=0;
if(event.p)
   { for(int i=0;i<memory_1.size();i++)
        if(abs(memory_1[i].x-event.x)<=rho/2 && abs(memory_1[i].y-event.y)<=rho/2)
        tmsurf[memory_1[i].x-event.x+rho/2][memory_1[i].y-event.y+rho/2]+=1-(event.t-memory_1[i].t)/tau;
    memory_1[memory_1.size()]=event;
   }
else
    {for(int i=0;i<memory_0.size();i++)
        if(abs(memory_0[i].x-event.x)<=rho/2 && abs(memory_0[i].y-event.y)<=rho/2)
            tmsurf[memory_0[i].x-event.x+rho/2][memory_0[i].y-event.y+rho/2]+=1-(event.t-memory_0[i].t)/tau;
    memory_0[memory_0.size()]=event;        
    }

for(int i=0;i<rho;i++)
    for(int j=0;j<rho;j++)
        hist[i][j]+=tmsurf[i][j]

if(cnt)
    {for(int i=0;i<rho;i++)
        for(int j=0;j<rho;j++)
            hist[i][j]/=cnt;
    }

}
