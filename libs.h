#ifndef LIBS_H
#define LIBS_H
#include"fundamental.h"
#include<opencv2/opencv.hpp>
 QImage IplImage2QImage(const _IplImage *iplImage);
 IplImage* qImage2IplImage(const QImage& qImage);

#endif // LIBS_H
