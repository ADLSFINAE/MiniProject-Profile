#ifndef PAWN_H
#define PAWN_H
#include "figures/figure.h"

class Pawn : public Figure
{
public:
    Pawn(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions() override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // PAWN_H
