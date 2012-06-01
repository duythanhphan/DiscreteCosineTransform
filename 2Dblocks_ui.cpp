

#include"fundamental.h"
#include"libs.h"
#include"report.h"


void ImageDisplayer::on_action8_8_blocks_triggered()
{
  QElapsedTimer timer;
  timer.start();
  M88DCT=img88DCT(mtx);
  int et=timer.elapsed();
  QMessageBox finish(this);
  QString st("2DDCT by 8*8 blocks  finished!\nTime used:");
  st.append(QString::number(et));
  st.append(" ms");
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::on_actionIn_verse_8_8_blocks_triggered()
{
  QElapsedTimer timer;
  timer.start();
  M88iDCT=img88Inverse_DCT(M88DCT,mtx.rows,mtx.cols,0);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,M88iDCT);
  double psnr=PSNR(mtx,M88iDCT);
  IplImage* imgQ=new IplImage(M88iDCT);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QString time=QString::number(et,10);
  QString st("Inverse 2DDCT on 8*8 blocks finished!\n");
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

void ImageDisplayer::Inverse_2D_blocks_DCT(int coefficient)
{
  QElapsedTimer timer;
  timer.start();
  M88iDCT=img88Inverse_DCT(M88DCT,mtx.rows,mtx.cols,coefficient);
  int et=timer.elapsed();
  double mypsnr=myPSNR(mtx,M88iDCT);
  double psnr=PSNR(mtx,M88iDCT);
  IplImage* imgQ=new IplImage(M88iDCT);
  ImageBlocks=QImage(IplImage2QImage(imgQ));

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
  Evaluation2Dblocks=st;
}
void ImageDisplayer::on_action2D_blocks_Coefficient_Report_triggered()
{
  QString transTime=get2DblocksTime();
  QString eva[4];
  QImage inv_img[4];

  Inverse_2D_blocks_DCT(0);
  eva[0]=Evaluation2Dblocks;
  inv_img[0]=QImage(ImageBlocks);

//  cout<<qPrintable(Evaluation1D);
  Inverse_2D_blocks_DCT(4);
  eva[1]=Evaluation2Dblocks;
  inv_img[1]=QImage(ImageBlocks);
//cout<<qPrintable(Evaluation1D);
  Inverse_2D_blocks_DCT(16);
  eva[2]=Evaluation2Dblocks;
  inv_img[2]=QImage(ImageBlocks);

  Inverse_2D_blocks_DCT(64);
  eva[3]=Evaluation2Dblocks;
  inv_img[3]=QImage(ImageBlocks);

  rpt2Dblocks.setReport(transTime,eva,inv_img);
  rpt2Dblocks.show();
}

QString ImageDisplayer::get2DblocksTime()
{
  QElapsedTimer timer;
  timer.start();
  M88DCT=img88DCT(mtx);
  int et=timer.elapsed();

  QString st("2D blocks Transform Time Elapsed:\n");
  QString time=QString::number(et);
  st.append(time);
  st.append(" ms\n");
  return st;
}
