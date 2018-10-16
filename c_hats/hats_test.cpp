#include"hats_test.hpp"

sum_t loc_sum_test[tot_cell];
int_t cnt_testmem[tot_cell][2];
int_t cnt_test[tot_cell];
aer memory_test[tot_cell][2][5000];

sum_t svm_test(hist_t hist[rho][rho],comp_t weights[],int_t offset){
sum_t sum=0;
for(int_t i=0;i<rho;i++){
	for(int_t j=0;j<rho;j++){
		sum+=(hist[i][j]*weights[offset+i*rho+j]);
//		cout<<weights[offset+i*rho+j]<<"  "<<hist[i][j]<<"   "<< hist[i][j]*weights[offset+i*rho+j]<<"  "<<sum<<"\n";
		}
}
return sum;
}
void computeHistogram_test(addr_t cell_id,comp_t weights[],aer event)
{

hist_t hist[rho][rho]={0};
for (int i=0;i<rho;i++)
	for (int j=0;j<rho;j++)
		hist[i][j]=0;

for(int_t i=0;i<cnt_testmem[cell_id][event.p];i++)
	{
	 int_t x=memory_test[cell_id][event.p][i].y-event.y;
	 int_t y=memory_test[cell_id][event.p][i].x-event.x;
        if(abs(x)<=rho/2 && abs(y)<=rho/2)
      {
        	hist[x+rho/2][y+rho/2]++;
//    		hist[x+rho/2][y+rho/2]+=(1-(event.t-memory_test[cell_id][event.p][i].t)/tau);
//      int k=1-(event.t-memory_test[cell_id][event.p][i].t)/tau;
//      cout<<hist[x+rho/2][y+rho/2]<<endl;
      }
	}
	int_t offset= cell_id*rho*rho;
 loc_sum_test[cell_id]+=svm_test(hist,weights,offset);
}
sum_t hats_test(aer events[],comp_t weights[],int_t size)
{
sum_t sum=0;
addr_t cell_id;

for (int_t i=0;i<tot_cell;i++)
	{
	loc_sum_test[i]=0;
	cnt_test[i]=0 ;
	cnt_testmem[i][0]=0;
	cnt_testmem[i][1]=0;}
for(int_t j=0;j<size;j++)
	{
	cell_id= ((events[j].x)/10)*10+(events[j].y)/10;
	computeHistogram_test(cell_id,weights,events[j]);
	memory_test[cell_id][events[j].p][cnt_testmem[cell_id][events[j].p]]=events[j];
	cnt_testmem[cell_id][events[j].p]++;
	cnt_test[cell_id]++;
	}
//cout<<sum<<"initial"<<endl;
for(int_t k=0;k<tot_cell;k++)
{
	if(cnt_test[k]>0)
sum+=loc_sum_test[k]/cnt_test[k];
//cout<<sum<<"  "<<loc_sum_test[k]<<endl;
}

return sum;
}

