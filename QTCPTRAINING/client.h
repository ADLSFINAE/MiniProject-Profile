#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QTcpSocket>
#include <QLineEdit>
#include <QPushButton>
#include <QByteArray>

class Client : public QWidget
{
  Q_OBJECT
public:
  Client(QWidget* parent = nullptr);
  void sendToServer(QString str);
public slots:
  void clickedOnButton();
  void slotReadyRead();
private:
  QTcpSocket* socket{nullptr};
  QByteArray arr;
  QLabel* label{nullptr};
  QTextEdit* textEdit{nullptr};
  QLineEdit* lineEdit{nullptr};
  QPushButton* button{nullptr};
};

#endif // CLIENT_H
