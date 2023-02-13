#include "winnerwidget.h"

WinnerWidget::WinnerWidget(QWidget *parent)
  :QWidget(parent)
{
  this->setFixedSize(300, 100);
  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->resize(300, 100);
}

WinnerWidget::WinnerWidget(QString string)
{
  this->setFixedSize(300, 100);
  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->resize(300, 100);
  label->setText(string);
  label->setFont(QFont("Arial", 50));
}
