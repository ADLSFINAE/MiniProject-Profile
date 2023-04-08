#ifndef HORSE_H
#define HORSE_H
#include "figures/figure.h"

class Horse : public Figure
{
public:
    Horse(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions() override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // HORSE_H
