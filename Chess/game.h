#ifndef GAME_H
#define GAME_H
#include <QVector>
#include <QPair>
#include "figures/figure.h"
#include "figures/pawn.h"
#include "figures/king.h"
#include "figures/figure.h"
#include "figures/horse.h"
#include "figures/queen.h"
#include "figures/elephant.h"
#include "figures/rook.h"

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

    King* whiteKing{nullptr};
    King* blackKing{nullptr};

    void afterUs(QVector<Block*>queenVec, QVector<Block*>blackKingVec, QSet<Block*>& CEELO);
public slots:
    void editVecs(QVector<Figure*>& vecs);
    void calculateCheckMateFunc(bool colorOfTheKing);
signals:
    void getPawnCollection(QVector< QPair <Figure*, QPointF> >& collection, bool color);
    void signalStartCalculatingCheckMateFROMWHITE(bool colorOfTheKing);
    void signalStartCalculatingCheckMateFROMBLACK(bool colorOfTheKing);
    void exportCEELOToKingFromWhite(QSet<Block*> block);
    void exportCEELOToKingFromBlack(QSet<Block*> block);
};

#endif // GAME_H
