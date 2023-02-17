#include "Internet/client.h"

Client::Client()
{
    this->connectToHost(QHostAddress::LocalHost, 2323);

    connect(this, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);
}

void Client::sendToServer(QString str)
{
  this->write(str.toUtf8());
}

void Client::slotReadyRead()
{
    QObject* sender = QObject::sender();
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender);
}
