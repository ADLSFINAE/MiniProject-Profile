#include "Internet/server.h"

Server::Server()
{
    if (!listen(QHostAddress::Any, 2323))
    {
        qDebug() << "Not working";
    }
    else
    {
        qDebug() << "Working";
    }
}

void Server::messageToClient(QString str)
{
    socket->write(str.toUtf8());
}

void Server::slotReadyRead()
{
    QString data = socket->readAll();
    qDebug()<<data;
    messageToClient(data);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}
