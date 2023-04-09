#include "figures/rook.h"

Rook::Rook(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteRook));
    else
        this->setPixmap(QPixmap(pngBlackRook));
}

QVector<QPointF> Rook::getValidNeighbourPositions()
{

}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Rook::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Rook::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
