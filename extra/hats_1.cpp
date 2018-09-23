#include"hats_1.hpp"

// make 10 accelerators in parallel
// each with 49*12 cell weights 
void svm(comp_t *sum,comp_t hist[rho][rho],comp_t weights[], int_t offset){
//SVM weights vector
#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
for(int_t i=0;i<rho;i++){
	for(int_t j=0;j<rho;j++)
	#pragma HLS PIPELINE II=1
		*sum+=hist[i][j]*weights[offset+i*rho+j];
}

}
void computeHistogram(comp_t hist[rho][rho],aer event,aer memory[],int_t size)
{

comp_t tmsurf[rho][rho];
memset(tmsurf, 0, sizeof(tmsurf[0][0]) *49);
#pragma HLS RESOURCE variable=tmsurf core=RAM_2P_BRAM
 for(int_t i=0;i<size;i++)
	{
	 int_t x=memory[i].y-event.y;
	 int_t y=memory[i].x-event.x;
        if(abs(x)<=rho/2 && abs(y)<=rho/2)
      {  tmsurf[x+rho/2][y+rho/2]+=1-(event.t-memory[i].t)/tau;
		// cout<<"tmsurf is set to"<<1-(event.t-memory[i].t)/tau;}
	}
// cout<<"time surface is"<<endl;
// for(int_t i=0;i<rho;i++)
//     for(int_t j=0;j<rho;j++)
// 	{cout<<tmsurf[i][j]<<endl;
//         }
//  cout <<"histogram here is "<<endl;
for(int_t i=0;i<rho;i++)
    for(int_t j=0;j<rho;j++)
	// {cout<<hist[i][j];
	    #pragma HLS unroll factor = N_PE
		#pragma HLS PIPELINE II = 1
        hist[i][j]+=tmsurf[i][j];}
// cout<<endl;
}

comp_t hats(aer events[],int_t size,comp_t weights[])
{
// cout<<"\n"<<"here";
#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
#pragma HLS INTERFACE m_axi port=weights offset=slaves
comp_t hist[tot_cell][rho][rho];
comp_t sum=0;
int_t offset=0;
int_t cnt[tot_cell];
int_t cell_id;
aer memory[tot_cell][2][30];
int_t cntmem[tot_cell][2];
// cout<<"\n"<<"here";
#pragma HLS RESOURCE variable=memory core=RAM_2P_BRAM
#pragma HLS RESOURCE variable=size core=RAM_2P_BRAM
memset(hist, 0, sizeof(hist[0][0][0])*tot_cell*rho*rho);
memset(cnt, 0, sizeof(cnt[0])*tot_cell);
memset(cntmem, 0, sizeof(cntmem[0][0])*tot_cell*2);
for(int_t j=0;j<size;j++)
	{cell_id= ((events[j].x)/10)*10+(events[j].y)/10;
	// cout<<"cell_id is" <<cell_id<<endl;
	computeHistogram(hist[cell_id],events[j],memory[cell_id][events[j].p],cntmem[cell_id][events[j].p]);
	//  cout <<"histogram in loop is "<<endl;
	cout<<"j is"<<j<<endl;
	memory[cell_id][events[j].p][cntmem[cell_id][events[j].p]]=events[j];
	cntmem[cell_id][events[j].p]++;
	cnt[cell_id]++;
	}

// cout<<"here";
for(int_t k=0;k<tot_cell;k++)
{if(cnt[k]>0)
    {for(int_t i=0;i<rho;i++)
        for(int_t j=0;j<rho;j++)
        {	#pragma HLS unroll factor = N_PE
        	hist[k][i][j]=hist[k][i][j]/cnt[k];
        }

    }
}
for(int_t i=0;i<tot_cell;i++)
	{offset=i*rho*rho;
	svm(&sum,hist[i],weights,offset);
	}
return sum;
}

