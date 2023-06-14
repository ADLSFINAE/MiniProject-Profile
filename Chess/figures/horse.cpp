#include "figures/horse.h"
#include <QSet>

Horse::Horse(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteHorse));
    else
        this->setPixmap(QPixmap(pngBlackHorse));
}

QVector<Block*> Horse::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    QVector<QPair<int, int> > bloody;
    bloody.push_back({getPosition().x() + 1, getPosition().y() + 2});
    bloody.push_back({getPosition().x() + 1, getPosition().y() + 2});
    bloody.push_back({getPosition().x() + 2, getPosition().y() + 1});
    bloody.push_back({getPosition().x() + 2, getPosition().y() - 1});
    bloody.push_back({getPosition().x() + 1, getPosition().y() - 2});
    bloody.push_back({getPosition().x() - 1, getPosition().y() - 2});
    bloody.push_back({getPosition().x() - 2, getPosition().y() - 1});
    bloody.push_back({getPosition().x() - 2, getPosition().y() + 1});
    bloody.push_back({getPosition().x() - 1, getPosition().y() + 2});

    for(auto& elem : bloody){
        if(elem.first >= 0 && elem.first <= 7 && elem.second >= 0 && elem.second <= 7){
            positions.push_back(getBoard()[elem.first][elem.second]);
        }
    }
    vecFromGetKnowledge = positions;
    return positions;
}

void Horse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
}

void Horse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
    emit updateFiguresPositions(this);
}

void Horse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

