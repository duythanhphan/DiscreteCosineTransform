#ifndef D2DDCT_H
#define D2DDCT_H
#include"libs.h"

using namespace cv;
using namespace std;

Mat img2D_DCT(Mat mtx);
Mat imgInverse_2D_DCT(Mat mtx,int coe);

double Sum_2D_DCT(Mat mtx,int u,int v,int N,int M);
double Sum_Inverse_2D_DCT(Mat mtx,int i,int j,int N,int M);

vector<Mat> img88DCT(Mat mtx);
Mat img88Inverse_DCT(vector<Mat> vmtx,int rows,int cols,int coe);


#endif // D2DDCT_H
