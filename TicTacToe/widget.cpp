#include "widget.h"
#include <QtAlgorithms>
#include <algorithm>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
  this->setFixedSize(300, 360);

  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          button[i][j] = new QPushButton(this);
          button[i][j]->resize(100, 100);
          button[i][j]->move(i * 100, j * 100);
          connect(button[i][j], &QPushButton::clicked, this, &Widget::changeName);
        }
    }

  resetButton = new QPushButton(this);
  resetButton->resize(300, 60);
  resetButton->move(0, 300);
  resetButton->setText("Reset Game");
  connect(resetButton, &QPushButton::clicked, this, &Widget::resetGame);


}

QString Widget::getBoard(int version)
{
  QString perfocard;
  if(version == 0){
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
              perfocard = perfocard + button[i][j]->text();
              qDebug()<<button[i][j]->text();
            }
          qDebug()<<Qt::endl;
        }
      qDebug()<<"Perfocard info is: "<<perfocard;
      return perfocard;
    }
  else if(version == 1){
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
              if(i == j){
                  button[i][j]->text();
                }
            }
        }
    }
  else{
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
              perfocard = perfocard + button[i][j]->text();
              qDebug()<<button[j][i]->text();
            }
          qDebug()<<Qt::endl;
        }
      qDebug()<<"Perfocard info is: "<<perfocard;
      return perfocard;
    }
}

Widget::~Widget()
{
}

void Widget::algorithm(QString string)
{
  if(string.indexOf(QString("ooo")) != (-1)){
      qDebug()<<"O WIN THE GAME";
    }

  if(string.indexOf(QString("xxx")) != (-1)){
      qDebug()<<"X WIN THE GAME";
    }
}

void Widget::changeName()
{
  QObject* sender = QObject::sender();
  QPushButton* clickedButton = dynamic_cast<QPushButton*>(sender);
  count++;
  if(count % 2 == 0){
      clickedButton->setText(QString("o"));
      clickedButton->setEnabled(false);
      algorithm(getBoard(0));
      algorithm(getBoard(1));
    }
  else{
      clickedButton->setText(QString("x"));
      clickedButton->setEnabled(false);
      algorithm(getBoard(0));
      algorithm(getBoard(1));
    }
}

void Widget::resetGame()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          button[i][j]->setText(QString(""));
          button[i][j]->setEnabled(true);
        }
    }
}

