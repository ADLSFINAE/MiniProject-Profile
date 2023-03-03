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
  bool isFirst;
  ~Widget();
public:
  QPushButton* changeIcon1{nullptr};
  QPushButton* changeIcon2{nullptr};
  QChar defaultLetter;

public slots:
  //logic for set a shit with general matrix from Server
  void blockButton(int i , int j, QChar name);
  void resetGamePlayers();
  void getMatrixFromServer(QString fromServer);


public slots:
  void showWinner(QString winnerShape); //Показ победителя
  void openFolder();  //Вызов панели для выставления картинки
  void changeName();  //Изменение пустого поля на кнопке после хода
  void resetGame(); //Обнуление доски
  void blockForNewGame(); //Если выигрывает кто-либо, то обе доски блокируются полностью
  void getMessageFromBoard(); //Собирательная модель работы между клиентом и виджетом

public slots:
  //Сигналы для блокировки досок, которые сходили и разблокировка той, которая должна ходить первой
  void slotBlockButtons();
  void slotUnblockButtons();
signals:
  //Общая система сигналов для работы с виджетом
  void signalForBlock();
  void givePixmap(QString string, ShowGamers* view);
  void sendToClient(QChar value, int i , int j);
  void sendBoardToServer();
  void signalBlockButton(int i , int j, QChar name);

signals:
  //Здесь сигналы на блокировку кнопок
  void signalToClientReset();
  void resetFor2Gamers();

signals:
  //Здесь сигналы на блокировку кнопок во время хода
  void signalBlockButtons();
  void signalUnblockButtons1();
  void signalUnblockButtons2();

private:
  QPushButton* button[3][3];
  QPushButton* resetButton{nullptr};
  bool checkStep = true;
  WinnerWidget* winnerWidget{nullptr};
  QVBoxLayout* playerLayout{nullptr};
  ShowGamers* users[2];

};
#endif // WIDGET_H
