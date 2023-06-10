#include "coreElems/customview.h"
#include <QApplication>
#include <QDesktopWidget>
#include "boardElems/board.h"
#include "coreElems/customscene.h"
#include "boardElems/board.h"
#include "qscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomScene* scene = new CustomScene();
    CustomView* view = new CustomView(scene);
    view->show();
    QPoint globalCursorPos = QCursor::pos();
    qDebug()<<qApp->desktop();
    qDebug()<<qApp->screenAt(globalCursorPos)->geometry()<<"QAPPPPP";
    int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);
    QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
    QPoint localCursorPos = globalCursorPos - mouseScreenGeometry.topLeft();
    qDebug()<<localCursorPos;
    QList<QScreen*>blya = qApp->screens();
    for(auto& elem : blya){
        qDebug()<<elem->geometry();
    }
    qDebug()<<qApp->screens().size();
    return a.exec();
}
