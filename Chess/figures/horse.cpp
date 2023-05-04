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
    QVector<Block*> flashback;
    QVector<Block*> last;

    for (int i = -2; i <= 2; i++){
        for (int j = -2; j <= 2; j++){
            if(checkOnOut(i, j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);
        }
    }

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if(checkOnOut(i, j))
                flashback.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);
        }
    }

    for(int i = 0; i < positions.size(); i++){
        for(int j = 0; j < flashback.size(); j++){
            if(positions[i] == flashback[j]){
                positions.remove(i);
            }
        }
    }

    for(int i = 0; i < positions.size(); i++){
        if(getBoard()[getPosition().x()][getPosition().y()]->getDefColor() == QColor(Qt::gray)){
            if(positions[i]->getDefColor() == QColor(Qt::gray))
                positions.remove(i);
        }
        else{
            if(positions[i]->getDefColor() == Qt::black)
                positions.remove(i);
        }

        //qDebug()<<positions[i]->getDefColor() << positions[i]->pos().y() / 80;
    }




    return positions;
}

void Horse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(Qt::yellow);
    }
}

void Horse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->getOldPosition().first, this->getOldPosition().second);
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(block->getDefColor());
    }
}

void Horse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->pos();
    this->setPos(mapToScene(event->pos()));
}
