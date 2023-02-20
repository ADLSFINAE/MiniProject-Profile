#include "widget.h"
#include "showgamers.h"
#include <QtAlgorithms>
#include <algorithm>
#include <QFileDialog>

const QString XXX = "xxx";
const QString OOO = "ooo";

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
  this->setFixedSize(420, 360);
  this->setWindowTitle("TicTacToe");

  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          button[i][j] = new QPushButton(this);
          button[i][j]->resize(100, 100);
          button[i][j]->move((i * 100) + 60, j * 100);
          button[i][j]->setFont(QFont("Arial", 50));
          connect(button[i][j], &QPushButton::clicked, this, &Widget::changeName);
          connect(button[i][j], &QPushButton::clicked, this, &Widget::getMessageFromBoard);
        }
    }

  resetButton = new QPushButton(this);
  resetButton->resize(300, 60);
  resetButton->move(60, 300);
  resetButton->setText("Reset Game");

  connect(resetButton, &QPushButton::clicked, this, &Widget::resetGame);
  connect(this, &Widget::signalForBlock, this, &Widget::blockForNewGame);
}

void Widget::madeIcon(QGraphicsView *view, bool secondPlayer)
{
  QWidget* playerIcon = new QWidget(this);
  playerIcon->resize(60, 80);

  if(!secondPlayer){
      users[0] = dynamic_cast<ShowGamers*>(view);
      QWidget* playerIcon = new QWidget(this);
      playerIcon->resize(60, 80);
      playerIcon->move(0, 0);

      changeIcon1 = new QPushButton(playerIcon);
      changeIcon1->setText(QString("ICON"));
      changeIcon1->resize(60, 20);

      connect(changeIcon1, &QPushButton::clicked, this, &Widget::openFolder);

      playerLayout = new QVBoxLayout;
      playerLayout->addWidget(view, 1);
      playerLayout->addWidget(changeIcon1, 2);
      playerLayout->setMargin(0);

      playerIcon->setLayout(playerLayout);
    }
  else{
      users[1] = dynamic_cast<ShowGamers*>(view);
      QWidget* playerIcon = new QWidget(this);
      playerIcon->resize(60, 80);
      playerIcon->move(360, 0);

      changeIcon2 = new QPushButton(playerIcon);
      changeIcon2->setText(QString("ICON"));
      changeIcon2->resize(60, 20);

      connect(changeIcon2, &QPushButton::clicked, this, &Widget::openFolder);

      playerLayout = new QVBoxLayout;
      playerLayout->addWidget(view, 1);
      playerLayout->addWidget(changeIcon2, 2);
      playerLayout->setMargin(0);

      playerIcon->setLayout(playerLayout);
    }
}

Widget::~Widget()
{
}

void Widget::showWinner(QString winnerShape)
{
  winnerWidget = new WinnerWidget(winnerShape + " :Win the Game");
  winnerWidget->show();
  emit signalForBlock();
}

void Widget::openFolder()
{
  QString string = QFileDialog::getOpenFileName(this, "Open File", "C://");

  if(dynamic_cast<QPushButton*>(QObject::sender()) == changeIcon1)
      emit givePixmap(string, users[0]);
  else
      emit givePixmap(string, users[1]);
}

void Widget::changeName()
{
  QObject* sender = QObject::sender();
  QPushButton* clickedButton = dynamic_cast<QPushButton*>(sender);

  if(checkStep){
      clickedButton->setText(QString("o"));
      clickedButton->setEnabled(false);
      checkStep = false;
    }
  else{
      clickedButton->setText(QString("x"));
      clickedButton->setEnabled(false);
      checkStep = true;
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

void Widget::getMessageFromBoard()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){

          if(button[i][j]->text() != "")
            emit sendToClient(button[i][j]->text().at(0), i, j);
          else
            emit sendToClient('_', i, j);

          if(button[i][j]->text() == "o")
            qDebug()<<"GOVNO O"<<i<<j;
        }
    }
  emit sendBoardToServer();
}


