#include "server.h"

Server::Server()
{
    if (not listen(QHostAddress::Any, 2323))
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
    std::reverse(str.begin(), str.end());
    socket->write(str.toUtf8());
    emit dataReceived("Сервер отправил клиенту сообщение: " + str);
}

void Server::slotReadyRead()
{
    QString data = socket->readAll();
    emit dataReceived("Сервер получил сообщение от клиента: " + data);
    messageToClient(data);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    emit dataReceived(QStringLiteral("Подключен клиент с дескриптором %1`").arg(socketDescriptor));
}
