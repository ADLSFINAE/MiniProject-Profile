#include "coreElems/customscene.h"
#include "figures/king.cpp"
CustomScene::CustomScene(QGraphicsScene *scene)
    :QGraphicsScene(scene)
{
    this->setSceneRect(0, 0, GlobX * LongByX, GlobY * LongByY);
    board = new Board(this);
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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
