#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLabel>
#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QHostAddress>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void messageToClient(QString str);

public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);

private:
    QTcpSocket* socket{nullptr};
};

#endif // SERVER_H
