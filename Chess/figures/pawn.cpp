#include "figures/pawn.h"

Pawn::Pawn(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhitePawn));
    else
        this->setPixmap(QPixmap(pngBlackPawn));
    start_pos_x = x;
    start_pos_y = y;
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    if(!leave_from_start_position()){
        for(int i = 1; i < 3; i++)
            forward_step(positions, i);
    }
    else{
        for(int i = 1; i < 2; i++)
            forward_step(positions, i);
    }
    return positions;
}

bool Pawn::leave_from_start_position()
{
    if(start_pos_x != this->getPosition().x() || start_pos_y != this->getPosition().y())
        return true;
    else
        return false;
}

void Pawn::step_length_limiter_for_pawn(QVector<Block *> vec_block)
{
    for(int i = 0; i < vec_block.size(); i++){
        if(vec_block[i]->getAnotherBrushColor() == Qt::green
                || vec_block[i]->getAnotherBrushColor() == Qt::blue){
            for(int j = i; j < vec_block.size(); j++){
                vec_block[j]->setAnotherBrushColor(vec_block[j]->getDefColor());
            }
            break;
        }
    }
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mousePressEvent(event);

    step_length_limiter_for_pawn(getValidNeighbourPositions());
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

void Pawn::forward_step(QVector<Block*>& positions, int offset)
{
    if(this->getColor()){
        if((this->getPosition().y() - offset >= 0) && (this->getPosition().y() - offset <= 7)){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() - offset]);
        }
    }
    else{
        if((this->getPosition().y() + offset >= 0) && (this->getPosition().y() + offset <= 7)){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() + offset]);
        }
    }
}

