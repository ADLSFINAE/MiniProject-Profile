#include "boardElems/board.h"
#include "figures/figure.h"

#include "figures/king.h"
#include "figures/horse.h"
#include "figures/queen.h"
#include "figures/elephant.h"
#include "figures/pawn.h"
#include "figures/rook.h"

Board::Board(QGraphicsScene *scene ,QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    //initialization of my array, it's not seems like in pure c++, but it's QVector
    // and i used resize method for it
    this->initVectorOfBlocks();
    this->inizialization(scene);
    game = new Game();
    this->figuresPlacing(scene, true);
    this->figuresPlacing(scene, false);
}

QRectF Board::boundingRect() const
{
    return boardSizeRect;
}

QVector<QVector<Block *> > Board::getBoard()
{
    return arrOfBlocks;
}

void Board::figuresPlacing(QGraphicsScene* scene, bool isWhite)
{
    int cols, pawnCols;
    isWhite ? ({cols = 7; pawnCols = 6;}) : ({cols = 0; pawnCols = 1;});

    QVector<Figure*> figures = {
        new King(4, cols, isWhite),
        new Queen(3, cols, isWhite),
        new Horse(1, cols, isWhite),
        new Horse(6, cols, isWhite),
        new Elephant(2, cols, isWhite),
        new Elephant(5, cols, isWhite),
        new Rook(0, cols, isWhite),
        new Rook(7, cols, isWhite),
    };

    for(int rows = 0; rows < LongByX; rows++)
        figures.push_back(new Pawn(rows, pawnCols, isWhite));

    for (const auto& figure : figures) {
        scene->addItem(figure);
        game->initOfVecs(figure, isWhite);
        figure->setBoard(arrOfBlocks);
    }

    qDebug()<<game->vecOfWhiteFigures.size()<<"DSADASDASDAS";
    qDebug()<<game->vecOfBlackFigures.size()<<"DSADASDASDAS";
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

