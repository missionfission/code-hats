#include"hats.hpp"

// make 10 accelerators in parallel
// each with 49*12 cell weights 
void svm(float sum,float hist[rho][rho]){
	//SVM weights vector

    float weights[n];
#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
    svm_loop:for(int i=0;i<rho;i++){
        for(int j=0;j<rho;j++)
    // #pragma HLS PIPELINE II=1
		    sum+=hist[i][j]*weights[i*rho+j];
	}
char *filename= "weights.bin";
FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("ERROR: File %s could not be opened!\n", filename);
    exit(-1);
  }
  fread(weights, sizeof(float),n, infile);
  fclose(infile);
}
void computeHistogram0(float hist[rho][rho],aer *event)
{
int cnt=0;
float tmsurf[rho][rho];
aer *memory_0[30];
int size0;
aer *memory_1[30];
int size1;
memset(tmsurf, 0, sizeof(tmsurf[0][0]) *49);
for(int i=0;i<rho;i++)
 for(int j=0;j<rho;j++)
        tmsurf[i][j]=0;
if(event->p)
   { for(int i=0;i<size1;i++)
        if(abs(memory_1[i]->x-event->x)<=rho/2 && abs(memory_1[i]->y-event->y)<=rho/2)
        tmsurf[memory_1[i]->x-event->x+rho/2][memory_1[i]->y-event->y+rho/2]+=1-(event->t-memory_1[i]->t)/tau;
    memory_1[size1]=event;
   }
else
    {for(int i=0;i<size1;i++)
        if(abs(memory_0[i]->x-event->x)<=rho/2 && abs(memory_0[i]->y-event->y)<=rho/2)
            tmsurf[memory_0[i]->x-event->x+rho/2][memory_0[i]->y-event->y+rho/2]+=1-(event->t-memory_0[i]->t)/tau;
    memory_0[size0]=event;
    }

for(int i=0;i<rho;i++)
    for(int j=0;j<rho;j++)
        hist[i][j]+=tmsurf[i][j];

if(cnt)
    {for(int i=0;i<rho;i++)
        for(int j=0;j<rho;j++)
            hist[i][j]/=cnt;
    }

}

void hats(aer *events)
{
float hist[rho][rho];
float sum=0;
memset(hist, 0, sizeof(hist[0][0]) *rho*rho);
// #pragma HLS INTERFACE s_axilite depth=16 port=specs bundle=SPECS
// #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
// #pragma HLS INTERFACE m_axi port=hist0 offset=slave bundle=INPUT_IMAGE
computeHistogram0(hist,events);
svm(sum,hist);
}

