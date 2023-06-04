#include "figures/rook.h"

Rook::Rook(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteRook));
    else
        this->setPixmap(QPixmap(pngBlackRook));
}

QVector<Block*> Rook::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    for (int i = -8; i <= 8; i++){
        for (int j = -8; j <= 8; j++){
            if(checkOnOut(i, j)){
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y()]);
                positions.push_back(getBoard()[getPosition().x()][getPosition().y() + j]);
            }
        }
    }

    return positions;
}

void Rook::getKnowledge(QVector<Block *> vec_block)
{

}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mousePressEvent(event);
}

void Rook::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
}

void Rook::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

