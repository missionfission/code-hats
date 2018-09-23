#include "hog.hpp"

extern data_t img[s_row][s_col], g_row[s_row][s_col], g_col[s_row][s_col];
extern data_t ori_hist[n_cells_row][n_cells_col][orient],mag[s_row][s_col],orientation[s_row][s_col];
extern data_t norm_block[n_blocks_row][n_blocks_col][b_row][b_col][orient];

void hog(data_t *SHARED_DRAM, unsigned int input_offset)
{
#pragma HLS INTERFACE m_axi depth = DRAM_DEPTH port = SHARED_DRAM offset = slave bundle = memorybus register
#pragma HLS INTERFACE s_axilite port = input_offset bundle = axilite  register
#pragma HLS INTERFACE m_axi depth = DRAM_DEPTH port =norm_block offset = master bundle = memorybus register

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//load_image(SHARED_DRAM);
//TODO
//firstsstage();
secondstage();
compute_magnitude();
thirdstage();
fourthstage();
//writetoDRAM(SHARED_DRAM);
}
void load_image(data_t *SHARED_DRAM)
{
int pixel_offset=0;

for (int x = 0; x < s_row; x++) {
	for (int y=0;y<s_col;y++)
		{img[x][y] = reg(SHARED_DRAM[pixel_offset]);
    	pixel_offset++;
		}
	}
}
void secondstage()
{
#pragma HLS RESOURCE variable = g_row core = RAM_S2P_BRAM latency=2
#pragma HLS RESOURCE variable = g_col core = RAM_S2P_BRAM latency=2
for(int i=0; i<s_col;i++)
{
	#pragma HLS LOOP_TRIPCOUNT min=16 max = 32
    g_row[0][i] = 0;
    g_row[s_row-1][i] = 0;
    for (int j=1;j<s_row-1;j++)
    g_row[j][i] = img[j+1][i] - img[j-1][i];
}
// Calculate Column GRADIENT
for(int i=0; i<s_row;i++)
{
	#pragma HLS LOOP_TRIPCOUNT min=16 max = 32
    g_col[i][0] = 0;
    g_col[i][s_col-1] = 0;
    for (int j=1;j<s_row-1;j++)
    g_col[i][j] = img[i][j+1] - img[i][j-1];
}
}

void thirdstage()
{
#pragma HLS RESOURCE variable = ori_hist core = RAM_S2P_BRAM latency=2
int i,j,k,r,c,n,r_0,c_0,cc,cr,c_i,r_i,start,end;
n=180/orient;
r_0 = c_row / 2 ;
c_0 = c_col / 2;
cc = c_row * n_cells_row;
cr = c_col * n_cells_col;
for(i=0;i<orient;i++)
    {
    start=n*i;end=start+n;
    for (r=c_row / 2,r_i=0;r < cc;r+=c_row,r_i++)
	    for (c=c_col / 2,c_i=0;c < cr;c+=c_col,c_i++)
			ori_hist[r_i][c_i][i] = cell_hog(r,c,start,end);
    }
}
void compute_magnitude()
{
#pragma HLS RESOURCE variable = mag core = RAM_S2P_BRAM latency=2
#pragma HLS RESOURCE variable = orientation core = RAM_S2P_BRAM latency=2
for(int i=0;i<s_row;i++)
    for(int j=0;j<s_col;j++)
        {
    	#pragma HLS LOOP_TRIPCOUNT min = 256 max = 1024
    	mag[i][j] = hls::sqrt(hls::pow(g_row[i][j],2)+hls::pow(g_col[i][j],2));
        orientation[i][j] = (int)(hls::atan2(g_row[i][j], g_col[i][j])/3.14*180) % 180;
        }
}

data_t cell_hog(int r,int c,int start,int end)
{
int cri,cci;
#pragma HLS inline
data_t total=0;
for (int i=-c_row/2; i<c_row/2; i++)
    {
	#pragma HLS unroll
    cri = r + i;
    if (cri < 0 or cri >= s_row)
        continue;

    for (int j = -c_col/2; j<c_col/2; j++)
        {
    	#pragma HLS unroll
        cci = c + j;
        if (cci < 0 or cci >= s_col or orientation[cri][cci]>= end or 
        orientation[cri][cci]< start)
        continue;
        total += mag[cri][cci];
        }
    } 
	return (total / (c_row * c_col));
}            
void fourthstage()
{
#pragma HLS RESOURCE variable = norm_block core = RAM_S2P_BRAM latency=2
int i,j,k;
data_t sum, block[b_row][b_col][orient];
for(int r=0;r<n_blocks_row;r++)
    for(int c=0;c<n_blocks_col;c++)
        {
//		#pragma HLS PIPELINE
		#pragma HLS LOOP_TRIPCOUNT min = 256 max = 1024
          sum=0;
          for ( i =0;i<b_row;i++)
            for( j=0;j<b_col;j++)
                for( k=0;k<orient;k++)
                   { block[i][j][k]=ori_hist[i+r][j+c][k]; 
                   	   sum +=hls::abs(ori_hist[i+r][j+c][k]);
                   }   
         sum+=0.00001;
        for (i =0;i<b_row;i++)
            for( j=0;j<b_col;j++)
                for(k=0;k<orient;k++)
                {  norm_block[r][c][i][j][k]=block[i][j][k]/sum;
                }          
        }      
}
void writetoDRAM(data_t *SHARED_DRAM)
{
int result_offset = 0;
int result_size = sizeof(data_t)*n_blocks_row*n_blocks_col*b_row*b_col*orient;
//memcpy(results, SHARED_DRAM + result_offset, result_size);
}


