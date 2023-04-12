#include "figures/figure.h"
#include <QPainter>
Figure::Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent)
    :QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->isWhite = isWhite;
    this->setPos(x * GlobX, y * GlobY);
    this->sceneBoundingRect();
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

void Figure::setOldPosition(int start_x, int start_y)
{
    this->start_x = start_x;
    this->start_y = start_y;
}


QPair<int, int> Figure::getOldPosition() const
{
    QPair<int, int> oldPos;
    oldPos.first = this->start_x;
    oldPos.second = this->start_y;
    return oldPos;
}

bool Figure::checkOnOut(int rows, int cols) const
{
    qDebug()<<getPosition().x()<<getPosition().y();
    int&& sum_x = (this->getPosition().x() + rows);
    int&& sum_y = (this->getPosition().y() + cols);
    if(((this->getPosition().x() + rows) == getPosition().x())
                &&((this->getPosition().y() + cols) == getPosition().y()))
            return false;

    else if(((this->getPosition().x() + rows) >= 0) && ((this->getPosition().x() + rows) <= 7)
            && ((this->getPosition().y() + cols) >= 0) && ((this->getPosition().y() + cols) <= 7))
            return true;
    else
        return false;
}

QVector<QVector<Block *> > Figure::getBoard()
{
    return arrWithBoard;
}

QRectF Figure::boundingRect() const
{
    return figureSizeRect;
}

QPoint Figure::getPosition() const
{
    return QPoint(x, y);
}

void Figure::setBoard(QVector< QVector<Block*> > arrWithBoard)
{
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            this->arrWithBoard[i][j] = arrWithBoard[i][j];
        }
    }
}


