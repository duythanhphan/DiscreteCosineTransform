#ifndef D1DDCT_H
#define D1DDCT_H

#include"libs.h"
using namespace cv;
using namespace std;

Mat img1D_DCT(Mat mtx);
Mat imgInverse_1D_DCT(Mat mtx);
double DCT_sum_row(Mat mtx,int i,int u,int N);
double DCT_sum_col(Mat mtx,int i,int u,int N);
double iDCT_sum_row(Mat mtx,int i,int x,int N);
double iDCT_sum_col(Mat mtx,int i,int x,int N);

#endif // D1DDCT_H
