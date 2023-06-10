#include "coreElems/customscene.h"
#include <QDebug>
CustomScene::CustomScene(QGraphicsScene *scene)
    :QGraphicsScene(scene)
{
    this->setSceneRect(sceneSizeRect);
    board = new Board(this);
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(board->fig != nullptr){
        qDebug()<<board->fig->getColor();
    }
    QGraphicsScene::mousePressEvent(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}
