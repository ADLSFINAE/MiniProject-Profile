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

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void changeColor(QBrush brush);
    void setDefPen();
    void setBlockPos(int x, int y);
    QPoint getBlockPos() const;
    QBrush getDefColor() const;
    bool colorWasChanged = false;
private:
    QBrush brush;
    int x, y;
};

#endif // BLOCK_H
