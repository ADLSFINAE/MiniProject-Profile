#include "figures/pawn.h"

Pawn::Pawn(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhitePawn));
    else
        this->setPixmap(QPixmap(pngBlackPawn));
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{

}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
