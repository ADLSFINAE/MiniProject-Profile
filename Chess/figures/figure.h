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
#include <QtMath>
#include <QVector>
#include <QList>
using namespace GlobVal;

class Figure : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent = nullptr);
    QRectF boundingRect()const override;

    //for set position
    void setPosition(int x, int y);
    QPoint getPosition() const;

    //get position for mouse events
    void setOldPosition(int start_x, int start_y);
    QPair<int, int> getOldPosition() const;

    //bool checkers
    bool checkOnOut(int rows, int cols) const;
    bool checkForStep(QVector<Block*> block_vector, QVector<Figure*> fig_vector);
    bool get_permission_to_move(Block* block);
    bool getColor();
    bool lastCheck(Block* block);

    //other logic
    QVector< QVector<Block*> > getBoard();
    void setBoard(QVector< QVector<Block*> > arrWithBoard);
    double calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
public:
    virtual QVector<Block*> getValidNeighbourPositions() = 0;
private:
    QVector< QVector<Block*> > arrWithBoard;
    bool isWhite;
    int x,y;
    int start_x, start_y;
};

#endif // FIGURE_H
