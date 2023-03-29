#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>

class CustomView : public QGraphicsView
{
public:
    CustomView(QGraphicsScene* scene);
    void mousePressEvent(QMouseEvent* event);
};

#endif // CUSTOMVIEW_H
