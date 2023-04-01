#include "figures/figures.h"

Figures::Figures(int x, int y, bool isWhite, QGraphicsPixmapItem* parent)
    :QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->setPos(x * GlobX, y * GlobY);
    qDebug()<<"Figures was included";
}

void Figures::setPosition(int x, int y)
{
    this->setPos(x * GlobX, y * GlobY);
}

QPoint Figures::getPosition() const
{
    return QPoint(x, y);
}


