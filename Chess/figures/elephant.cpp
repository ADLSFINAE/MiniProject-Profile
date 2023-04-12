#include "elephant.h"

Elephant::Elephant(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteElephant));
    else
        this->setPixmap(QPixmap(pngBlackElephant));
}

QVector<Block*> Elephant::getValidNeighbourPositions()
{

}

void Elephant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Elephant::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Elephant::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

