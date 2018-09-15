#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #include "lighter_svm.hpp"
//#include <opencv2/core/mat.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
#include <hls_opencv.h>
using namespace cv;

typedef struct svm{
	float x1;
	float x2;
	float y1;
	float y2;
	svm *next;
	svm *prev;
	float scale;
	float score;
} svmpoints;

float max(float a,float b){
	if (a>=b)
		return a;
	else 
		return b;
}

float min(float a,float b){
	if (a<=b)
		return a;
	else 
		return b;
}

int int_min(int A,int B){
	if(A<B)
		return A;
	else
		return B;
}

float area(float x1,float x2,float y1,float y2){
	return fabs(x1-x2)*fabs(y1-y2);
}

void printResults(svmpoints *head){
    for(svmpoints *node = head->next; node->next!=NULL;node = node->next){
        printf("X1 = %lf,X2= %lf,Y1 = %lf,Y2 = %lf --- scale = %lf --- score = %lf\n",node->x1,node->x2,node->y1,node->y2,node->scale,node->score);
    }
}

void addNode(int x, int y, double scale,double score,svmpoints *head){
	svmpoints *newNode = (svmpoints*)malloc(sizeof(svmpoints));;
	newNode->x1 = (x*WINDOWSTRIDEX)/scale;
	newNode->x2 = (x*WINDOWSTRIDEX+64)/scale;
	newNode->y1 = (y*WINDOWSTRIDEY)/scale;
	newNode->y2  =(y*WINDOWSTRIDEY+128)/scale;
	newNode->scale = scale;
	newNode->score = score;
	newNode->next = head->next;
	newNode->prev = head;
	if(head->next != NULL)
		head->next->prev = newNode;
	head->next = newNode;
}

void draw(svmpoints *head, Mat drawImage){
    
	int ibound;
	int jbound;
    Vec3b pixel;
    pixel[0] = 0;
    pixel[1] = 255;
    pixel[2] = 0;
    char msg[80];  

	for(svmpoints *node = head->next; node->next!=NULL;node = node->next){
		ibound = node->y2-node->y1;
		jbound = node->x2-node->x1;
		for (int i=0;i<ibound;i++){
			for(int j=0;j<jbound;j++){
				if(i==0 || i== ibound - 1 || j==0 || j == jbound-1){
                    drawImage.at<Vec3b>(int_min(node->y1+i,drawImage.rows),int_min(node->x1+j,drawImage.cols)) = pixel;
				}
			}
		}
        sprintf(msg,"%lf -- %lf",node->score,node->scale);
        putText(drawImage, msg, cvPoint(node->x1,node->y2-4), FONT_HERSHEY_SIMPLEX, 0.3, cvScalar(0,0,255), 1, CV_AA);
	}
}

void readImage(Mat _img ,imageData *image,int border){
	image->width = _img.cols + 2 * border;
	image->height = _img.rows + 2 * border;
	image->size = image->width * image->height;
	
	int img_counter = 0;
	int j = image->width + border, x = 0, y = 0;	
	for(int r = 0; r < _img.rows; ++r) {
		for(int c = 0; c < _img.cols; ++c, j++) {
			image->data[j] = _img.at<unsigned char>(r,c);
		}
		j += 2 * border;	//Shift 2 border pixels
	}
}
