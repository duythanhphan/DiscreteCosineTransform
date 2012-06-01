#ifndef REPORT_H
#define REPORT_H

#include <QDialog>


namespace Ui {
  class Report;
}

class Report : public QDialog
{
  //Q_OBJECT
  
public slots:
  void on_ButtonOK_clicked();
public:
  explicit Report(QWidget *parent = 0);
  ~Report();
  void setReport(QString time,QString eval[4],QImage img[4]);
private:
  Ui::Report *ui;
};

#endif // REPORT_H
