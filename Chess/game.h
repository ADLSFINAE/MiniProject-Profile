#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <QPair>
#include "figures/figure.h"
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    void initOfVecs(Figure* figure, bool isWhite);
    void giveInfo();
    QVector< QPair <Figure*, QPointF> > vecOfBlackFigures;
    QVector< QPair <Figure*, QPointF> > vecOfWhiteFigures;
};

#endif // GAME_H
