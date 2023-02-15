#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLabel>
#include <QByteArray>
#include <QDataStream>
#include <QString>.

class Server : public QWidget
{
  Q_OBJECT
public:
  Server(QWidget* parent = nullptr);
  void messageToClient(QString str);

public slots:
  void slotReadyRead();
  void incomingConnection(qintptr socketDescriptor);

private:
  QByteArray arr;
  QTcpServer* server;
  QTcpSocket* socket;
  QLabel* label;
  QTextEdit* textEdit;
};

#endif // SERVER_H
