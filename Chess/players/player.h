#ifndef PLAYER_H
#define PLAYER_H
#include "figures/figure.h"
#include <QObject>
#include <QVector>
#include <QString>

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QString nameOfPlayer, bool color);
public slots:
    void getVecOfFigures(QVector<Figure*> vec);
private:
    QString nameOfPlayer;
    bool color;
    QVector<Figure*> vecWithFigures;
};

#endif // PLAYER_H
