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

    void set_def_color_for_all_board();
    bool check_on_valid_block(Block* block);
    bool working_with_colliding_vec_from_block(Block* block);

    //for set position
    void setPosition(int x, int y);
    QPoint getPosition() const;

    //get position for mouse events
    void setOldPosition(int start_x, int start_y);
    QPair<int, int> getOldPosition() const;

    //bool checkers
    bool checkOnOut(int rows, int cols) const;
    bool checkForStep(QVector<Block*> block_vector, QVector<Figure*> fig_vector);
    bool getColor();

    QPair<Figure*, double> find_min_dist_for_figures(QVector<QPair<Figure*, double>> vec);
    QPair<Block*, double> find_min_dist_for_blocks(QVector<QPair<Block*, double>> vec);

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
