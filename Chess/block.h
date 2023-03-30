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
    void changeColor(QBrush brush);
    void setDefPen();
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // BLOCK_H
