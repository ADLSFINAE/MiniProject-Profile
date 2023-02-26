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
#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void messageToClient(QString str);
private:
    void madeMatrix(QString data, bool secondPlayer);

    void checkOnEqualOfMatrix();
    void checkOnTheWin();
    void vertical();
    void horizontal();
    void diagonal();
    bool getInfo(const QString& str);
    void matrixAddition();

    void startInizialization();

public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);

private:
    QChar matrix1[3][3];
    QChar matrix2[3][3];
    QChar matrix[3][3];
    QList<QTcpSocket*> listOfClients;
    QString dataForTheFirstPlayer;
    QString dataForTheSecondPlayer;
};

#endif // SERVER_H
