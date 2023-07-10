#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QPair>
#include <QDebug>
#include <QObject>

#include "figures/figure.h"
#include "figures/pawn.h"
#include "figures/king.h"
#include "figures/figure.h"
#include "figures/horse.h"
#include "figures/queen.h"
#include "figures/elephant.h"
#include "figures/rook.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    void initOfVecs(Figure* figure, bool isWhite);

public:
    QVector< QPair <Figure*, QPointF> > vecOfBlackFigures;
    QVector< QPair <Figure*, QPointF> > vecOfWhiteFigures;
    QVector< QPair <Figure*, QPointF> > vecOfAllFigures;
    QVector< QPair <Figure*, QPointF> > vecOfBlackPawnFigures;
    QVector< QPair <Figure*, QPointF> > vecOfWhitePawnFigures;

public slots:
    void countOfSteps();
    void editVecs(QVector<Figure*>& vecs);
    void calculateCheckMateFunc(bool colorOfTheKing);

signals:
    void getPawnCollection(QVector< QPair <Figure*, QPointF> >& collection);
    void sendAllFigures(QVector< QPair <Figure*, QPointF> >& collection);
    void signalStartCalculatingCheckMateFROMWHITE(bool colorOfTheKing);
    void signalStartCalculatingCheckMateFROMBLACK(bool colorOfTheKing);
    void exportCEELOToKingFromWhite(QSet<Block*> block);
    void exportCEELOToKingFromBlack(QSet<Block*> block);

    void exportFiguresVec(QVector<Figure*> fig);

private:
    void afterUs(Figure* figure, King *king, QSet<Block*>& CEELO, QVector<Figure*>& figVec);

private:
    King* whiteKing{nullptr};
    King* blackKing{nullptr};
    int count = 0;

};

#endif // GAME_H
