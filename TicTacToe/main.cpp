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
  QObject::connect(&w, &Widget::givePixmap, player1, &ShowGamers::changePixmapForPlayer);

  ShowGamers* player2 = new ShowGamers;
  w.madeIcon(player2, false);
  QObject::connect(&w, &Widget::givePixmap, player2, &ShowGamers::changePixmapForPlayer);

  w.show();

  return a.exec();
}
