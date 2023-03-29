#ifndef KING_H
#define KING_H
#include "block.h"
#include "board.h"
#include "figures/figures.h"
extern Board* board;
class King : public Figures
{
    Q_OBJECT
public:
    King(int x, int y, bool isWhite);
    QVector<QPointF> getValidNeighbourPositions();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

};

#endif // KING_H
