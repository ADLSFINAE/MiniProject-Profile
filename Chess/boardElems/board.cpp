#include "boardElems/board.h"
#include "figures/king.h"

Board::Board(QGraphicsScene *scene ,QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    //initialization of my array, it's not seems like in pure c++, but it's QVector
    // and i used resize method for it
    this->initVectorOfBlocks();
    this->inizialization(scene);

}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, GlobX * LongByX, GlobY * LongByY);
}

QVector<QVector<Block *> > Board::getBoard()
{
    return arrOfBlocks;
}

void Board::inizialization(QGraphicsScene *scene)
{
    scene->addItem(this);
    /*
    * Lets talk about how it gonna working: *
    * 1) we adding Board like a ITEM to scene; *
    * 2) in buildingBlock() function we set what our blocks have parent and it our BOARD; *
    * 3) cause we addItem() -> board, all items what have parent board adding with him like they are blocks; *
    */
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            if(neededColorChecker(i, j))
                buildingBlock(Qt::gray, i, j);
            else
                buildingBlock(Qt::black, i, j);
        }
    }

    King* king = new King(5,5, true);
    //king.setParent(board);
    king->setZValue(1000);
    king->setVisible(true);
    king->setBoard(this->getBoard());
    scene->addItem(king);
    king->setPixmap(QPixmap(":/whiteFigures/chesscom/whiteFigures/wK.png"));

}

void Board::buildingBlock(QBrush brush, int rows, int cols)
{
    arrOfBlocks[rows][cols] = new Block();
    arrOfBlocks[rows][cols]->setParentItem(this);

    arrOfBlocks[rows][cols]->setRect(0, 0, GlobX, GlobY);
    arrOfBlocks[rows][cols]->setPos(rows * GlobX, cols * GlobY);
    arrOfBlocks[rows][cols]->setDefPen();
    arrOfBlocks[rows][cols]->changeColor(brush);
}

void Board::initVectorOfBlocks()
{
    arrOfBlocks.resize(LongByX);

    for (int i = 0; i < LongByY; i++) {
        arrOfBlocks[i].resize(LongByY);
    }
}


bool Board::neededColorChecker(int rows, int cols) const
{
    if((rows + cols) % 2 == 0)
        return true;
    else
        return false;
}


