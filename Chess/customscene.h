#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsScene>
#include "board.h"

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene(QGraphicsScene* scene = nullptr);
private:
    Board* board{nullptr};
};

#endif // CUSTOMSCENE_H
