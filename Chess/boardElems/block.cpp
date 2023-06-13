
#include "boardElems/block.h"
#include <QColor>
void Block::changeColor(QBrush brush)
{
    this->setBrush(brush);
    this->brush = brush;
}

void Block::setDefPen()
{
    this->setPen(Qt::SolidLine);
}

void Block::setBlockPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Block::setDefColor()
{
    this->setAnotherBrushColor(getDefColor());
}

bool Block::check_another_brush_color_on_def_color() const
{
    if(getAnotherBrushColor() == getDefColor()){
        return false;
    }
    else{
        return true;
    }

}

QPoint Block::getBlockPos() const
{
    return QPoint(x, y);
}

QBrush Block::getDefColor() const
{
    return brush;
}

QVector<QGraphicsItem *> Block::getCollidingItemsForMousePressEvent()
{
    QList<QGraphicsItem*> list = this->collidingItems();
    QVector<QGraphicsItem*> vec;
    for(auto& elem : list){
            vec.push_back(elem);
    }
    return vec;
}

QVector<QGraphicsItem *> Block::getCollidingItemsForMouseReleaseEvent(QGraphicsItem *figure)
{
    QList<QGraphicsItem*> list = this->collidingItems();
    QVector<QGraphicsItem*> vec;
    for(auto& elem : list){
        if(elem != figure)
            vec.push_back(elem);
    }
    return vec;
}

void Block::setAnotherBrushColor(QBrush anotherBrush)
{
    this->anotherBrush = anotherBrush;
    this->setBrush(anotherBrush);
}

QBrush Block::getAnotherBrushColor() const
{
    return anotherBrush;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
}

QRectF Block::boundingRect() const
{
    return blockSizeRect;
}



