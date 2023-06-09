#ifndef PAWN_H
#define PAWN_H
#include "figures/figure.h"

class Pawn : public Figure
{
    Q_OBJECT
public:
    Pawn(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
    bool checkOnOutForPawn(int i);
    bool leave_from_start_position();
    void step_length_limiter_for_pawn(QVector<Block *> vec_block);
    QVector<Block *> getKnowledge();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
signals:
    void createChangePawnWidget(bool color, int posX, int posY);
private:
    void forward_step(QVector<Block*>& positions, int offset);
    int start_pos_x, start_pos_y;
    bool isMovedFromStart;
};

#endif // PAWN_H
