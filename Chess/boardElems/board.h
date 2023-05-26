#ifndef BOARD_H
#define BOARD_H
#include "boardElems/block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "paramsNdefines.h"
#include "game.h"
#include "figures/figure.h"
using namespace GlobVal;

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board() = default;
    Board(QGraphicsScene *scene, QGraphicsRectItem* parent = nullptr);
    QRectF boundingRect() const override;
    QVector< QVector<Block*> > getBoard();
    QGraphicsScene* pointer_to_scene = nullptr;
    QVector<Figure*> figures;
public slots:
    void remove_from_scene(Figure* figure);
private:
    void figuresPlacing(QGraphicsScene* scene, bool isWhite);
    void buildingBlock(QBrush brush, int rows, int cols);
    void inizialization(QGraphicsScene* scene);
    void initVectorOfBlocks();
    bool neededColorChecker(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;// to draw a board
    Game* game{nullptr};
};

#endif // BOARD_H
