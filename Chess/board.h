#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "paramsNdefines.h"
using namespace bigDick;

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board(QGraphicsRectItem* parent = nullptr);
    void inizialization(QGraphicsScene* scene);
    void buildingBlock(QBrush brush, int i, int j, QGraphicsScene* scene);
private:
    bool check4Color(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;
};

#endif // BOARD_H
