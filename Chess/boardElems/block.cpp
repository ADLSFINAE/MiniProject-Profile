#include "boardElems/block.h"
#include <QColor>
void Block::changeColor(QBrush brush)
{
    this->setBrush(brush);
    this->brush = brush;
}

void Block::setDefPen()
{
    this->setPen(Qt::NoPen);
}

void Block::setBlockPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

QPoint Block::getBlockPos() const
{
    return QPoint(x, y);
}

QBrush Block::getDefColor() const
{
    return brush;
}


void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
}

QRectF Block::boundingRect() const
{
    return blockSizeRect;
}



