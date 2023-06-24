#include "figures/rook.h"

Rook::Rook(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteRook));
    else
        this->setPixmap(QPixmap(pngBlackRook));
}

QVector<Block*> Rook::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    for (int i = -8; i <= 8; i++){
        for (int j = -8; j <= 8; j++){
            if(checkOnOut(i, j)){
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y()]);
                positions.push_back(getBoard()[getPosition().x()][getPosition().y() + j]);
            }
        }
    }

    return positions;
}

void Rook::getKnowledge(QVector<Block *> vec_block)
{
    QVector<Block*>forward;
    QVector<Block*>back;
    QVector<Block*>left;
    QVector<Block*>right;

    int current_figure_x = this->getPosition().x();
    int current_figure_y = this->getPosition().y();
    for(auto& elem : vec_block){
#define ELEM_X elem->getBlockPos().x()
#define ELEM_Y elem->getBlockPos().y()
        if(ELEM_X == current_figure_x && ELEM_Y >= current_figure_y)
            forward.push_back(elem);
        if(ELEM_X == current_figure_x && ELEM_Y <= current_figure_y)
            back.push_back(elem);
        if(ELEM_X < current_figure_x && ELEM_Y == current_figure_y)
            left.push_back(elem);
        if(ELEM_X > current_figure_x && ELEM_Y == current_figure_y)
            right.push_back(elem);
    }

    bubbleSortMaxToMinY(forward);
    bubbleSortMinToMaxY(back);
    bubbleSortMinToMaxX(left);
    bubbleSortMaxToMinX(right);

    vecFromGetKnowledge = step_length_limiter_2(forward) +
            step_length_limiter_2(back) +
            step_length_limiter_2(left) +
            step_length_limiter_2(right);

    step_length_limiter(forward);
    step_length_limiter(back);
    step_length_limiter(left);
    step_length_limiter(right);
}

void Rook::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
    getKnowledge(this->clean_up(getValidNeighbourPositions()));
}

void Rook::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
    emit updateFiguresPositions(this);
}

void Rook::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

