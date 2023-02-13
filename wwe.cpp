#include "wwe.h"
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <string>
#include <QTimer>

Calculator::Calculator(QWidget *parent)
  :QWidget(parent){
  lcdNumber = new QLCDNumber;
  lcdNumber->setFixedHeight(50);

  QGridLayout* gridLayout = new QGridLayout;
  for(int i = 0; i < 9; i++){
      pushButton[i] = new QPushButton(QString(static_cast<char>((49 + i))));
      pushButton[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  }
  pushButtonC = new QPushButton("C");
  pushButtonPlus = new QPushButton("+/=");
  pushButtonC->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  pushButtonPlus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  QPushButton* button0 = new QPushButton("0");
  gridLayout->addWidget(lcdNumber, 0, 0, 1, 4);
  gridLayout->addWidget(pushButton[0], 1, 0);
  gridLayout->addWidget(pushButton[1], 1, 1);
  gridLayout->addWidget(pushButton[2], 1, 2);
  gridLayout->addWidget(pushButton[3], 2, 0);
  gridLayout->addWidget(pushButton[4], 2, 1);
  gridLayout->addWidget(pushButton[5], 2, 2);
  gridLayout->addWidget(pushButton[6], 3, 0);
  gridLayout->addWidget(pushButton[7], 3, 1);
  gridLayout->addWidget(pushButton[8], 3, 2);
  gridLayout->addWidget(pushButtonC, 1, 3);
  gridLayout->addWidget(pushButtonPlus, 2, 3, 3, 1);
  gridLayout->addWidget(button0, 4, 0, 1, 3);
  button0->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  //настройка родительского виджета
  this->setWindowTitle("Govnishe");
  this->resize(300, 300);
  this->setLayout(gridLayout);

  //коннекты, чтоб хуй стоял и функции работали
  for(int i = 0; i < 9; i++){
      connect(pushButton[i], &QPushButton::clicked, this, &Calculator::enteringNumber);
    }
  connect(button0, &QPushButton::clicked, this, &Calculator::enteringNumber);
  connect(pushButtonPlus, &QPushButton::clicked, this, &Calculator::plusEvent);
  connect(pushButtonC, &QPushButton::clicked, this, &Calculator::clearEvent);
}

void Calculator::enteringNumber()
{
   QObject* sender = QObject::sender();
   QPushButton* clickedButton = dynamic_cast<QPushButton*>(sender);
   mainNum = mainNum + clickedButton->text();
   lcdNumber->display(mainNum.toInt());
}

void Calculator::plusEvent()
{
  //lcdNumber->display(0);
  sum = sum + mainNum.toInt();
  mainNum.clear();
  qDebug()<<sum;
  lcdNumber->display(0);
}

void Calculator::clearEvent()
{
  sum = 0;
  mainNum.clear();
  lcdNumber->display(0);
}




