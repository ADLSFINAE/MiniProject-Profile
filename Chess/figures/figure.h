#ifndef FIGURE_H
#define FIGURE_H

#include "boardElems/block.h"
#include "paramsNdefines.h"

#include <QDebug>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPair>
#include <QList>
using namespace GlobVal;

class Figure : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent = nullptr);
    QRectF boundingRect()const override;
public:
    //for set position
    void setPosition(int x, int y);
    QPoint getPosition() const;

    //get position for mouse events
    void setOldPosition(int start_x, int start_y);
    QPair<int, int> getOldPosition() const;
    bool checkOnOut(int rows, int cols) const;

    bool getColor();
    QVector< QVector<Block*> > getBoard();
    void setBoard(QVector< QVector<Block*> > arrWithBoard);
public:
    virtual QVector<Block*> getValidNeighbourPositions() = 0;

private:
    QVector< QVector<Block*> > arrWithBoard;
    bool isWhite;
    int x,y;
    int start_x, start_y;
};

#endif // FIGURE_H
