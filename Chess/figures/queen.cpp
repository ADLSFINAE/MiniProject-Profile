#include "queen.h"

Queen::Queen(int x, int y, bool isWhite) : Figures(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(":/chesscom/wQ.png"));
    else
        this->setPixmap(QPixmap(":/chesscom/bQ.png"));
}

QVector<QPointF> Queen::getValidNeighbourPositions()
{

}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Queen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
