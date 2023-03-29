#include "rook.h"

Rook::Rook(int x, int y, bool isWhite) : Figures(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(":/chesscom/wR.png"));
    else
        this->setPixmap(QPixmap(":/chesscom/bR.png"));
}

QVector<QPointF> Rook::getValidNeighbourPositions()
{

}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Rook::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
