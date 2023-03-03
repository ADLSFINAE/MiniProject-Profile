#include "client.h"
#include "showgamers.h"
#include "widget.h"
#include <QApplication>
#include <QObject>
#include <QChar>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//FIRST CLIENT
  Widget w;
  w.isFirst = true;
  w.defaultLetter = 'x';
  w.setWindowTitle("X");

  ShowGamers* player1ForW = new ShowGamers;
  w.madeIcon(player1ForW, true);
  QObject::connect(&w, &Widget::givePixmap, player1ForW, &ShowGamers::changePixmapForPlayer);

  ShowGamers* player2ForW = new ShowGamers;
  w.madeIcon(player2ForW, false);
  QObject::connect(&w, &Widget::givePixmap, player2ForW, &ShowGamers::changePixmapForPlayer);
  w.changeIcon2->setEnabled(false);

  Client client;
  QObject::connect(&w, &Widget::sendToClient, &client, &Client::getBoardOnClient);
  QObject::connect(&w, &Widget::sendBoardToServer, &client, &Client::sendToServer);
  QObject::connect(&client, &Client::sendAWinnerOnWidget, &w, &Widget::showWinner);

  w.show();
//SECOND CLIENT
  Widget w2;
  w2.isFirst = false;
  w2.defaultLetter = 'o';
  w2.setWindowTitle("O");

  ShowGamers* player1ForW2 = new ShowGamers;
  w2.madeIcon(player1ForW2, true);
  QObject::connect(&w2, &Widget::givePixmap, player1ForW2, &ShowGamers::changePixmapForPlayer);

  ShowGamers* player2ForW2 = new ShowGamers;
  w2.madeIcon(player2ForW2, false);
  QObject::connect(&w2, &Widget::givePixmap, player2ForW2, &ShowGamers::changePixmapForPlayer);
  w2.changeIcon1->setEnabled(false);

  Client client2;
  QObject::connect(&w2, &Widget::sendToClient, &client2, &Client::getBoardOnClient);
  QObject::connect(&w2, &Widget::sendBoardToServer, &client2, &Client::sendToServer);
  QObject::connect(&client2, &Client::sendAWinnerOnWidget, &w2, &Widget::showWinner);

  //THIS CODE IS SUBOPTIMAL AND NEED A UPDATE, CAUSE I DON'T KNOW HOW IT WORKS
  QObject::connect(&client, &Client::signalGetMatrixFromServer, &w, &Widget::getMatrixFromServer);
  QObject::connect(&client, &Client::signalGetMatrixFromServer, &w2, &Widget::getMatrixFromServer);
  QObject::connect(&w, &Widget::signalBlockButton, &w2, &Widget::blockButton);

  QObject::connect(&client2, &Client::signalGetMatrixFromServer, &w, &Widget::getMatrixFromServer);
  QObject::connect(&client2, &Client::signalGetMatrixFromServer, &w2, &Widget::getMatrixFromServer);
  QObject::connect(&w2, &Widget::signalBlockButton, &w, &Widget::blockButton);

 QObject::connect(&w, &Widget::resetFor2Gamers, &w, &Widget::resetGame);
 QObject::connect(&w, &Widget::resetFor2Gamers, &w2, &Widget::resetGame);

 QObject::connect(&w2, &Widget::resetFor2Gamers, &w, &Widget::resetGame);
 QObject::connect(&w2, &Widget::resetFor2Gamers, &w2, &Widget::resetGame);

 QObject::connect(&client, &Client::signalToBlockAllUsersButtons, &w2, &Widget::blockForNewGame);
 QObject::connect(&client2, &Client::signalToBlockAllUsersButtons, &w, &Widget::blockForNewGame);

 QObject::connect(&w, &Widget::signalUnblockButtons1, &w2, &Widget::slotUnblockButtons);
 QObject::connect(&w2, &Widget::signalUnblockButtons2, &w, &Widget::slotUnblockButtons);
  w2.show();

  return a.exec();
}
