
#include"fundamental.h"
#include"libs.h"
#include"report.h"


void ImageDisplayer::on_action_RowThenColumn_triggered()
{
  QElapsedTimer timer;
  timer.start();
  M1DDCT=img1D_DCT(mtx);
  //  IplImage* imgQ=new IplImage(M1DDCT);
  //  QImage qimg=IplImage2QImage(imgQ);
  //  imageLabel->setPixmap(QPixmap::fromImage(qimg));
  int et=timer.elapsed();
  // cout<<et;
  QMessageBox finish(this);
  QString st("1DDCT finished!\nTime Elapsed:");
  QString time=QString::number(et,10);
  st.append(time);
  st.append(" ms");
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::on_actionI1DDCT_triggered()
{
  QElapsedTimer timer;
  timer.start();
  Mi1DDCT=imgInverse_1D_DCT(M1DDCT,0);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,Mi1DDCT);
  double psnr=PSNR(mtx,Mi1DDCT);
  IplImage* imgQ=new IplImage(Mi1DDCT);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QString time=QString::number(et,10);
  QString st("Inverse 1DDCT finished!\n");
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

void ImageDisplayer::Inverse_1D_DCT(int coefficient)
{
  QElapsedTimer timer;
  timer.start();
  this->Mi1DDCT=imgInverse_1D_DCT(M1DDCT,coefficient);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,Mi1DDCT);
  double psnr=PSNR(mtx,Mi1DDCT);
  IplImage* imgQ=new IplImage(Mi1DDCT);
  this->Image1D=QImage(IplImage2QImage(imgQ));

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
  Evaluation1D=st;
}


void ImageDisplayer::on_action1D_Coefficient_Report_triggered()
{
  clean();

  QString transTime=get1Dtime();
  QString eva[4];
  QImage inv_img[4];

  Inverse_1D_DCT(0);
  eva[0]=Evaluation1D;
  inv_img[0]=QImage(Image1D);

//  cout<<qPrintable(Evaluation1D);
  Inverse_1D_DCT(4);
  eva[1]=Evaluation1D;
  inv_img[1]=QImage(Image1D);
//cout<<qPrintable(Evaluation1D);
  Inverse_1D_DCT(16);
  eva[2]=Evaluation1D;
  inv_img[2]=QImage(Image1D);

  Inverse_1D_DCT(64);
  eva[3]=Evaluation1D;
  inv_img[3]=QImage(Image1D);
  rpt1D.setWindowTitle("1D Report");
  rpt1D.setReport(transTime,eva,inv_img);
  rpt1D.show();
}

QString ImageDisplayer::get1Dtime()
{
  QElapsedTimer timer;
  timer.start();
 this-> M1DDCT=img1D_DCT(mtx);
  int et=timer.elapsed();
  QString res("Transform Time Elapsed:");
  QString time=QString::number(et);
  res.append(time);
  res.append(" ms\n");
  return res;
}
