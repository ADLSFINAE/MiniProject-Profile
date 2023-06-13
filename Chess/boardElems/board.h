#ifndef BOARD_H
#define BOARD_H
#include "boardElems/block.h"
#include "coreElems/ChangePawnElems/changepawnwidget.h"
#include "paramsNdefines.h"
#include "game.h"
#include "figures/figure.h"
#include "figures/king.h"
#include "figures/horse.h"
#include "figures/queen.h"
#include "figures/elephant.h"
#include "figures/pawn.h"
#include "figures/rook.h"
#include "coreElems/ChangePawnElems/figurelabel.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
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
    Figure* fig = nullptr;
public slots:
    void remove_from_scene(Figure* figure);
    void createChangePawnWidget(bool color, int posX, int posY);
    void createNewFigure(Figure* element);
    void updateFiguresVec(Figure* fig);
signals:
    void initGameVecs(QVector<Figure*>& vecs);
private:
    void figuresPlacing(QGraphicsScene* scene, bool isWhite);
    void buildingBlock(QBrush brush, int rows, int cols);
    void inizialization(QGraphicsScene* scene);
    void initVectorOfBlocks();
    bool neededColorChecker(int rows, int cols) const;
    QVector< QVector<Block*> > arrOfBlocks;// to draw a board
    int NEWFIGX, NEWFIGY;
    ChangePawnWidget* changePawnWidget{nullptr};
    Game* game{nullptr};
};

#endif // BOARD_H
