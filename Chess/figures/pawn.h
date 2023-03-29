#ifndef PAWN_H
#define PAWN_H
#include "figures/figures.h"
#include "board.h"

class Pawn : public Figures
{
public:
    Pawn(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    bool isWhite;
};

#endif // PAWN_H
