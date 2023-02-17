#include "showgamers.h"
#include "widget.h"
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  ShowGamers* player1 = new ShowGamers;
  w.madeIcon(player1, true);
  //QObject::connect(w, &Widget::givePixmap(QString), player1, &ShowGamers::changePixmapForPlayer(QString));
  ShowGamers* player2 = new ShowGamers;
  w.madeIcon(player2, false);
  w.show();
  QObject::connect(&w, &Widget::givePixmap, player1, &ShowGamers::changePixmapForPlayer);
  QObject::connect(&w, &Widget::givePixmap, player2, &ShowGamers::changePixmapForPlayer);
  return a.exec();
}
