#include "figures/horse.h"

Horse::Horse(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteHorse));
    else
        this->setPixmap(QPixmap(pngBlackHorse));
}

QVector<QPointF> Horse::getValidNeighbourPositions()
{

}

void Horse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Horse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Horse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
