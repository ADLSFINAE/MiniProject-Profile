#include "coreElems/customview.h"
#include <QApplication>
#include "boardElems/board.h"
#include "coreElems/customscene.h"
#include "boardElems/board.h"
#include "coreElems/changepawnwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomScene* scene = new CustomScene();
    CustomView* view = new CustomView(scene);
    ChangePawnWidget* changePawnWidget = new ChangePawnWidget(true);
    changePawnWidget->show();
    ChangePawnWidget* changePawnWidget1 = new ChangePawnWidget(false);
    changePawnWidget1->show();
    view->show();
    return a.exec();
}
