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
#include <QSet>
using namespace GlobVal;

class Figure : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent = nullptr);
    QRectF boundingRect()const override;

    void set_def_color_for_all_board();
    bool check_on_valid_block(Block* block);
    void kill_functionality(Block* block);

    //step length limiter logic
    QVector<Block*> sort_min_to_max_x(QVector<Block*> vec_for_sort);
    QVector<Block*> sort_min_to_max_y(QVector<Block*> vec_for_sort);
    QVector<Block*> reverse_vector(QVector<Block *> vec_for_reverse);
    void step_length_limiter(QVector<Block*>& vec_block);

    //cleaning for 300$ bucks
    QVector<Block*> clean_up(QVector<Block*> vec);

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

    //проверка на возможность хода и его реализация
    QPair<Block*, double> find_min_dist_for_blocks(QVector<QPair<Block*, double>> vec);
    void find_valid_positions(QVector<QPair<Block*, double>> block_vec);

    //other logic
    QVector< QVector<Block*> > getBoard();
    void setBoard(QVector< QVector<Block*> > arrWithBoard);
    double calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y);
signals:
    void vahue(Figure* figure);
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
