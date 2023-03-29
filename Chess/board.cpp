#include "board.h"
#include "paramsNdefines.h"
using namespace bigDick;

Board::Board(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    this->setRect(0, 0, bigDick::GENX * bigDick::LONGOFMYPENISX, bigDick::GENY * bigDick::LONGOFMYPENISY);
}

void Board::inizialization(QGraphicsScene *scene)
{
    scene->addItem(this);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(check4Color(i, j))
                buildingBlock(Qt::gray, i, j, scene);
            else
                buildingBlock(Qt::black, i, j, scene);
        }
    }
}

void Board::buildingBlock(QBrush brush, int i, int j, QGraphicsScene* scene)
{
    blockArray[i][j] = new Block();
    scene->addItem(blockArray[i][j]);

    blockArray[i][j]->setRect(0, 0, bigDick::GENX, bigDick::GENY);
    blockArray[i][j]->setPos(i * bigDick::GENX, j * bigDick::GENY);
    blockArray[i][j]->setDefPen();
    blockArray[i][j]->changeColor(brush);
}



bool Board::check4Color(int rows, int cols) const
{
    if((rows + cols) % 2 == 0)
        return true;
    else
        return false;
}


