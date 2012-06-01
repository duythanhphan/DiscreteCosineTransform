#include"fundamental.h"
#include"libs.h"


ImageDisplayer::ImageDisplayer(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::ImageDisplayer)
{
  img=NULL;
  ui->setupUi(this);
  initializeIcons();
  //initializeWidgets();
  //initializeShortcuts();
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  //scrollArea->setWidgetResizable(true);
  setCentralWidget(scrollArea);

  resize(1024,600);
}

ImageDisplayer::~ImageDisplayer()
{
  delete ui;
}

void ImageDisplayer::loadImage()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),"/home/gsc/Documents",tr("Image Files (*.png *.jpg *.bmp *.jpeg *.tiff *.tif *.p?m *.sr *.jp2);;All Files (*.*);;BMP(*.bmp);;JPEG(*.jpg *.jpeg *.jp2);;PNG(*.png);;TIFF(*.tif *.tiff)"));
  if (!fileName.isEmpty())
    {
      cout<<fileName.toStdString()<<endl;
      //this->img=cvLoadImage(fileName.toStdString().c_str(),CV_LOAD_IMAGE_GRAYSCALE);
      //img=im_gray;
      mtx_color=imread(fileName.toStdString().c_str());
      cvtColor(mtx_color,mtx,CV_RGB2GRAY);
     //Mat mtxQimg;
      //cvtColor(mtx,mtxQimg,CV_BGR2RGB);
     // Mat mtxb = mtx >256;
      img=new IplImage(mtx);
       QImage qimg=IplImage2QImage(this->img);
      //QImage qimg((uchar*)mtxQimg.data,mtxQimg.cols,mtxQimg.rows,QImage::Format_RGB32);
      imageLabel->setPixmap(QPixmap::fromImage(qimg));
      scaleFactor = 1.0;

      ui->action_Fit_to_Window->setEnabled(true);
      updateActions();

      if (!ui->action_Fit_to_Window->isChecked())
        {
          imageLabel->adjustSize();
        }
    }
}

void ImageDisplayer::on_actionExit_triggered()
{
  this->close();
}

void ImageDisplayer::on_actionOpen_triggered()
{
  this->loadImage();
}

void ImageDisplayer::on_action_About_triggered()
{
  QMessageBox::about(this, tr("About DCT"),
                     tr("Written by GaoShichao"));
}

void ImageDisplayer::on_action_Fit_to_Window_triggered()
{
  fitToWindow();
}

void ImageDisplayer::on_action_Actual_Size_triggered()
{
  normalSize();
}

void ImageDisplayer::fitToWindow()
{
  bool fitToWindow =ui->action_Fit_to_Window->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);

  if (!fitToWindow) {
      normalSize();
    }
  updateActions();
}

void ImageDisplayer::normalSize()
{
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void ImageDisplayer::updateActions()
{
  ui->actionZoom_In->setEnabled(!ui->action_Fit_to_Window->isChecked());
  ui->actionZoom_Out->setEnabled(!ui->action_Fit_to_Window->isChecked());
  ui->action_Actual_Size->setEnabled(!ui->action_Fit_to_Window->isChecked());
}

void ImageDisplayer::initializeIcons()
{
  ui->actionOpen->setIcon(qcs.standardIcon(QStyle::SP_DirIcon,0,0));
  ui->actionExit->setIcon(qcs.standardIcon(QStyle::SP_DialogCloseButton,0,0));
}

void ImageDisplayer::zoomIn()
//! [9] //! [10]
{
  scaleImage(1.25);
}

void ImageDisplayer::zoomOut()
{
  scaleImage(0.8);
}

void ImageDisplayer::on_actionZoom_In_triggered()
{
  zoomIn();
}

void ImageDisplayer::on_actionZoom_Out_triggered()
{
  zoomOut();
}

void ImageDisplayer::scaleImage(double factor)
{
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

}


void ImageDisplayer::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
  scrollBar->setValue(int(factor * scrollBar->value()
                          + ((factor - 1) * scrollBar->pageStep()/2)));
}

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
  Mi1DDCT=imgInverse_1D_DCT(M1DDCT);
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
  Mi2DDCT_whole=imgInverse_2D_DCT(M2DDCT_whole);
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
  M88iDCT=img88Inverse_DCT(M88DCT,mtx.rows,mtx.cols);
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
