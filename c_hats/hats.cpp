#include"hats.hpp"

// make 10 accelerators in parallel
// each with 49*12 cell weights 
void svm(comp_t sum,comp_t hist[rho][rho],comp_t weights[], int_t offset){
//SVM weights vector
#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
for(int_t i=0;i<rho;i++){
	for(int_t j=0;j<rho;j++)
#pragma HLS PIPELINE II=1
		sum+=hist[i][j]*weights[offset+i*rho+j];
}

}
void computeHistogram(comp_t hist[rho][rho],aer event,aer memory[],int_t size)
{

comp_t tmsurf[rho][rho];
#pragma HLS RESOURCE variable=tmsurf core=RAM_2P_BRAM
//memset(tmsurf, 0, sizeof(tmsurf[0][0]) *49);
if(event.p)
   { for(int_t i=0;i<size;i++)
        if(abs(memory[i].x-event.x)<=rho/2 && abs(memory[i].y-event.y)<=rho/2)
        tmsurf[memory[i].x-event.x+rho/2][memory[i].y-event.y+rho/2]+=1-(event.t-memory[i].t)/tau;
    memory[size]=event;

   }
for(int_t i=0;i<rho;i++)
    for(int_t j=0;j<rho;j++)
        hist[i][j]+=tmsurf[i][j];
}

comp_t hats(aer events[ents],int_t n,comp_t *weights)
{


#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
#pragma HLS INTERFACE m_axi port=weights offset=slave
//#pragma HLS INTERFACE m_axi port=events bundle=Events
comp_t hist[tot_cell][rho][rho];
#pragma HLS RESOURCE variable=hist core=RAM_2P_BRAM
comp_t sum=0;
int_t offset=0;
int_t cnt[tot_cell];
int_t cell_id;
aer memory[tot_cell][2][30];
int_t size[tot_cell][2];
#pragma HLS RESOURCE variable=memory core=RAM_2P_BRAM
#pragma HLS RESOURCE variable=size core=RAM_2P_BRAM
//memset(hist, 0, sizeof(hist[0][0][0])*tot_cell*rho*rho);
//memset(cnt, 0, sizeof(cnt[0])*tot_cell);
//memset(size, 0, sizeof(size[0][0])*tot_cell*2);
for(int_t j=0;j<ents;j++)
	{cell_id= events[j].x*10+events[j].y;
	computeHistogram(hist[cell_id],events[j],memory[cell_id][events[j].p],size[cell_id][events[j].p]);
	size[cell_id][events[j].p]++;
	cnt[cell_id]++;
	}

for(int_t k=0;k<tot_cell;k++)
{if(cnt[k]>0)
    {for(int_t i=0;i<rho;i++)
        for(int_t j=0;j<rho;j++)
            hist[k][i][j]/=cnt[k];

    }
}
for(int_t i=0;i<tot_cell*rho*rho;i++)
	{offset=i*rho*rho;
	svm(sum,hist[i],weights,offset);
	}
return sum;
}

