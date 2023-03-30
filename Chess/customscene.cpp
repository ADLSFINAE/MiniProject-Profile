#include "customscene.h"

CustomScene::CustomScene(QGraphicsScene *scene)
    :QGraphicsScene(scene)
{
    this->setSceneRect(0, 0, GlobX * LongByX, GlobY * LongByY);
    board = new Board(this);
    qDebug()<<"Board size is:"<<board->x()<<board->y();
}
