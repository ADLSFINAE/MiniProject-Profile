#include "figures/king.h"

King::King(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteKing));
    else
        this->setPixmap(QPixmap(pngBlackKing));
}

QVector<Block*> King::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if(checkOnOut(i, j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);
        }
    }

    return positions;
}

void King::getCEELO(QSet<Block*>CEELO)
{
    this->CEELO.clear();
    this->CEELO = CEELO;

    for(auto& elem : qAsConst(CEELO)){
        for(auto& fig : elem->getCollidingItemsForMousePressEvent()){
            Figure* figure = dynamic_cast<Figure*>(fig);
            if(figure != nullptr){

            }
        }
    }
}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
    for(auto& elem : qAsConst(CEELO)){
        qDebug()<<"CEELO WAS CALLED";
        if(elem->getAnotherBrushColor() == Qt::yellow)
            elem->setAnotherBrushColor(Qt::red);
    }
}

void King::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
    emit updateFiguresPositions(this);
}

void King::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

