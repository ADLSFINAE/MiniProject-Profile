#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsScene>
#include "boardElems/board.h"
#include "paramsNdefines.h"
using namespace GlobVal;

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene(QGraphicsScene* scene = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
private:
    Board* board{nullptr};
};

#endif // CUSTOMSCENE_H
