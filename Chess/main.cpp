#include "customview.h"
#include <QApplication>
#include "board.h"
#include "customscene.h"
#include "board.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomScene* scene = new CustomScene();
    qDebug()<<"Scene size is:"<<scene->width()<<scene->height();
    CustomView* view = new CustomView(scene);
    qDebug()<<"View size is:"<<view->width()<<view->height();
    view->show();
    return a.exec();
}
