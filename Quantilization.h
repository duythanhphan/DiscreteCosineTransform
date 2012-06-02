#ifndef QUANTILIZATION_H
#define QUANTILIZATION_H

#include"libs.h"
using namespace cv;
using namespace std;

struct t88Res{
  vector<Mat> DCT;
  vector<Mat> orig;
};

struct i88Res{
  vector<Mat> blocks;
  Mat res;
};

t88Res img88DCT_Q(Mat mtx,Mat Q);
Mat img2D_DCT_Q(Mat mtx,Mat Q);
i88Res img88Inverse_DCT_Q(vector<Mat> vmtx, int rows, int cols,int coefficient);

#endif // QUANTILIZATION_H
