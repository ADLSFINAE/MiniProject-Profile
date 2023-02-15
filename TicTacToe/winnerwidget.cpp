#include "winnerwidget.h"

WinnerWidget::WinnerWidget(QString string, QWidget *parent)
  :QWidget(parent)
{
  this->setFixedSize(300, 100);
  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->resize(300, 100);
  label->setText(string);
  label->setFont(QFont("Arial", 50));
}
