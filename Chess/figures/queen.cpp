#include "figures/queen.h"

Queen::Queen(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteQueen));
    else
        this->setPixmap(QPixmap(pngBlackQueen));
}

QVector<Block*> Queen::getValidNeighbourPositions()
{

}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Queen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Queen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
