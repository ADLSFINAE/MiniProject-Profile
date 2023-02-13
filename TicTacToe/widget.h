#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  QString getBoard(int version);
  ~Widget();
  void algorithm(QString string);

public slots:
  void changeName();
  void resetGame();
signals:
private:
  QPushButton* button[3][3];
  QPushButton* resetButton;
  int count = 0;
};
#endif // WIDGET_H
