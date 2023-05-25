#include "figures/figure.h"
#include "qmath.h"
#include <QPainter>
Figure::Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent)
    :QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->isWhite = isWhite;
    this->setPos(x * GlobX, y * GlobY);
    this->sceneBoundingRect();
    qDebug()<<"Figures was included";

    arrWithBoard.resize(LongByX);

    for (int i = 0; i < LongByY; i++) {
        arrWithBoard[i].resize(LongByY);
    }
}

void Figure::setPosition(int x, int y)
{
    this->setPos(x * GlobX, y * GlobY);
    this->x = x;
    this->y = y;
}

void Figure::setOldPosition(int start_x, int start_y)
{
    this->start_x = start_x;
    this->start_y = start_y;
}


QPair<int, int> Figure::getOldPosition() const
{
    QPair<int, int> oldPos;
    oldPos.first = this->start_x;
    oldPos.second = this->start_y;
    return oldPos;
}

bool Figure::checkOnOut(int rows, int cols) const
{
    int sum_x = (this->getPosition().x() + rows);
    int sum_y = (this->getPosition().y() + cols);

    if((sum_x == getPosition().x()) &&(sum_y == getPosition().y()))
            return false;

    else if((sum_x >= 0) && (sum_x <= 7)
            && (sum_y >= 0) && (sum_y <= 7))
            return true;

    else
        return false;

}

bool Figure::checkForStep(QVector<Block*> block_vector, QVector<Figure*> fig_vector)
{
    if(fig_vector.size() == 1){
        for(auto& elem : block_vector){
            if(elem->pos() == fig_vector[0]->pos())
                return true;
        }
    }
        return false;
}

bool Figure::getColor()
{
    return isWhite;
}

QVector<QVector<Block *> > Figure::getBoard()
{
    return arrWithBoard;
}

QRectF Figure::boundingRect() const
{
    return figureSizeRect;
}

void Figure::set_def_color_for_all_board()
{
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            arrWithBoard[i][j]->setDefColor();
        }
    }
}

bool Figure::check_on_valid_block(Block *block)
{
    for(auto& elem : getValidNeighbourPositions()){
        if(elem->getBlockPos().x() == block->getBlockPos().x() &&
                elem->getBlockPos().y() == block->getBlockPos().y()){
            return true;
        }
    }
    return false;
}

bool Figure::working_with_colliding_vec_from_block(Block* block)
{
    Figure* fig;
    for(auto& elem : block->getCollidingItemsForMouseReleaseEvent(this)){
        Figure* item = dynamic_cast<Figure*>(elem);
        if(item != nullptr){
            fig = item;
            break;
        }
    }

    if(fig->getColor() == this->getColor())
        return false;
    else
        return true;


}

QPoint Figure::getPosition() const
{
    return QPoint(x, y);
}

void Figure::setBoard(QVector< QVector<Block*> > arrWithBoard)
{
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            this->arrWithBoard[i][j] = arrWithBoard[i][j];
        }
    }
}

QPair<Figure*, double> Figure::find_min_dist_for_figures(QVector<QPair<Figure *, double> > vec)
{
    QPair<Figure*, double> pull_up;
    if(vec.size() > 0){
        Figure* minElem = nullptr;
        double checker = 1000;
        for(auto& elem : vec){
            if(checker > elem.second){
                minElem = elem.first;
                checker = elem.second;
            }
        }
        if(minElem != nullptr){
            this->setPosition(minElem->getPosition().x(), minElem->getPosition().y());
            minElem->setPos(-100, -100);
        }
        pull_up.first = minElem;
        pull_up.second = checker;
    }
    return pull_up;
}

QPair<Block*, double> Figure::find_min_dist_for_blocks(QVector<QPair<Block *, double> > vec)
{
    QPair<Block*, double> pull_up;
    if(vec.size() == 0){
        this->setPosition(getPosition().x(), getPosition().y());
    }
    if(vec.size() > 0){
        Block* minElem = nullptr;
        double checker = 1000;
        for(auto& elem : vec){
            if(checker > elem.second){
                minElem = elem.first;
                checker = elem.second;
            }
        }
        pull_up.first = minElem;
        pull_up.second = checker;
        this->setPosition(minElem->getBlockPos().x(), minElem->getBlockPos().y());
    }
    return pull_up;
}

double Figure::calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y)
{
    return qSqrt(qPow((event_figure_x - block_x), 2) + qPow((event_figure_y - block_y), 2));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions()){
        block->setAnotherBrushColor(Qt::yellow);
        block->colorWasChanged = true;
    }

    for(auto& elem : getValidNeighbourPositions()){
        QVector<QGraphicsItem*> vec = elem->getCollidingItemsForMousePressEvent();
        for(auto& vec_elem : vec){
            Figure* fig = dynamic_cast<Figure*>(vec_elem);
            if(fig != nullptr){
                if((this->getColor() && fig->getColor()) || (!this->getColor() && !fig->getColor()))
                    elem->setBrush(elem->getDefColor());
                else
                    elem->setBrush(Qt::blue);
            }
        }
    }
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QVector<QPair<Figure*, double>> figure_list;
    QVector<QPair<Block*, double>> block_list;
    for(auto& elem_of_item_list : this->collidingItems()){//Вектор пересеченных фигур, которые можно уничтожить
        Figure* item = dynamic_cast<Figure*>(elem_of_item_list);
        if((item != nullptr)
                && ((this->getColor() && !item->getColor()) || (!this->getColor() && item->getColor()))){
            figure_list.push_back({item, calculatingDistance(
                                   (int)item->pos().x() + 40,//aviable to delete +40
                                   (int)item->pos().y() + 40,//aviable to delete +40
                                   (int)mapToScene(event->pos()).x() + 40,
                                   (int)mapToScene(event->pos()).y() + 40)});
        }

        Block* block = dynamic_cast<Block*>(elem_of_item_list);
        if(block != nullptr && check_on_valid_block(block)
                && block->check_another_brush_color_on_def_color()
                && working_with_colliding_vec_from_block(block)){
            block_list.push_back({block, calculatingDistance(
                                           (int)block->pos().x() + 40,//aviable to delete +40
                                           (int)block->pos().y() + 40,//aviable to delete +40
                                           (int)mapToScene(event->pos()).x() + 40,
                                           (int)mapToScene(event->pos()).y() + 40)});
        }
    }

    qDebug()<<"FIGURSHICA"<<figure_list.size();
    qDebug()<<"BLOCKSHICA"<<block_list.size();
    find_min_dist_for_figures(figure_list);
    find_min_dist_for_blocks(block_list);
    set_def_color_for_all_board();



}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}


