#include "report.h"
#include "ui_report.h"
#include"fundamental.h"
Report::Report(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Report)
{
  ui->setupUi(this);
}

Report::~Report()
{
  delete ui;
}

void Report::on_ButtonOK_clicked()
{
  this->close();
}

void Report::setReport(QString time, QString eval[], QImage img[])
{
  ui->label_1->setBackgroundRole(QPalette::Base);
  ui->label_1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->label_1->setScaledContents(true);
  ui->label_1->setPixmap(QPixmap::fromImage(img[0]));

  ui->label_3->setBackgroundRole(QPalette::Base);
  ui->label_3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->label_3->setScaledContents(true);
  ui->label_3->setPixmap(QPixmap::fromImage(img[1]));

  ui->label_5->setBackgroundRole(QPalette::Base);
  ui->label_5->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->label_5->setScaledContents(true);
  ui->label_5->setPixmap(QPixmap::fromImage(img[2]));

  ui->label_7->setBackgroundRole(QPalette::Base);
  ui->label_7->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->label_7->setScaledContents(true);
  ui->label_7->setPixmap(QPixmap::fromImage(img[3]));

  ui->label_2->setText(time+eval[0]);
  ui->label_4->setText(time+eval[1]);
  ui->label_6->setText(time+eval[2]);
  ui->label_8->setText(time+eval[3]);
}
