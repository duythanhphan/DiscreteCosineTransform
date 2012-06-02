
#include"fundamental.h"
#include"Quantilization.h"


void ImageDisplayer::on_action_JpegQ_triggered()
{

  t88Res tret=img88DCT_Q(mtx,Qjpeg);
  M88DCT_Q=tret.DCT;
  M88orig=tret.orig;

  i88Res iret=img88Inverse_DCT_Q(M88DCT_Q,mtx.rows,mtx.cols,0);
  M88iDCT_Q=iret.res;
  M88blocksiDCT_Q=iret.blocks;
  CalcBlocksPSNR();

  IplImage* imgQ=new IplImage(M88iDCT_Q);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QMessageBox finish;
  QString st("blocks PSNR output to \"BlocksPSNR.log\"\n");
  st.append("Average PSNR over all blocks:\n");
  st.append(QString::number(avePSNR));
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::CalcBlocksPSNR()
{
  for(uint i=0;i<M88DCT_Q.size();i++)
    {
      BlocksPSNR.push_back(PSNR(M88orig[i],M88blocksiDCT_Q[i]));
    }
  ofstream outfile;
  double sum=0;
  outfile.open("BlocksPSNR.log",ios::out);
  for(uint i=0;i<BlocksPSNR.size();i++)
    {
      outfile<<BlocksPSNR[i]<<endl;
      sum+=BlocksPSNR[i];
    }
  avePSNR=sum/BlocksPSNR.size();
  outfile.close();
}

void ImageDisplayer::on_action_a_Q_triggered()
{
  ofstream outfile;
  outfile.open("AveragePSNR.log",ios::out);
  outfile<<"a\tAveragePSNR"<<endl;
  double x[38],y[38];
  int i=0;
  for(double a=0.1;a<2;a+=0.05)
    {
      t88Res tret=img88DCT_Q(mtx,a*Qjpeg);
      M88DCT_Q=tret.DCT;
      M88orig=tret.orig;

      i88Res iret=img88Inverse_DCT_Q(M88DCT_Q,mtx.rows,mtx.cols,0);
      M88iDCT_Q=iret.res;
      M88blocksiDCT_Q=iret.blocks;

      CalcBlocksPSNR();

      IplImage* imgQ=new IplImage(M88iDCT_Q);
      QImage qimg=IplImage2QImage(imgQ);
      imageLabel->setPixmap(QPixmap::fromImage(qimg));
      x[i]=a;y[i]=avePSNR;
      i++;
      outfile<<a<<"\t";
      outfile<<avePSNR<<endl;
    }
  QwtPlot pl;
  pl.setTitle("PSNR-a");
  //  setCanvasBackground(QBrush(QColor("black")));
  pl.setAxisTitle(QwtPlot::xBottom,QString("a"));

  pl.setAxisTitle(QwtPlot::yLeft,QString("PSNR"));

  QwtPlotCurve curve("PSNR-a");
  curve.setSamples(x,y,38);
  curve.setPen(QPen("red"));
  curve.setStyle(QwtPlotCurve::Lines);
  curve.attach(&pl);
  pl.show();
  pl.replot();

  QMessageBox finish;
  QString st("Average PSNRs output to \"AveragePSNR.log\"\n");
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::on_action_CannonQ_triggered()
{

  t88Res tret=img88DCT_Q(mtx,Qcannon);
  M88DCT_Q=tret.DCT;
  M88orig=tret.orig;

  i88Res iret=img88Inverse_DCT_Q(M88DCT_Q,mtx.rows,mtx.cols,0);
  M88iDCT_Q=iret.res;
  M88blocksiDCT_Q=iret.blocks;
  CalcBlocksPSNR();

  IplImage* imgQ=new IplImage(M88iDCT_Q);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QMessageBox finish;
  QString st("blocks PSNR output to \"BlocksPSNR.log\"\n");
  st.append("Average PSNR over all blocks:\n");
  st.append(QString::number(avePSNR));
  finish.setText(st);
  finish.exec();
}

void ImageDisplayer::on_action_NikonQ_triggered()
{

  t88Res tret=img88DCT_Q(mtx,Qnikon);
  M88DCT_Q=tret.DCT;
  M88orig=tret.orig;

  i88Res iret=img88Inverse_DCT_Q(M88DCT_Q,mtx.rows,mtx.cols,0);
  M88iDCT_Q=iret.res;
  M88blocksiDCT_Q=iret.blocks;
  CalcBlocksPSNR();

  IplImage* imgQ=new IplImage(M88iDCT_Q);
  QImage qimg=IplImage2QImage(imgQ);
  imageLabel->setPixmap(QPixmap::fromImage(qimg));

  QMessageBox finish;
  QString st("blocks PSNR output to \"BlocksPSNR.log\"\n");
  st.append("Average PSNR over all blocks:\n");
  st.append(QString::number(avePSNR));
  finish.setText(st);
  finish.exec();
}
