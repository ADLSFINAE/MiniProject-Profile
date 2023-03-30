#include "coreElems/customview.h"
#include <QApplication>
#include "boardElems/board.h"
#include "coreElems/customscene.h"
#include "boardElems/board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomScene* scene = new CustomScene();
    CustomView* view = new CustomView(scene);
    view->show();
    return a.exec();
}
