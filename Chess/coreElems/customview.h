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

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // CUSTOMVIEW_H
