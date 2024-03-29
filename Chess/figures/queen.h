#ifndef QUEEN_H
#define QUEEN_H
#include "figures/figure.h"

class Queen : public Figure
{
    Q_OBJECT
public:
    Queen(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
    void getKnowledge(QVector<Block*> vec_block);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // QUEEN_H
