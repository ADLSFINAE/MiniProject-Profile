#include "boardElems/block.h"

void Block::changeColor(QBrush brush)
{
    this->setBrush(brush);
}

void Block::setDefPen()
{
    this->setPen(Qt::NoPen);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
    qDebug()<<"Block was clicked";
}

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, GlobX, GlobY);
}



