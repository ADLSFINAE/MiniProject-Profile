#include "block.h"

void Block::changeColor(QBrush brush)
{
    this->setBrush(brush);
}

void Block::setDefPen()
{
    QPen pen;
    pen.setWidth(0);
    this->setPen(pen);
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



