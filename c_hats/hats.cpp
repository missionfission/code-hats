#include"hats.hpp"

// make 10 accelerators in parallel
// each with 49*12 cell weights 
void svm(float sum,float hist[rho][rho],float weights[], int offset){
//SVM weights vector
//#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
svm_loop:for(int i=0;i<rho;i++){
	for(int j=0;j<rho;j++)
// #pragma HLS PIPELINE II=1
		sum+=hist[i][j]*weights[offset+i*rho+j];
}

}
void computeHistogram(float hist[rho][rho],aer *event,aer memory[],int size)
{

float tmsurf[rho][rho];
memset(tmsurf, 0, sizeof(tmsurf[0][0]) *49);
if(event->p)
   { for(int i=0;i<size;i++)
        if(abs(memory[i].x-event->x)<=rho/2 && abs(memory[i].y-event->y)<=rho/2)
        tmsurf[memory[i].x-event->x+rho/2][memory[i].y-event->y+rho/2]+=1-(event->t-memory[i].t)/tau;
    memory[size]=*event;
    size++;
   }
for(int i=0;i<rho;i++)
    for(int j=0;j<rho;j++)
        hist[i][j]+=tmsurf[i][j];
}

float hats(aer **events)
{

// #pragma HLS INTERFACE s_axilite depth=16 port=specs bundle=SPECS
// #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
// #pragma HLS INTERFACE m_axi port=hist0 offset=slave bundle=INPUT_IMAGE
float hist[tot_cell][rho][rho];
float sum=0;
int offset=0;
memset(hist, 0, sizeof(hist[0][0][0])*tot_cell*rho*rho);
float weights[n];
char *filename= "weights.bin";
FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("ERROR: File %s could not be opened!\n", filename);
    exit(-1);
  }
  fread(weights, sizeof(float),n, infile);
  fclose(infile);

int cnt[tot_cell];
int cell_id;
aer memory[tot_cell][2][30];
int size[tot_cell][2];
memset(cnt, 0, sizeof(cnt[0])*tot_cell);
memset(size, 0, sizeof(size[0][0])*tot_cell*2);
for(int j=0;j<n;j++)
	{cell_id=int(events[j]->x*10+events[j]->y);
	computeHistogram(hist[cell_id],events[j],memory[cell_id][events[j]->p],size[cell_id][events[j]->p]);
	cnt[cell_id]++;
	}

for(int k=0;k<tot_cell;k++)
{if(cnt[k])
    {for(int i=0;i<rho;i++)
        for(int j=0;j<rho;j++)
            hist[k][i][j]/=cnt[k];

    }
}
for(int i=0;i<tot_cell*rho*rho;i++)
	{offset=i*rho*rho;
	svm(sum,hist[i],weights,offset);
	}
	return sum;
}

