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
private:
    void madeMatrix(QString data);

    void checkOnTheWin();
    void vertical();
    void horizontal();
    void diagonal();
    bool getInfo(const QString& str);

public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);

private:
    QTcpSocket* socket{nullptr};
    QChar matrix[3][3];
};

#endif // SERVER_H
