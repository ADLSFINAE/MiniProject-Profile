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
#include <QTextStream>
#include "showgamers.h"

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  void madeIcon(QGraphicsView *view, bool secondPlayer);
  ~Widget();
private:

  //logic to check winner (START)
  //logic to check winner (END)

public slots:
  void showWinner(QString winnerShape);
  void openFolder();
  void changeName();
  void resetGame();
  void blockForNewGame();
  void getMessageFromBoard();

signals:
  void signalForBlock();
  void givePixmap(QString string, ShowGamers* view);
  void sendToClient(QChar value, int i , int j);
  void sendBoardToServer();
public:
  QPushButton* changeIcon1{nullptr};
  QPushButton* changeIcon2{nullptr};
private:
  QPushButton* button[3][3];
  QPushButton* resetButton{nullptr};
  bool checkStep = true;
  WinnerWidget* winnerWidget{nullptr};
  QVBoxLayout* playerLayout{nullptr};
  ShowGamers* users[2];

};
#endif // WIDGET_H
