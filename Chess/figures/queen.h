#ifndef QUEEN_H
#define QUEEN_H
#include "figures/figure.h"

class Queen : public Figure
{
public:
    Queen(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // QUEEN_H
