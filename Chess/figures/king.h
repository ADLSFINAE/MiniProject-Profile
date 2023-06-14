#ifndef KING_H
#define KING_H
#include "figures/figure.h"
#include <QPixmap>

class King : public Figure
{
    Q_OBJECT
public:
    King(int x, int y, bool isWhite);
    QVector<Block*> getValidNeighbourPositions() override;
public slots:
    void getCEELO(QSet<Block*>CEELO);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    QSet<Block*>CEELO;

};

#endif // KING_H
