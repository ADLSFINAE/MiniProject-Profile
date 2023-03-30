#include "board.h"

Board::Board(QGraphicsScene *scene ,QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    //initialization of my array, it's not seems like in pure c++, but it's QVector
    // and i used resize method for it
    this->initVectorOfBlocks();
    this->setRect(0, 0, GlobVal::GlobX * GlobVal::LongByX, GlobVal::GlobY * GlobVal::LongByY);
    this->inizialization(scene);
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
    for(int i = 0; i < GlobVal::LongByX; i++){
        for(int j = 0; j < GlobVal::LongByY; j++){
            if(check4Color(i, j))
                buildingBlock(Qt::gray, i, j);
            else
                buildingBlock(Qt::black, i, j);
        }
    }
}

void Board::buildingBlock(QBrush brush, int i, int j)
{
    arrOfBlocks[i][j] = new Block();
    arrOfBlocks[i][j]->setParentItem(this);

    arrOfBlocks[i][j]->setRect(0, 0, GlobVal::GlobX, GlobVal::GlobY);
    arrOfBlocks[i][j]->setPos(i * GlobVal::GlobX, j * GlobVal::GlobY);
    arrOfBlocks[i][j]->setDefPen();
    arrOfBlocks[i][j]->changeColor(brush);
}

void Board::initVectorOfBlocks()
{
    arrOfBlocks.resize(GlobVal::LongByX);

    for (int i = 0; i < GlobVal::LongByY; i++) {
        arrOfBlocks[i].resize(GlobVal::LongByY);
    }
}

bool Board::check4Color(int rows, int cols) const
{
    if((rows + cols) % 2 == 0)
        return true;
    else
        return false;
}


