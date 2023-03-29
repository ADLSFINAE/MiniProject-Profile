#include "figures.h"

Figures::Figures(int x, int y, bool isWhite)
{
    this->x = x;
    this->y = y;
    this->isWhite = isWhite;
    this->setPos(x * 80, y * 80);
    qDebug()<<"Figures was included";
}

QPoint Figures::getPosition() const
{
    return QPoint(x, y);
}

bool Figures::getColor()
{
    return isWhite;
}


