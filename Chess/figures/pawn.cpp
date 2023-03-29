#include "pawn.h"
extern Board* board;
Pawn::Pawn(int x, int y, bool isWhite) : Figures(x, y, isWhite)
{
    this->isWhite = isWhite;

    if(isWhite)
        this->setPixmap(QPixmap(":/chesscom/wP.png"));
    else
        this->setPixmap(QPixmap(":/chesscom/bP.png"));
}

QVector<QPointF> Pawn::getValidNeighbourPositions()
{
    QVector<QPointF> positions;

    if(isWhite){
        for(int i = 1; i < 3; i++){
            QPointF neighbourPosition = (this->pos() / 80) + QPointF(0, i);
            positions.push_back(neighbourPosition);
        }
        return positions;
    }

    else{
        for(int i = 1; i < 3; i++){
            QPointF neighbourPosition = (this->pos() / 80) + QPointF(0, -i);
            positions.push_back(neighbourPosition);
        }
        return positions;
    }
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*QVector<QPointF> positions = this->getValidNeighbourPositions();
        for (const auto& point : positions) {
            int x = point.x();
            int y = point.y();
            board->blockArray[x][y]->setBrush(Qt::red);
        }*/
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /*QVector<QPointF> positions = this->getValidNeighbourPositions();
        for (const auto& point : positions) {
            int x = point.x();
            int y = point.y();
            board->blockArray[x][y]->setBrush(board->blockArray[x][y]->defaultBrush);
        }*/
}
