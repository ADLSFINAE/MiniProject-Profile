#include "customview.h"
#include <QApplication>
#include "board.h"
#include "customscene.h"
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomScene* scene = new CustomScene;
    Board* board = new Board;
    board->inizialization(scene);

    CustomView* view = new CustomView(scene);
    view->show();
    return a.exec();
}