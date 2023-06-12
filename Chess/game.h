#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <QPair>
#include "figures/figure.h"
#include "figures/pawn.h"
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

    QVector< QPair <Figure*, QPointF> > vecOfBlackPawnFigures;
    QVector< QPair <Figure*, QPointF> > vecOfWhitePawnFigures;
public slots:
    void editVecs(QVector<Figure*>& vecs);
signals:
    void getPawnCollection(QVector< QPair <Figure*, QPointF> >& collection, bool color);
};

#endif // GAME_H
