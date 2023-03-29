#ifndef ROOK_H
#define ROOK_H
#include "figures/figures.h"

class Rook : public Figures
{
public:
    Rook(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // ROOK_H
