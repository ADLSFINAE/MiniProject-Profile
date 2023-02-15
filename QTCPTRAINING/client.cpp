#include "client.h"
#include "qhostaddress.h"

Client::Client(QWidget *parent)
  :QWidget(parent)
{
  this->setFixedSize(200, 420);
  socket = new QTcpSocket(this);

  textEdit = new QTextEdit(this);
  textEdit->setReadOnly(true);
  textEdit->resize(200, 300);
  textEdit->move(0, 100);

  lineEdit = new QLineEdit(this);
  lineEdit->resize(120, 20);
  lineEdit->move(0, 400);

  label = new QLabel("Client", this);
  label->resize(200, 100);
  label->move(0, 0);
  label->setFont(QFont("Arial", 50));

  button = new QPushButton("&Send", this);
  button->resize(80, 20);
  button->move(120, 400);
  button->setFont(QFont("Arial", 10));
  connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
  connect(button, &QPushButton::clicked, this, &Client::clickedOnButton);
  socket->connectToHost(QHostAddress::LocalHost, 2323);
}

void Client::sendToServer(QString str)
{
  arr.clear();
  QDataStream out(&arr, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_15);
  out << str;
  socket->write(arr);
}

void Client::clickedOnButton()
{
  //socket->connectToHost(QHostAddress::LocalHost, 2323);
  sendToServer(lineEdit->text());
  textEdit->append(lineEdit->text());
}

void Client::slotReadyRead()
{
  QObject* sender = QObject::sender();
  socket = dynamic_cast<QTcpSocket*>(sender);

  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_5_15);
  if(in.status() == QDataStream::Ok){
      QString string;
      in >> string;
      textEdit->append(string);
    }
  else{
      textEdit->append("SLOT READY READ ERROR");
    }
}
