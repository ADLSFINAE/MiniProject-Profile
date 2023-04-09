#ifndef BOARD_H
#define BOARD_H
#include "boardElems/block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "paramsNdefines.h"
#include "game.h"
using namespace GlobVal;

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board() = default;
    Board(QGraphicsScene *scene, QGraphicsRectItem* parent = nullptr);
    QRectF boundingRect() const override;
    QVector< QVector<Block*> > getBoard();
private:
    void figuresPlacing(QGraphicsScene* scene, bool isWhite);
    void buildingBlock(QBrush brush, int rows, int cols);
    void inizialization(QGraphicsScene* scene);
    void initVectorOfBlocks();
    bool neededColorChecker(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;// to draw a board
    Game* game{nullptr};
};

#endif // BOARD_H
