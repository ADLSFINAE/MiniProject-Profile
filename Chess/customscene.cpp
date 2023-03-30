#include "customscene.h"

CustomScene::CustomScene(QGraphicsScene *scene)
    :QGraphicsScene(scene)
{
    this->setSceneRect(0, 0, 640, 640);
    board = new Board(this);
}
