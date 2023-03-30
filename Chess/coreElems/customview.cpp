#include "coreElems/customview.h"

CustomView::CustomView(QGraphicsScene* scene, QGraphicsView* view)
    :QGraphicsView(view)
{
    this->setScene(scene);
    this->setFixedSize(scene->height() + LongByX, scene->width() + LongByY);
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
