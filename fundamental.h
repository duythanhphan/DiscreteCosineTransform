#ifndef FUNDAMENTAL_H
#define FUNDAMENTAL_H

#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<iomanip>

#include<QtOpenGL/QtOpenGL>
#include<QtDebug>
#include<QString>
#include<QFileDialog>
#include<GL/glu.h>
#include<QShortcut>
#include<QImage>
#include<QIcon>
#include<QStyle>
#include<QCommonStyle>

#include<qwt/qwt_plot.h>
#include<qwt/qwt_plot_curve.h>

#ifdef Q_WS_X11
#include<opencv2/opencv.hpp>
#endif

#ifdef Q_WS_WIN
#include<cv.h>
#endif


#include"libs.h"
#include"ui_mainwindow.h"

#include"report.h"


using namespace std;
using namespace cv;
namespace Ui{
  class ImageDisplayer;
}



class ImageDisplayer:public QMainWindow
{
  Q_OBJECT

public:
  explicit ImageDisplayer(QWidget *parent =0);
  ~ImageDisplayer();
  void Display();
public:
  Mat mtx,mtx_color;
  Mat M1DDCT,Mi1DDCT;
  Mat M2DDCT_whole,Mi2DDCT_whole;
  vector<Mat> M88DCT;
  vector<Mat> M88DCT_Q;
  vector<Mat> M88orig;
  vector<Mat> M88blocksiDCT_Q;
  Mat M88iDCT;
  Mat M88iDCT_Q;
  IplImage *img;
  Report rpt1D,rpt2D,rpt2Dblocks;
  Mat Qjpeg,Qcannon,Qnikon;
  vector<double> BlocksPSNR;
  double avePSNR;
public slots:
  void loadImage();
  void on_actionOpen_triggered();
  void on_actionExit_triggered();
  void on_action_About_triggered();
  void on_actionZoom_In_triggered();
  void on_actionZoom_Out_triggered();
  void on_action_Fit_to_Window_triggered();
  void on_action_Actual_Size_triggered();
  void on_action_RowThenColumn_triggered();
  void on_actionI1DDCT_triggered();
  void on_actionWholeImage_triggered();
  void on_actionInverseWholeImage_triggered();
  void on_action8_8_blocks_triggered();
  void on_actionIn_verse_8_8_blocks_triggered();
  void on_action1D_Coefficient_Report_triggered();
  void on_action2D_Coefficient_Re_port_triggered();
  void on_action2D_blocks_Coefficient_Report_triggered();
  void on_action_JpegQ_triggered();
  void on_action_a_Q_triggered();
  void on_action_CannonQ_triggered();
  void on_action_NikonQ_triggered();
private:
  Ui::ImageDisplayer *ui;
  QLabel *imageLabel;
  QScrollArea *scrollArea;
  QCommonStyle  qcs;
  QImage Image1D,Image2D,ImageBlocks;
  QString Evaluation1D,Evaluation2D,Evaluation2Dblocks;
private:
  void initializeShortcuts();
  void initializeWidgets();
  void initializeIcons();
  void initializeQ();
  void fitToWindow();
  void normalSize();
  void updateActions();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);
  void zoomIn();
  void zoomOut();
  void clean();
  QString get1Dtime();
  QString get2Dtime();
  QString get2DblocksTime();
  void CalcBlocksPSNR();
  void Inverse_1D_DCT(int coefficient);
  void Inverse_2D_DCT(int coefficient);
  void Inverse_2D_blocks_DCT(int coefficient);
  double scaleFactor;
protected:
  //  void initializeGL();
  //  void resizeGL(int w, int h);
  //  void paintGL();
};

#endif // FUNDAMENTAL_H
