#ifndef BOARD_H
#define BOARD_H
#include "boardElems/block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "paramsNdefines.h"
using namespace GlobVal;

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board() = default;
    Board(QGraphicsScene *scene, QGraphicsRectItem* parent = nullptr);
    QRectF boundingRect() const override;
private:
    void buildingBlock(QBrush brush, int rows, int cols);
    void inizialization(QGraphicsScene* scene);
    void initVectorOfBlocks();
    bool neededColorChecker(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;
};

#endif // BOARD_H
