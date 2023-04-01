#ifndef PAWN_H
#define PAWN_H
#include "figures/figures.h"

class Pawn : public Figures
{
public:
    Pawn(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions() override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // PAWN_H
