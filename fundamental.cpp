#include"fundamental.h"
#include"libs.h"
#include"report.h"

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
  initializeQ();
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



void ImageDisplayer::clean()
{
  ;
}

void ImageDisplayer::initializeQ()
{

  Qjpeg=(Mat_<double>(8,8)<<
         16,11,10,16,24,40,51,61,
         12,12,14,19,26,58,60,55,
         14,13,16,24,40,57,69,55,
         14,17,22,29,51,87,80,62,
         18,22,37,56,68,109,103,77,
         24,35,55,64,81,104,113,92,
         49,64,78,87,103,121,120,101,
         72,92,95,98,112,100,103,99);

  Qcannon=(Mat_<double>(8,8)<<
           1,1,1,2,3,6,8,10,
           1,1,2,3,4,8,9,8,
           2,2,2,3,6,8,10,8,
           2,2,3,4,7,12,11,9,
           3,3,8,11,10,16,15,11,
           3,5,8,10,12,15,16,13,
           7,10,11,12,15,17,17,14,
           14,13,13,15,15,14,14,14);

  Qnikon=(Mat_<double>(8,8)<<
          2,1,1,2,3,5,6,7,
          1,1,2,2,3,7,7,7,
          2,2,2,3,5,7,8,7,
          2,2,3,3,6,10,10,7,
          2,3,4,7,8,13,12,9,
          3,4,7,8,10,12,14,11,
          6,8,9,10,12,15,14,12,
          9,11,11,12,13,12,12,12);

}
