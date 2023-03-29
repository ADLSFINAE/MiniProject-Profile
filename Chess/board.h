#ifndef BOARD_H
#define BOARD_H
#include "block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board(QGraphicsRectItem* parent = nullptr);
    void inizialization(QGraphicsScene* scene);
    void buildingBlock(QBrush brush, int i, int j, QGraphicsScene* scene);
private:
    bool check4Color(int rows, int cols) const;

    Block* blockArray[8][8];
};

#endif // BOARD_H
