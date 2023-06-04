#ifndef ELEPHANT_H
#define ELEPHANT_H
#include "figures/figure.h"

class Elephant : public Figure
{
    Q_OBJECT
public:
    Elephant(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
    void getKnowledge(QVector<Block*> vec_block);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // ELEPHANT_H
