#include "client.h"

Client::Client()
{
    this->connectToHost(QHostAddress::LocalHost, 2323);

    connect(this, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);
}

void Client::sendToServer()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          string = string + array[i][j];
        }
    }
  qDebug()<<"ON CLIENT WAS:"<<string<<string.toUtf8();
  this->write(string.toUtf8());
  string.clear();
}

void Client::slotReadyRead()
{
    QObject* sender = QObject::sender();
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender);
}

void Client::getBoardOnClient(QChar value, int i , int j)
{
    array[i][j] = value;
}
