#include "figures/figure.h"

Figure::Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent)
    :QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->isWhite = isWhite;
    this->setPos(x * GlobX, y * GlobY);
    qDebug()<<"Figures was included";

    arrWithBoard.resize(LongByX);

    for (int i = 0; i < LongByY; i++) {
        arrWithBoard[i].resize(LongByY);
    }
}

void Figure::setPosition(int x, int y)
{
    this->setPos(x * GlobX, y * GlobY);
}

QPoint Figure::getPosition() const
{
    return QPoint(x, y);
}

void Figure::sayHi()
{
    qDebug()<<"Hi";
}

void Figure::setBoard(QVector< QVector<Block*> > arrWithBoard)
{
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            this->arrWithBoard[i][j] = arrWithBoard[i][j];
        }
    }
}


