#ifndef QUEEN_H
#define QUEEN_H
#include "figures/figures.h"

class Queen : public Figures
{
public:
    Queen(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // QUEEN_H
