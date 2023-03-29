#include "king.h"
#include "pawn.h"
#include <QGraphicsScene>
#include <QList>
#include <QVector>

King::King(int x, int y, bool isWhite) : Figures(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(":/chesscom/wK.png"));
    else
        this->setPixmap(QPixmap(":/chesscom/bK.png"));
}

QVector<QPointF> King::getValidNeighbourPositions()
{
    //Возвращает вектор из возможных позиций
    QVector<QPointF> positions;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            QPointF neighbourPosition = (this->pos() / 80) + QPointF(i, j);
            qDebug()<<neighbourPosition<<"neighbourPosition";
            bool isOutsideSceneByX = neighbourPosition.x() < 0 || neighbourPosition.x() >= 8;
            bool isOutsideSceneByY = neighbourPosition.y() < 0 || neighbourPosition.y() >= 8;

            if (isOutsideSceneByX || isOutsideSceneByY) {
                continue;
            }

            if (neighbourPosition == this->pos() / 80) {
                continue;
            }

            positions.push_back(neighbourPosition);
        }
    }

    return positions;
}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  /*  QVector<QPointF> positions = this->getValidNeighbourPositions();
        for (const auto& point : positions) {
            int x = point.x();
            int y = point.y();
            board->blockArray[x][y]->setBrush(Qt::red);
            for(int i = 0; i < game->figuresAll.size(); i++){
                if(game->figuresAll[i]->pos() == board->blockArray[x][y]->pos()){

                    if(this->getColor() == true){
                        if(game->figuresAll[i]->getColor() == true)
                            board->blockArray[x][y]->setBrush(Qt::green);
                        else
                            board->blockArray[x][y]->setBrush(Qt::yellow);
                    }

                    else{
                        if(game->figuresAll[i]->getColor() == true)
                            board->blockArray[x][y]->setBrush(Qt::yellow);
                        else
                            board->blockArray[x][y]->setBrush(Qt::green);
                    }
                }
            }
        }
*/
}

void King::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /*QVector<QPointF> positions = this->getValidNeighbourPositions();
        for (const auto& point : positions) {
            int x = point.x();
            int y = point.y();
            this->setDefaultBrush(board->blockArray[x][y]);
        }*/
}

