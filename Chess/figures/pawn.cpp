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
    QVector<Block*> positions;
    for(int i = 1; i < 3; i++){
        if(getColor()){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() - i]);
        }
        else{
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() + i]);
        }
    }

    return positions;
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(Qt::yellow);
    }
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->getOldPosition().first, this->getOldPosition().second);
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(block->getDefColor());
    }
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->pos();
    this->setPos(mapToScene(event->pos()));
}
