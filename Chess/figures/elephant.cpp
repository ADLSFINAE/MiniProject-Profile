#include "elephant.h"

Elephant::Elephant(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteElephant));
    else
        this->setPixmap(QPixmap(pngBlackElephant));
}

QVector<Block*> Elephant::getValidNeighbourPositions()
{
    QVector<Block*> positions;
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

void Elephant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mousePressEvent(event);
}

void Elephant::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
}

void Elephant::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

