#include "widget.h"
#include <QtAlgorithms>
#include <algorithm>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
  this->setFixedSize(300, 360);
  this->setWindowTitle("TicTacToe");
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          button[i][j] = new QPushButton(this);
          button[i][j]->resize(100, 100);
          button[i][j]->move(i * 100, j * 100);
          button[i][j]->setFont(QFont("Arial", 50));
          connect(button[i][j], &QPushButton::clicked, this, &Widget::changeName);
        }
    }

  resetButton = new QPushButton(this);
  resetButton->resize(300, 60);
  resetButton->move(0, 300);
  resetButton->setText("Reset Game");

  connect(resetButton, &QPushButton::clicked, this, &Widget::resetGame);
  connect(this, &Widget::signalForBlock, this, &Widget::blockForNewGame);

}

void Widget::getBoard()
{
  QString perfocard1;
  QString perfocard2;
  QString perfocard3;

  QString perfocard1i;
  QString perfocard2i;
  QString perfocard3i;

  QString diagonal1;
  QString diagonal2;
  int assistant = 2;

  for(int i = 0; i < 3; i++){
      perfocard1 = perfocard1 + button[0][i]->text();
      perfocard2 = perfocard2 + button[1][i]->text();
      perfocard3 = perfocard3 + button[2][i]->text();

      diagonal1 = diagonal1 + button[i][i]->text();
      if(assistant > -1){
          diagonal2 = diagonal2 + button[i][assistant]->text();
          assistant--;
        }

      perfocard1i = perfocard1i + button[i][0]->text();
      perfocard2i = perfocard2i + button[i][1]->text();
      perfocard3i = perfocard3i + button[i][2]->text();
    }

  if((perfocard3 == "xxx") || (perfocard2 == "xxx") || (perfocard1 == "xxx")
     || (perfocard3i == "xxx") || (perfocard2i == "xxx") || (perfocard1i == "xxx")
     || (diagonal1 == "xxx") || (diagonal2 == "xxx")){
      qDebug()<<"Win have XXX";
      winnerWidget = new WinnerWidget("x IS WIN");
      winnerWidget->show();
      emit signalForBlock();
    }
  else if((perfocard3 == "ooo") || (perfocard2 == "ooo") || (perfocard1 == "ooo")
     || (perfocard3i == "ooo") || (perfocard2i == "ooo") || (perfocard1i == "ooo")
     || (diagonal1 == "ooo") || (diagonal2 == "ooo")){
      qDebug()<<"Win have OOO";
      winnerWidget = new WinnerWidget("o IS WIN");
      winnerWidget->show();
      emit signalForBlock();
    }
}

Widget::~Widget()
{
}

void Widget::changeName()
{
  QObject* sender = QObject::sender();
  QPushButton* clickedButton = dynamic_cast<QPushButton*>(sender);
  count++;
  if(count % 2 == 0){
      clickedButton->setText(QString("o"));
      clickedButton->setEnabled(false);
      getBoard();
    }
  else{
      qDebug()<<button[1][1]->text();
      clickedButton->setText(QString("x"));
      clickedButton->setEnabled(false);
      getBoard();
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

void Widget::blockForNewGame()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          button[i][j]->setEnabled(false);
        }
    }
}

