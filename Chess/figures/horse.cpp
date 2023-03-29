#include "horse.h"

Horse::Horse(int x, int y, bool isWhite) : Figures(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(":/chesscom/wN.png"));
    else
        this->setPixmap(QPixmap(":/chesscom/bN.png"));
}

QVector<QPointF> Horse::getValidNeighbourPositions()
{

}

void Horse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Horse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
