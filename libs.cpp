#include"libs.h"


 IplImage* qImage2IplImage(const QImage& qImage)
{
  int width = qImage.width();
  int height = qImage.height();

  // Creates a iplImage with 3 channels
  IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
  char * imgBuffer = img->imageData;

  //Remove alpha channel
  int jump = (qImage.hasAlphaChannel()) ? 4 : 3;

  for (int y=0;y<img->height;y++){
      QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
      for (int i=0; i<a.size(); i+=jump){
          //Swap from RGB to BGR
          imgBuffer[2] = a[i];
          imgBuffer[1] = a[i+1];
          imgBuffer[0] = a[i+2];
          imgBuffer+=3;
        }
    }

  return img;
}


 QImage IplImage2QImage(const _IplImage *iplImage)
{
  int height = iplImage->height;
  int width = iplImage->width;

  if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
      return img.rgbSwapped();
    }
  else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
      QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

      QVector<QRgb> colorTable;
      for (int i = 0; i < 256; i++){
          colorTable.push_back(qRgb(i, i, i));
        }
      img.setColorTable(colorTable);
      return img;
    }
  else{
      qWarning() << "Image cannot be converted.";
      return QImage();
    }
}

 Mat img1D_DCT(Mat mtx)
 {
   Mat res,middle;
   //First-Row-Then-Column
   res=mtx.clone();
   cout<<mtx.row(0).col(0)<<endl;
   cout<<mtx.at<uchar>(0,0)<<endl;
   res.at<uchar>(0,0)=233;
   cout<<res.row(0).col(0)<<endl;


//   cout<<mtx.rows<<' '<<mtx.cols<<endl;

cout<<mtx.row(0).col(0)<<endl;
cout<<mtx.at<uchar>(0,0)<<endl;
//   cout<<2*mtx.row(0).col(0)<<endl;
//   cout<<1.5*mtx.row(0).col(0)<<endl;
   //cout<<mtx;
//   ofstream outfile;
//   outfile.open("debug.log",ios::out);
//   for(int i=0;i<mtx.rows;i++)
//     {
//       outfile<<i<<'\n';
//     for(int j=0;j<mtx.cols;j++)
//       {

//         outfile<<mtx.row(i).col(j)<<'\t';
//       }
//     outfile<<endl;
//     }
   //outfile<<mtx;

   return res;
 }
