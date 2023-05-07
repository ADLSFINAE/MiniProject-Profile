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
            if((this->getPosition().y() - i >= 0) && (this->getPosition().y() - i <= 7)){
                positions.push_back(getBoard()[getPosition().x()][getPosition().y() - i]);
                if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7))
                    positions.push_back(getBoard()[getPosition().x() - 1][getPosition().y() - 1]);
                if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7))
                    positions.push_back(getBoard()[getPosition().x() + 1][getPosition().y() - 1]);
            }
        }
        else{
            if((this->getPosition().y() + i >= 0) && (this->getPosition().y() + i <= 7)){
                positions.push_back(getBoard()[getPosition().x()][getPosition().y() + i]);
                if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7))
                    positions.push_back(getBoard()[getPosition().x() - 1][getPosition().y() + 1]);
                if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7))
                    positions.push_back(getBoard()[getPosition().x() + 1][getPosition().y() + 1]);
            }
        }
    }


    return positions;
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mousePressEvent(event);
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

