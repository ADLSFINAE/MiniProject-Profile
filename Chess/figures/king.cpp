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
    vecFromGetKnowledge = positions;
    return positions;
}

void King::getCEELO(QSet<Block*>CEELO)
{
    this->CEELO.clear();
    this->CEELO = CEELO;
    qDebug()<<"CEELO SIZE IN GET"<<CEELO.size();

    //ОТСЮДА НУЖНО БУДЕТ СДЕЛАТЬ СИГНАЛ И СВЕРКУ ПОЗИЦИЙ КАК РАЗ ТАКИ ПО ЦВЕТАМ, ЧТОБЫ ЗАБЛОЧИТЬ ЗАСКОК ЗА КОРОЛЯ
    //ЛИБО CEELO ПРИДЕТСЯ ВОЗВРАЩАТЬ ИЗ GAME
    //ИЗ КЛАССА GAME
}

void King::getFiguresVec(QVector<Figure *> fig)
{
    this->figVec.clear();
    this->figVec = fig;
    qDebug()<<"figVec SIZE IN GET"<<figVec.size();
}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
    for(auto& elem : qAsConst(CEELO)){
        qDebug()<<"CEELO WAS CALLED"<<CEELO.size();
        if(elem->getAnotherBrushColor() == Qt::yellow){
            elem->setAnotherBrushColor(Qt::red);
        }
        if(elem->getBlockPos() == this->getPosition()){
            elem->setAnotherBrushColor(Qt::red);
        }
    }

    for(auto& elem : this->figVec){
        elem->blockForCheckOnDefense();
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

