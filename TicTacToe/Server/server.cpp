#include "server.h"

#include <QString>
#include <QtAlgorithms>
#include <QRegExp>

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
    this->startInizialization();
    connect(this, &Server::signalToSendGeneralMatrixToAllClients, this, &Server::sendGeneralMatrixFromScene);
}

void Server::startInizialization()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          matrix[i][j] = '_';
          matrix1[i][j] = '_';
          matrix2[i][j] = '_';
        }
    }
}

void Server::messageToClient(QString str)
{
  for(int i = 0; i < listOfClients.size(); i++){
      listOfClients.at(i)->write(str.toUtf8());
    }
}

void Server::madeMatrix(QString data, bool secondPlayer)
{
  int size = 0;
  if(data.size() == 0){
      for(int i = 0; i < 9; i++){
          data.push_back('_');
        }
    }

  if(!secondPlayer){
      qDebug()<<"Data for the first player is: "<<data;
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
              matrix1[i][j] = data.at(size);
              size++;
            }
        }
    }
  else{
      qDebug()<<"Data for the second player is: "<<data;
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < 3; j++){
              matrix2[i][j] = data.at(size);
              size++;
            }
        }
    }
}

void Server::checkOnEqualOfMatrix()
{
  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
          if(matrix1[i][j] == matrix2[i][j]){
              matrix[i][j] = '_';
            }
          else{
              if(matrix1[i][j] == 'x') matrix[i][j] = 'x';
              if(matrix1[i][j] == 'o') matrix[i][j] = 'o';
              if(matrix2[i][j] == 'x') matrix[i][j] = 'x';
              if(matrix2[i][j] == 'o') matrix[i][j] = 'o';
            }
          matrixToSend = matrixToSend + matrix[i][j];
        }
    }
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
      messageToClient("WINNER EVENT");
      return true;
    }
  else if(str == OOO){
    messageToClient(OOO);
    messageToClient("WINNER EVENT");
    return true;
  }
  else
    return false;
}

void Server::slotReadyRead()
{
  dataForTheFirstPlayer = listOfClients.at(0)->readAll();
  dataForTheSecondPlayer = listOfClients.at(1)->readAll();
  qDebug()<<"SERVER GET INFO:"<<dataForTheFirstPlayer;
  qDebug()<<"SERVER GET INFO:"<<dataForTheSecondPlayer;
  this->madeMatrix(dataForTheFirstPlayer, true);
  this->madeMatrix(dataForTheSecondPlayer, false);
  dataForTheFirstPlayer.clear();
  dataForTheSecondPlayer.clear();
  checkOnEqualOfMatrix();
  emit signalToSendGeneralMatrixToAllClients();
  checkOnTheWin();
}

void Server::sendGeneralMatrixFromScene()
{
      qDebug()<<"matrixToSend on Server is: "<<matrixToSend;
      listOfClients.at(1)->write(matrixToSend.toUtf8());
      matrixToSend.clear();
}



void Server::incomingConnection(qintptr socketDescriptor)
{
  QTcpSocket* socket = new QTcpSocket;
  socket->setSocketDescriptor(socketDescriptor);
  listOfClients.append(socket);
  qDebug()<<"SOCKET IS OPEN OR WHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAT"<<socket->isOpen()<<listOfClients.size();
  connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

