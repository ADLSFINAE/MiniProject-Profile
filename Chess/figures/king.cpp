#include "figures/king.h"


King::King(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteKing));
    else
        this->setPixmap(QPixmap(pngBlackKing));
}

QVector<QPointF> King::getValidNeighbourPositions()
{

}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    arrWithBoard[1][1]->setBrush(Qt::green);
}

void King::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void King::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

