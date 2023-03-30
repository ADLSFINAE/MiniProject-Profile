#include "board.h"

Board::Board(QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{

    arrOfBlocks.resize(bigDick::LONGOFMYPENISX);

    for (int i = 0; i < bigDick::LONGOFMYPENISY; ++i) {
        arrOfBlocks[i].resize(bigDick::LONGOFMYPENISY);
    }

    this->setRect(0, 0, bigDick::GENX * bigDick::LONGOFMYPENISX, bigDick::GENY * bigDick::LONGOFMYPENISY);
}

void Board::inizialization(QGraphicsScene *scene)
{
    scene->addItem(this);
    for(int i = 0; i < bigDick::LONGOFMYPENISX; i++){
        for(int j = 0; j < bigDick::LONGOFMYPENISY; j++){
            if(check4Color(i, j))
                buildingBlock(Qt::gray, i, j, scene);
            else
                buildingBlock(Qt::black, i, j, scene);
        }
    }
}

void Board::buildingBlock(QBrush brush, int i, int j, QGraphicsScene* scene)
{
    arrOfBlocks[i][j] = new Block();
    scene->addItem(arrOfBlocks[i][j]);

    arrOfBlocks[i][j]->setRect(0, 0, bigDick::GENX, bigDick::GENY);
    arrOfBlocks[i][j]->setPos(i * bigDick::GENX, j * bigDick::GENY);
    arrOfBlocks[i][j]->setDefPen();
    arrOfBlocks[i][j]->changeColor(brush);
}



bool Board::check4Color(int rows, int cols) const
{
    if((rows + cols) % 2 == 0)
        return true;
    else
        return false;
}


