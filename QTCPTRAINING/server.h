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

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void messageToClient(QString str);

public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);

signals:
    void dataReceived(const QString& data);

private:
    QTcpSocket* socket;
};

#endif // SERVER_H
