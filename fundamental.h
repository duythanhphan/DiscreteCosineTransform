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

#ifdef Q_WS_X11
#include<opencv2/opencv.hpp>
#endif

#ifdef Q_WS_WIN
#include<cv.h>
#endif


#include"libs.h"
#include"ui_mainwindow.h"


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

  IplImage *img;
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
private:
  Ui::ImageDisplayer *ui;
  QLabel *imageLabel;
  QScrollArea *scrollArea;
  QCommonStyle  qcs;
private:
  void initializeShortcuts();
  void initializeWidgets();
  void initializeIcons();
  void fitToWindow();
  void normalSize();
  void updateActions();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);
  void zoomIn();
  void zoomOut();
  double scaleFactor;
protected:
  //  void initializeGL();
  //  void resizeGL(int w, int h);
  //  void paintGL();
};

#endif // FUNDAMENTAL_H
