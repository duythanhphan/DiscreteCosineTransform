#ifndef LIBS_H
#define LIBS_H

#include<opencv2/opencv.hpp>

#include"fundamental.h"
#include"report.h"
#include"1DDCT.h"
#include"2DDCT.h"


#define PI 3.14159265

using namespace cv;
using namespace std;
 QImage IplImage2QImage(const _IplImage *iplImage);
 IplImage* qImage2IplImage(const QImage& qImage);

 double CalcMSE(Mat origin,Mat approx);
 double CalcPSNR(double mse);
 double myPSNR(Mat origin,Mat approx);
#endif // LIBS_H
