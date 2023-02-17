#include "widget.h"
#include "showgamers.h"
#include <QtAlgorithms>
#include <algorithm>
#include <QFileDialog>

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
        }
    }

  resetButton = new QPushButton(this);
  resetButton->resize(300, 60);
  resetButton->move(60, 300);
  resetButton->setText("Reset Game");

  connect(resetButton, &QPushButton::clicked, this, &Widget::resetGame);
  connect(this, &Widget::signalForBlock, this, &Widget::blockForNewGame);
}

void Widget::getBoard()
{
  //0
  QString perfocard1;
  QString perfocard2;
  QString perfocard3;

  //+90
  QString perfocard1i;
  QString perfocard2i;
  QString perfocard3i;

  //diagonals
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

  count++;

  if(count % 2 == 0){
      clickedButton->setText(QString("o"));
      clickedButton->setEnabled(false);
      getBoard();
    }
  else{
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

