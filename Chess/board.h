#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "paramsNdefines.h"
using namespace GlobVal;

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board(QGraphicsScene *scene, QGraphicsRectItem* parent = nullptr);
    void inizialization(QGraphicsScene* scene);
    void buildingBlock(QBrush brush, int i, int j);
private:
    void initVectorOfBlocks();
    bool check4Color(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;
};

#endif // BOARD_H
