#ifndef WINNERWIDGET_H
#define WINNERWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QFont>

class WinnerWidget : public QWidget
{
  Q_OBJECT
public:
  WinnerWidget(QWidget *parent = nullptr);
  WinnerWidget(QString string);
private:
  QLabel* label;
  QString string;
};

#endif // WINNERWIDGET_H
