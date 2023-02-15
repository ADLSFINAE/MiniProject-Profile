#include "server.h"

Server::Server(QWidget *parent)
  :QWidget(parent)
{
  this->setFixedSize(200, 400);

  server = new QTcpServer(this);
  if(server->listen(QHostAddress::Any, 2323)){
      qDebug()<<"give me some cringe";
    }
  else{
      qDebug()<<"HAPPENINGS VERY CRINGE SITUATION KYS";
    }

  textEdit = new QTextEdit(this);
  textEdit->setReadOnly(true);
  textEdit->resize(200, 300);
  textEdit->move(0, 100);

  label = new QLabel("Server", this);
  label->resize(200, 100);
  label->move(0, 0);
  label->setFont(QFont("Arial", 50));
}

void Server::messageToClient(QString str)
{
  arr.clear();
  QDataStream out(&arr, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_15);
  out << str;
  socket->write(arr);
}

void Server::slotReadyRead()
{
  QObject* sender = QObject::sender();
  socket = dynamic_cast<QTcpSocket*>(sender);

  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_5_15);
  if(in.status() == QDataStream::Ok){
      qDebug()<<"All okay";
      QString str;
      in >> str;
      qDebug()<<str;
      messageToClient(str);
      textEdit->append(str);
    }
  else{
      qDebug()<<"Error in slotReadyRead()";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  //Дескриптор число, которое идентифицирует поток in/out
  socket = new QTcpSocket(this);
  socket->setSocketDescriptor(socketDescriptor);
  qDebug()<<"AAAAAAAAAAAAAA";
  connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
  qDebug()<<"descriptor number"<<socketDescriptor;
}
