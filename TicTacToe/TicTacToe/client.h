#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QTextStream>

class Client : public QTcpSocket
{
  Q_OBJECT
public:
  Client();

public slots:
  void slotReadyRead();
  void sendToServer();
  void getBoardOnClient(QChar value, int i , int j);
signals:
  void sendAWinnerOnWidget(QString string);
  void signalGetMatrixFromServer(QString fromServer);

  void signalToBlockAllUsersButtons();

private:
  QByteArray arr;
  QChar array[3][3];
  QString string;
  //Нужно чистить, так как если вызывается resetGame он нихуя не пустой
};

#endif // CLIENT_H
