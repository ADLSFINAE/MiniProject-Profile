#include "figures/queen.h"

Queen::Queen(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteQueen));
    else
        this->setPixmap(QPixmap(pngBlackQueen));
}

QVector<Block*> Queen::getValidNeighbourPositions()
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

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if(checkOnOut(i, j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);
        }
    }

    for (int i = -8; i < 8; i++){
        for (int j = -8; j < 8; j++){
            if(checkOnOut(i, j) && (i == j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);

            int xs = getPosition().x() + i;
            int ys = getPosition().y() - i;
            if(xs >= 0 && ys >= 0 && xs <= 7 && ys <= 7){
                positions.push_back(getBoard()[xs][ys]);
            }

        }
    }

    return positions;
}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(Qt::yellow);
    }
}

void Queen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->getOldPosition().first, this->getOldPosition().second);
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(block->getDefColor());
    }
}

void Queen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->pos();
    this->setPos(mapToScene(event->pos()));
}
