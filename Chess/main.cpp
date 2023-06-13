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
    return a.exec();
}
