#ifndef LIBS_H
#define LIBS_H
#include"fundamental.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
 QImage IplImage2QImage(const _IplImage *iplImage);
 IplImage* qImage2IplImage(const QImage& qImage);
 Mat img1D_DCT(Mat mtx);

#endif // LIBS_H
