#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>

class Client : public QTcpSocket
{
  Q_OBJECT
public:
  Client();
  void sendToServer(QString str);
public slots:
  void slotReadyRead();
private:
  QByteArray arr;
};

#endif // CLIENT_H
