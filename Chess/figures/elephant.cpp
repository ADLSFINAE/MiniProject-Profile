#include "elephant.h"

Elephant::Elephant(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhiteElephant));
    else
        this->setPixmap(QPixmap(pngBlackElephant));
}

QVector<Block*> Elephant::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    for (int i = -8; i < 8; i++){
        for (int j = -8; j < 8; j++){
            if(checkOnOut(i, j) && (i == j))
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() + j]);

            if(getPosition().x() + i >= 0 && getPosition().y() - i >= 0
                    && getPosition().x() + i <= 7 && getPosition().y() - i <= 7)
                positions.push_back(getBoard()[getPosition().x() + i][getPosition().y() - i]);

        }
    }
    return positions;
}

void Elephant::getKnowledge(QVector<Block *> vec_block)
{
    QVector<Block*>upper_left;
    QVector<Block*>upper_right;
    QVector<Block*>down_left;
    QVector<Block*>down_right;

    int current_figure_x = this->getPosition().x();
    int current_figure_y = this->getPosition().y();
    for(auto& elem : vec_block){
#define ELEM_X elem->getBlockPos().x()
#define ELEM_Y elem->getBlockPos().y()
        if(ELEM_X <= current_figure_x && ELEM_Y <= current_figure_y)
            upper_left.push_back(elem);
        if(ELEM_X >= current_figure_x && ELEM_Y <= current_figure_y)
            upper_right.push_back(elem);
        if(ELEM_X <= current_figure_x && ELEM_Y >= current_figure_y)
            down_left.push_back(elem);
        if(ELEM_X >= current_figure_x && ELEM_Y >= current_figure_y)
            down_right.push_back(elem);
    }

    upper_left = sort_min_to_max_x(upper_left);
    upper_right = sort_min_to_max_x(upper_right);
    down_left = sort_min_to_max_x(down_left);
    down_right = sort_min_to_max_x(down_right);

    upper_right = reverse_vector(upper_right);
    down_right = reverse_vector(down_right);

    vecFromGetKnowledge = step_length_limiter_2(upper_left) +
            step_length_limiter_2(upper_right) +
            step_length_limiter_2(down_left) +
            step_length_limiter_2(down_right);

    step_length_limiter(upper_left);
    step_length_limiter(upper_right);
    step_length_limiter(down_left);
    step_length_limiter(down_right);

}

void Elephant::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateFiguresPositions(this);
    Figure::mousePressEvent(event);
    getKnowledge(this->clean_up(getValidNeighbourPositions()));
}

void Elephant::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseReleaseEvent(event);
    emit updateFiguresPositions(this);
}

void Elephant::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

