#include "customview.h"

CustomView::CustomView(QGraphicsScene* scene)
{
    this->setScene(scene);
    this->setFixedSize(648, 648);
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
