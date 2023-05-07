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

bool Figure::get_permission_to_move(Block* block)
{
    QVector<Figure*>vec_of_collidingItems;
    for(auto& elem : block->collidingItems()){
        Figure* item = dynamic_cast<Figure*>(elem);
        if(item != nullptr)
            vec_of_collidingItems.push_back(item);
    }
    qDebug()<<"Size of vec_of_collidingItems"<<vec_of_collidingItems.size();
    if(vec_of_collidingItems.size() == 2)
        return false;
    else
        return true;
}

double Figure::calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y)
{
    return qSqrt(qPow((event_figure_x - block_x), 2) + qPow((event_figure_y - block_y), 2));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions()){
        block->setBrush(Qt::yellow);
        block->colorWasChanged = true;
    }
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*>item_list = this->collidingItems();
    QVector<Figure*>figure_list;

    for(auto& elem_of_item_list : item_list){//Вектор пересеченных фигур, которые можно уничтожить
        Figure* item = dynamic_cast<Figure*>(elem_of_item_list);
        if(item != nullptr)
            figure_list.push_back(item);
    }

    for(auto& elem_of_block_list : getValidNeighbourPositions()){//Перекраска позиций, куда можно сходить
        elem_of_block_list->setBrush(elem_of_block_list->getDefColor());
    }


    if(figure_list.size() == 1){ // Если фигура, с которой пересекается удерживаемая всего одна

        if(this->getColor() && !figure_list[0]->getColor()//Белый цвет нашей фигуры и Черный цвет атакуемой
                && checkForStep(getValidNeighbourPositions(), figure_list)){

            this->setPosition(figure_list[0]->getPosition().x(), figure_list[0]->getPosition().y());
            figure_list[0]->setPos(-100, -100);
        }
        else if(!this->getColor() && figure_list[0]->getColor()//Черный цвет нашей фигуры и Белый цвет атакуемой
                && checkForStep(getValidNeighbourPositions(), figure_list)){

            this->setPosition(figure_list[0]->getPosition().x(), figure_list[0]->getPosition().y());
            figure_list[0]->setPos(-100, -100);
        }
        else//Если цвет нашей и атакуемой одинаковый, возвращаемся назад
            this->setPos(this->getOldPosition().first, this->getOldPosition().second);
    }

    else if(figure_list.size() == 0){//Если фигуры нету, но есть клетки куда можно сходить
        QList<QGraphicsItem*>colliding_blocks_list = this->collidingItems();
        QVector<Block*>block_list;

        for(auto& elem_of_colliding_blocks : colliding_blocks_list){//Вектор блоков, куда можно сходить
            Block* item = dynamic_cast<Block*>(elem_of_colliding_blocks);
            if(item != nullptr)
                block_list.push_back(item);
        }

        //АЛГОРИТМ K-БЛИЖАЙШИХ СОСЕДЕЙ
        if(block_list.size() == 1)//Если фигура касается только одной клетки
            this->setPosition(block_list[0]->getBlockPos().x(), block_list[0]->getBlockPos().y());

        else{

            QVector<QPair<Block*, double> > valid_blocks_list;
            for(auto& elem_of_block_list : block_list){
                if(mapToScene(elem_of_block_list->pos()) != mapToScene(this->pos()))
                    valid_blocks_list.push_back({elem_of_block_list, calculatingDistance(
                                   (int)elem_of_block_list->pos().x(),
                                   (int)elem_of_block_list->pos().y(),
                                   (int)mapToScene(event->pos()).x(),
                                   (int)mapToScene(event->pos()).y())});
            }

            QVector<QPair<Block*, double> > updated_valid_block_list;
            for(auto& elem_liz : valid_blocks_list){
                for(auto& elem_nvm : getValidNeighbourPositions()){
                    if(elem_liz.first == elem_nvm)
                        updated_valid_block_list.push_back(elem_liz);
                }
            }

            if(updated_valid_block_list.size() == 0){
                this->setPos(this->getOldPosition().first, this->getOldPosition().second);
            }
            else{
                Block* findMe = nullptr;
                double checker = 1000;

                for(auto& elem : updated_valid_block_list){
                    qDebug()<<"PEN IS"<<elem.second;
                    if(checker > elem.second){
                       checker = elem.second;
                       findMe = elem.first;
                    }

                }
                if(get_permission_to_move(findMe)){
                    this->setPosition(findMe->getBlockPos().x(), findMe->getBlockPos().y());
                }
                else{
                    this->setPos(this->getOldPosition().first, this->getOldPosition().second);
                }
            }
        }
    }

    else
        this->setPos(this->getOldPosition().first, this->getOldPosition().second);
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}


