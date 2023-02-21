#include "server.h"

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
    for(int i = 0; i < listOfClients.size(); i++){
        QTcpSocket* item = listOfClients.at(i);
        item->write(str.toUtf8());
      }
}

void Server::slotReadyRead()
{
  for(int i = 0; i < listOfClients.size(); i++){
          QString data = listOfClients.at(i)->readAll();
          if(data.size() > 0){
              emit dataReceived("Сервер получил сообщение от клиента: " + data);
              messageToClient(data);
            }
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  QTcpSocket* socket = new QTcpSocket;
  socket->setSocketDescriptor(socketDescriptor);
  listOfClients.append(socket);
  qDebug()<<"SOCKET WAS CREATING";
  qDebug()<<"SOCKET IS OPEN:"<<socket->isOpen();

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    emit dataReceived(QStringLiteral("Подключен клиент с дескриптором %1`").arg(socketDescriptor));
}



