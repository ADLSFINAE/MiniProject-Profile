#ifndef HORSE_H
#define HORSE_H
#include "figures/figure.h"

class Horse : public Figure
{
    Q_OBJECT
public:
    Horse(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // HORSE_H
