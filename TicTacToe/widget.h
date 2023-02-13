#ifndef WIDGET_H
#define WIDGET_H

#include "winnerwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QLabel>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  void getBoard();
  ~Widget();

public slots:
  void changeName();
  void resetGame();
  void blockForNewGame();
signals:
  void signalForBlock();
private:
  QPushButton* button[3][3];
  QPushButton* resetButton;
  int count = 0;
  WinnerWidget* winnerWidget;

};
#endif // WIDGET_H
