#include "figures/queen.h"

Queen::Queen(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteQueen));
    else
        this->setPixmap(QPixmap(pngBlackQueen));
}

QVector<Block*> Queen::getValidNeighbourPositions()
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

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if(checkOnOut(i, j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);
        }
    }

    for (int i = -8; i < 8; i++){
        for (int j = -8; j < 8; j++){
            if(checkOnOut(i, j) && (i == j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);

            int xs = getPosition().x() + i;
            int ys = getPosition().y() - i;
            if(xs >= 0 && ys >= 0 && xs <= 7 && ys <= 7){
                positions.push_back(getBoard()[xs][ys]);
            }

        }
    }

    QSet<Block*> set_figures;
    for(auto& figures : positions){
        if(figures->getBlockPos() != this->getPosition())
            set_figures.insert(figures);
    }

    positions.clear();

    for(auto& elem : set_figures){
        positions.push_back(elem);
    }

    return positions;
}

void Queen::getKnowledge(QVector<Block *> vec_block)
{
    QVector<Block*>forward;
    QVector<Block*>back;
    QVector<Block*>left;
    QVector<Block*>right;
    QVector<Block*>upper_left;
    QVector<Block*>upper_right;
    QVector<Block*>down_left;
    QVector<Block*>down_right;

    for(auto& elem : vec_block){
#define ELEM_X elem->getBlockPos().x()
#define ELEM_Y elem->getBlockPos().y()
        if(ELEM_X == getPosition().x() && ELEM_Y >= getPosition().y())
            forward.push_back(elem);
        if(ELEM_X == getPosition().x() && ELEM_Y <= getPosition().y())
            back.push_back(elem);
        if(ELEM_X < getPosition().x() && ELEM_Y == getPosition().y())
            left.push_back(elem);
        if(ELEM_X > getPosition().x() && ELEM_Y == getPosition().y())
            right.push_back(elem);
        if(ELEM_X < getPosition().x() && ELEM_Y < getPosition().y())
            upper_left.push_back(elem);
        if(ELEM_X > getPosition().x() && ELEM_Y < getPosition().y())
            upper_right.push_back(elem);
        if(ELEM_X < getPosition().x() && ELEM_Y > getPosition().y())
            down_left.push_back(elem);
        if(ELEM_X > getPosition().x() && ELEM_Y > getPosition().y())
            down_right.push_back(elem);
    }
    bubbleSortMaxToMinY(forward);
    bubbleSortMinToMaxY(back);
    bubbleSortMinToMaxX(left);
    bubbleSortMaxToMinX(right);
    bubbleSortMinToMaxX(upper_left);
    bubbleSortMaxToMinX(upper_right);
    bubbleSortMinToMaxX(down_left);
    bubbleSortMaxToMinX(down_right);

    vecFromGetKnowledge = step_length_limiter_2(forward) +
            step_length_limiter_2(back)
            + step_length_limiter_2(left)
            + step_length_limiter_2(right) +
            step_length_limiter_2(upper_left) +
            step_length_limiter_2(upper_right) +
            step_length_limiter_2(down_left) +
            step_length_limiter_2(down_right);

    step_length_limiter(forward);
    step_length_limiter(back);
    step_length_limiter(left);
    step_length_limiter(right);
    step_length_limiter(upper_left);
    step_length_limiter(upper_right);
    step_length_limiter(down_left);
    step_length_limiter(down_right);
}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
    getKnowledge(getValidNeighbourPositions());
}

void Queen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
    emit updateFiguresPositions(this);
}

void Queen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

