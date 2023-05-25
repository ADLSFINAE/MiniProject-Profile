#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPen>
#include <QBrush>
#include "paramsNdefines.h"
using namespace GlobVal;

class Block : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Block() = default;
    QRectF boundingRect() const override;
    void changeColor(QBrush brush);
    void setDefPen();
    void setBlockPos(int x, int y);
    void setDefColor();
    bool check_another_brush_color_on_def_color() const;
    QBrush getAnotherBrushColor() const;
    QPoint getBlockPos() const;
    QBrush getDefColor() const;
    bool colorWasChanged = false;

    QVector<QGraphicsItem*> getCollidingItemsForMousePressEvent();
    QVector<QGraphicsItem*> getCollidingItemsForMouseReleaseEvent(QGraphicsItem* figure);
    void setAnotherBrushColor(QBrush anotherBrush);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
    QBrush brush;
    QBrush anotherBrush;
    int x, y;
};

#endif // BLOCK_H
