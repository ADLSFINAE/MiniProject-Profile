#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "paramsNdefines.h"
using namespace GlobVal;

class CustomView : public QGraphicsView
{
public:
    CustomView(QGraphicsScene* scene, QGraphicsView* view = nullptr);
    void mousePressEvent(QMouseEvent* event);
};

#endif // CUSTOMVIEW_H
