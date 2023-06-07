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

QVector<Block *> Figure::clean_up(QVector<Block *> vec)
{
    QSet<Block*> set_figures;
    QVector<Block*> vec_figures;
    for(auto& figures : vec){
        if(figures->getBlockPos() != this->getPosition())
            set_figures.insert(figures);
    }

    for(auto& elem : set_figures){
        vec_figures.push_back(elem);
    }
    return vec_figures;
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
    qDebug()<<"ALL OKAY? YES";
}

bool Figure::check_on_valid_block(Block *block)
{
    for(auto& elem : clean_up(getValidNeighbourPositions())){
        if(elem->getBlockPos().x() == block->getBlockPos().x() &&
                elem->getBlockPos().y() == block->getBlockPos().y()){
            return true;
        }
    }
    return false;
}

void Figure::kill_functionality(Block *block)
{
    for(auto& elem : block->getCollidingItemsForMousePressEvent()){
        Figure* item = dynamic_cast<Figure*>(elem);
        if(item != nullptr && item != this){
            emit vahue(item);
            item->hide();
            break;
        }
    }
}

QVector<Block *> Figure::sort_min_to_max_x(QVector<Block *> vec_for_sort)
{
    if(vec_for_sort.size() == 0){
        return vec_for_sort;
    }

    else{
        for (int i = 0; i < vec_for_sort.size(); i++) {
            for (int j = 0; j < vec_for_sort.size() - 1; j++) {
              if (vec_for_sort[j]->getBlockPos().x() < vec_for_sort[j + 1]->getBlockPos().x()) {
                auto b = vec_for_sort[j];
                vec_for_sort[j] = vec_for_sort[j + 1];
                vec_for_sort[j + 1] = b;
              }
            }
          }
        return vec_for_sort;
    }
}

QVector<Block *> Figure::sort_min_to_max_y(QVector<Block *> vec_for_sort)
{
    if(vec_for_sort.size() == 0){
        return vec_for_sort;
    }

    else{
        for (int i = 0; i < vec_for_sort.size(); i++) {
            for (int j = 0; j < vec_for_sort.size() - 1; j++) {
              if (vec_for_sort[j]->getBlockPos().y() < vec_for_sort[j + 1]->getBlockPos().y()) {
                auto b = vec_for_sort[j];
                vec_for_sort[j] = vec_for_sort[j + 1];
                vec_for_sort[j + 1] = b;
              }
            }
          }
        return vec_for_sort;
    }
}

QVector<Block *> Figure::reverse_vector(QVector<Block *> vec_for_reverse)
{
    QVector<Block*> vec;
    for(int i = vec_for_reverse.size() - 1; i >= 0; i--)
        vec.push_back(vec_for_reverse[i]);
    return vec;
}

void Figure::step_length_limiter(QVector<Block *> &vec_block)
{
    for(int i = 0; i < vec_block.size(); i++){
        if(vec_block[i]->getAnotherBrushColor() == Qt::green
                || vec_block[i]->getAnotherBrushColor() == Qt::blue){
            for(int j = i + 1; j < vec_block.size(); j++){
                vec_block[j]->setAnotherBrushColor(vec_block[j]->getDefColor());
            }
            break;
        }
    }
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


QPair<Block*, double> Figure::find_min_dist_for_blocks(QVector<QPair<Block *, double> > vec)
{
    QPair<Block*, double> pull_up;
    if(vec.size() == 0){
        this->setPosition(getPosition().x(), getPosition().y());
    }
    if(vec.size() > 0){
        Block* minElem = nullptr;
        double checker = 1000;//если выставить vec[0].second,
        //то при размере массива в единицу присваивание minElem не сработает
        for(auto& elem : vec){
            if(checker > elem.second){
                minElem = elem.first;
                checker = elem.second;
            }
        }
        pull_up.first = minElem;
        pull_up.second = checker;
    }
    return pull_up;
}

void Figure::find_valid_positions(QVector<QPair<Block *, double> > block_vec)
{
    Block* smoke_it = find_min_dist_for_blocks(block_vec).first;
    if(smoke_it != nullptr){
        if(smoke_it->getAnotherBrushColor() == Qt::yellow){
            qDebug()<<"yellows";
            this->setPosition(smoke_it->getBlockPos().x(), smoke_it->getBlockPos().y());
        }
        if(smoke_it->getAnotherBrushColor() == Qt::blue){
            qDebug()<<"blues";
            this->setPosition(smoke_it->getBlockPos().x(), smoke_it->getBlockPos().y());
            kill_functionality(smoke_it);
        }
        if(smoke_it->getAnotherBrushColor() == Qt::green){
            qDebug()<<"green";
            this->setPosition(this->getPosition().x(), this->getPosition().y());
        }
    }
    else{
        qDebug()<<"default color";
        this->setPosition(this->getPosition().x(), this->getPosition().y());
    }

}

double Figure::calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y)
{
    return qSqrt(qPow((event_figure_x - block_x), 2) + qPow((event_figure_y - block_y), 2));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : clean_up(getValidNeighbourPositions()))
        block->setAnotherBrushColor(Qt::yellow);

    for(auto& elem : clean_up(getValidNeighbourPositions())){
        QVector<QGraphicsItem*> vec = elem->getCollidingItemsForMousePressEvent();
        for(auto& vec_elem : vec){
            Figure* fig = dynamic_cast<Figure*>(vec_elem);
            if(fig != nullptr){
                if((this->getColor() && fig->getColor()) || (!this->getColor() && !fig->getColor()))
                    elem->setAnotherBrushColor(Qt::green);
                else
                    elem->setAnotherBrushColor(Qt::blue);
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
                && block->check_another_brush_color_on_def_color()){
            block_list.push_back({block, calculatingDistance(
                                           (int)block->pos().x() + 40,//aviable to delete +40
                                           (int)block->pos().y() + 40,//aviable to delete +40
                                           (int)mapToScene(event->pos()).x() + 40,
                                           (int)mapToScene(event->pos()).y() + 40)});
        }
    }
    find_valid_positions(block_list);
    set_def_color_for_all_board();
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}


