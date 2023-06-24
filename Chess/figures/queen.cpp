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
        if(ELEM_X < current_figure_x && ELEM_Y < current_figure_y)
            upper_left.push_back(elem);
        if(ELEM_X > current_figure_x && ELEM_Y < current_figure_y)
            upper_right.push_back(elem);
        if(ELEM_X < current_figure_x && ELEM_Y > current_figure_y)
            down_left.push_back(elem);
        if(ELEM_X > current_figure_x && ELEM_Y > current_figure_y)
            down_right.push_back(elem);
    }
    bubbleSortY(forward);
    bubbleSortY(back);
    bubbleSortX(left);
    bubbleSortX(right);
    bubbleSortX(upper_left);
    bubbleSortX(upper_right);
    bubbleSortX(down_left);
    bubbleSortX(down_right);

    forward = reverse_vector(forward);
    right = reverse_vector(right);
    upper_right = reverse_vector(upper_right);
    down_right = reverse_vector(down_right);

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
    getKnowledge(this->clean_up(getValidNeighbourPositions()));
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

