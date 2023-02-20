#include "server.h"

const QString XXX = "xxx";
const QString OOO = "ooo";

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

void Server::madeMatrix(QString data)
{
  int size = 0;
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          matrix[i][j] = data.at(size);
          size++;
        }
    }
  size = 0;
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          qDebug().nospace()<<matrix[i][j];
        }
      qDebug()<<Qt::endl;
    }
  checkOnTheWin();
}

void Server::checkOnTheWin()
{
  this->vertical();
  this->horizontal();
  this->diagonal();
}

void Server::vertical()
{
  QString firstLine;
  QString secondLine;
  QString thristLine;

  for(int i = 0; i < 3; i++){
      firstLine = firstLine + matrix[0][i];
      secondLine = secondLine + matrix[1][i];
      thristLine = thristLine + matrix[2][i];
    }
  this->getInfo(firstLine);
  this->getInfo(secondLine);
  this->getInfo(thristLine);
}

void Server::horizontal()
{
  QString firstLine;
  QString secondLine;
  QString thristLine;

  for(int i = 0; i < 3; i++){
      firstLine = firstLine + matrix[i][0];
      secondLine = secondLine + matrix[i][1];
      thristLine = thristLine + matrix[i][2];
    }
  this->getInfo(firstLine);
  this->getInfo(secondLine);
  this->getInfo(thristLine);
}

void Server::diagonal()
{
  QString firstDiagonal;
  QString secondDiagonal;
  int assistant = 2;
  for(int i = 0; i < 3; i++){
      firstDiagonal = firstDiagonal + matrix[i][i];
      secondDiagonal = secondDiagonal+ matrix[i][assistant];
      assistant--;
    }

  this->getInfo(firstDiagonal);
  this->getInfo(secondDiagonal);
}

bool Server::getInfo(const QString &str)
{
  if(str == XXX){
      messageToClient(XXX);
      return true;
    }
  else if(str == OOO){
    messageToClient(OOO);
    return true;
  }
  else
    return false;
}

void Server::slotReadyRead()
{
    QString data = socket->readAll();
    this->madeMatrix(data);
    qDebug()<<"SLOT READY READ WAS CALLING"<<data;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}
