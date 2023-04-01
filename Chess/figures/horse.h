#ifndef HORSE_H
#define HORSE_H
#include "figures/figures.h"

class Horse : public Figures
{
public:
    Horse(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions() override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // HORSE_H
