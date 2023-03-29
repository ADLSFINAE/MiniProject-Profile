#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene(QGraphicsScene* scene = nullptr);
};

#endif // CUSTOMSCENE_H
