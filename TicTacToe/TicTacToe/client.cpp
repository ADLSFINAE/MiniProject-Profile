#include "client.h"

const QString XXX = "xxx";
const QString OOO = "ooo";

Client::Client()
{
    //socket for write to server matrix
    this->connectToHost(QHostAddress::LocalHost, 2323);

    connect(this, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    //socket from read from server matrix
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

    QString string = socket->readAll();
    if(string == "WINNER EVENT"){
        emit signalToBlockAllUsersButtons();
      }
    if(string == XXX || string == OOO){
        emit sendAWinnerOnWidget(string);
      }
    else{
        QString support;
        for(int i = 0; i < 9; i++){
            support.push_back(string[i]);
          }
       qDebug()<<"On general matrix generated cringe by:"<<support;
        emit signalGetMatrixFromServer(support);
      }
}

void Client::getBoardOnClient(QChar value, int i , int j)
{
  array[i][j] = value;
}


