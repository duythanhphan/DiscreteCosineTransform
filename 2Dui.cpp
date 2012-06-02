#include"fundamental.h"
#include"libs.h"
#include"report.h"


void ImageDisplayer::on_actionWholeImage_triggered()
{
  QElapsedTimer timer;
  timer.start();
  M2DDCT_whole=img2D_DCT(mtx);
  int et=timer.elapsed();
  QMessageBox finish(this);
  QString st("2DDCT finished!\nTime Elapsed:");
  QString time=QString::number(et,10);
  st.append(time);
  st.append(" ms");
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::on_actionInverseWholeImage_triggered()
{
  QElapsedTimer timer;
  timer.start();
  Mi2DDCT_whole=imgInverse_2D_DCT(M2DDCT_whole,0);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,Mi2DDCT_whole);
  double psnr=PSNR(mtx,Mi2DDCT_whole);
  IplImage* imgQ=new IplImage(Mi2DDCT_whole);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QString time=QString::number(et,10);
  QString st("Inverse 2DDCT on whole image finished!\n");
  st.append("Time Elapsed:");
  st.append(time);
  st.append(" ms\n");
  st.append("myPSNR:");
  st.append(QString::number(mypsnr));
  st.append("\ncvPSNR:");
  st.append(QString::number(psnr));
  QMessageBox finish(this);
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::Inverse_2D_DCT(int coefficient)
{
  QElapsedTimer timer;
  timer.start();
  this->Mi2DDCT_whole=imgInverse_2D_DCT(M2DDCT_whole,coefficient);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,Mi2DDCT_whole);
  double psnr=PSNR(mtx,Mi2DDCT_whole);
  IplImage* imgQ=new IplImage(Mi2DDCT_whole);
  this->Image2D=QImage(IplImage2QImage(imgQ));

  QString time=QString::number(et,10);
  QString st("Coefficient used:");
  if(coefficient==0)
    st.append("All");
  else
    {
      st.append("1/");
      st.append(QString::number(coefficient));
    }
  st.append("\n\nInverse Evaluation:\n");
  st.append("Inverse Time Elapsed:");
  st.append(time);
  st.append(" ms\n");
  st.append("myPSNR:");
  st.append(QString::number(mypsnr));
  st.append("\ncvPSNR:");
  st.append(QString::number(psnr));
  st.append("\n");
  Evaluation2D=st;
}
void ImageDisplayer::on_action2D_Coefficient_Re_port_triggered()
{
  QString transTime=get2Dtime();
  QString eva[4];
  QImage inv_img[4];

  Inverse_2D_DCT(0);
  eva[0]=Evaluation2D;
  inv_img[0]=QImage(Image2D);

//  cout<<qPrintable(Evaluation1D);
  Inverse_2D_DCT(4);
  eva[1]=Evaluation2D;
  inv_img[1]=QImage(Image2D);
//cout<<qPrintable(Evaluation1D);
  Inverse_2D_DCT(16);
  eva[2]=Evaluation2D;
  inv_img[2]=QImage(Image2D);

  Inverse_2D_DCT(64);
  eva[3]=Evaluation2D;
  inv_img[3]=QImage(Image2D);
  rpt2D.setWindowTitle("2D Report");
  rpt2D.setReport(transTime,eva,inv_img);
  rpt2D.show();
}

QString ImageDisplayer::get2Dtime()
{
  QElapsedTimer timer;
  timer.start();
  M2DDCT_whole=img2D_DCT(mtx);
  int et=timer.elapsed();

  QString st("2D Transform Time Elapsed:");
  QString time=QString::number(et);
  st.append(time);
  st.append(" ms");
  return st;
}
