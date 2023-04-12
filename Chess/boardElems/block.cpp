#include "boardElems/block.h"

void Block::changeColor(QBrush brush)
{
    this->setBrush(brush);
    this->brush = brush;
}

void Block::setDefPen()
{
    this->setPen(Qt::NoPen);
}

QBrush Block::getDefColor()
{
    return brush;
}


void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
    qDebug()<<"Block was clicked"<<x() / 80<<y()/80;
}

QRectF Block::boundingRect() const
{
    return blockSizeRect;
}



