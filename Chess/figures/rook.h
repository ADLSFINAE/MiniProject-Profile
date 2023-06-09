#ifndef ROOK_H
#define ROOK_H
#include "figures/figure.h"

class Rook : public Figure
{
    Q_OBJECT
public:
    Rook(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
    void getKnowledge(QVector<Block*> vec_block);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // ROOK_H
