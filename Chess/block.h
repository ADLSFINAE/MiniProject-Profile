#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPen>
#include <QBrush>

class Block : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Block();
    void changeColor(QBrush brush);
    void setDefPen();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
    QRectF boundingRect() const override;
};

#endif // BLOCK_H
