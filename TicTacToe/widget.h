#ifndef WIDGET_H
#define WIDGET_H

#include "winnerwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsView>
#include "showgamers.h"

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  void getBoard();
  void madeIcon(QGraphicsView *view, bool secondPlayer);
  ~Widget();

public slots:
  void openFolder();

  void changeName();
  void resetGame();
  void blockForNewGame();
signals:
  void signalForBlock();
  void givePixmap(QString string, ShowGamers* view);
private:
  QPushButton* button[3][3];
  QPushButton* resetButton;
  int count = 0;
  WinnerWidget* winnerWidget;
  QVBoxLayout* playerLayout;
  ShowGamers* users[2];
  QPushButton* changeIcon1;
  QPushButton* changeIcon2;

};
#endif // WIDGET_H
