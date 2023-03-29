#ifndef FIGURES_H
#define FIGURES_H

#include "block.h"
#include <QDebug>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Figures : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Figures(int x, int y, bool isWhite);
    QPoint getPosition() const;
    bool getColor();
    virtual QVector<QPointF> getValidNeighbourPositions() = 0;
private:
    bool isWhite;
    int x;
    int y;
};

#endif // FIGURES_H
