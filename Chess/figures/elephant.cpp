#include "elephant.h"
#include <QSet>

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

            if(getPosition().x() + i >= 0 && getPosition().y() - i >= 0
                    && getPosition().x() + i <= 7 && getPosition().y() - i <= 7)
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() - i]);

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

