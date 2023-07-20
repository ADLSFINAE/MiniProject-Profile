#include "figures/figure.h"
#include "figures/king.h"

Figure::Figure(int x, int y, bool isWhite, QGraphicsPixmapItem* parent)
    :QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->isWhite = isWhite;
    this->setPos(x * GlobX, y * GlobY);

    arrWithBoard.resize(LongByX);

    for (int i = 0; i < LongByY; i++) {
        arrWithBoard[i].resize(LongByY);
    }

    this->setFlag(QGraphicsPixmapItem::ItemIsMovable, true);
    this->setOffset(0, 0);
}

Figure::Figure(Figure *fig)
{
    this->x = fig->x;
    this->y = fig->y;
    this->isWhite = fig->isWhite;
    this->sceneBoundingRect();

    this->arrWithBoard = fig->arrWithBoard;
}

////////////////////////Внутренние сортировки векторов константных ходов фигуры///////////////////////

void Figure::bubbleSortMinToMaxX(QVector<Block *>& vec)
{
    std::sort(vec.begin(), vec.end(),
              [&] (Block* block1, Block* block2) {return block1->getBlockPos().x() > block2->getBlockPos().x();});
}

void Figure::bubbleSortMaxToMinX(QVector<Block *>& vec)
{
    std::sort(vec.begin(), vec.end(),
              [&] (Block* block1, Block* block2) {return block1->getBlockPos().x() < block2->getBlockPos().x();});
}

void Figure::bubbleSortMinToMaxY(QVector<Block *>& vec)
{
    std::sort(vec.begin(), vec.end(),
              [&] (Block* block1, Block* block2) {return block1->getBlockPos().y() > block2->getBlockPos().y();});
}

void Figure::bubbleSortMaxToMinY(QVector<Block *>& vec)
{
    std::sort(vec.begin(), vec.end(),
              [&] (Block* block1, Block* block2) {return block1->getBlockPos().y() < block2->getBlockPos().y();});
}

////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////Ограничение длины хода////////////////////////////////////////////
bool Figure::getIterPos(Block *block)
{
    for(auto& elem : block->getCollidingItemsForMousePressEvent()){
        Figure* figure = dynamic_cast<Figure*>(elem);
        if((figure != nullptr)){
            return true;
            break;
        }
    }
    return false;
}

void Figure::step_length_limiter(QVector<Block *> &vec_block)
{
    int shizellow = 0;
    for(int i = 0; i < vec_block.size(); i++){
        if(getIterPos(vec_block[i])){
            shizellow = i + 1;
            for(int j = i + 1; j < vec_block.size(); j++){
                vec_block[j]->setAnotherBrushColor(vec_block[j]->getDefColor());
            }
            vec_block.erase((vec_block.begin() + shizellow), vec_block.end());
            break;
        }
    }
}

bool Figure::getIterPos_2(Block *block)
{
    for(auto& elem : block->getCollidingItemsForMousePressEvent()){
        Figure* figure = dynamic_cast<Figure*>(elem);
        King* king = dynamic_cast<King*>(elem);
        if((figure != nullptr && king == nullptr)){
            return true;
            break;
        }
    }
    return false;
}

QVector<Block *> Figure::step_length_limiter_2(QVector<Block *> vec_block)
{
    int shizellow = 0;
    for(int i = 0; i < vec_block.size(); i++){
        if(getIterPos_2(vec_block[i])){
            shizellow = i + 1;
            for(int j = i + 1; j < vec_block.size(); j++){
                vec_block[j]->setAnotherBrushColor(vec_block[j]->getDefColor());
            }
            vec_block.erase((vec_block.begin() + shizellow), vec_block.end());
            break;
        }
    }
    return vec_block;
}

////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////Установка позиции фигуры и получение этой позиции/////////////////////////////
void Figure::setPosition(int x, int y)
{
    this->setPos(x * GlobX, y * GlobY);
    this->x = x;
    this->y = y;
}

void Figure::setPosition(QPoint position)
{
    this->setPos(position.x() * GlobX, position.y() * GlobY);
    this->x = position.x();
    this->y = position.y();
}

void Figure::setOldPosition(int start_x, int start_y)
{
    this->start_x = start_x;
    this->start_y = start_y;
}

QPoint Figure::getPosition() const
{
    return QPoint(x, y);
}

QPair<int, int> Figure::getOldPosition() const
{
    QPair<int, int> oldPos;
    oldPos.first = this->start_x;
    oldPos.second = this->start_y;
    return oldPos;
}
////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////

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
    if(this->offset() == QPointF(-40, -40)){
        return QRectF(-FigureCenterX, -FigureCenterY, GlobX, GlobY);
    }
    return QRectF(0, 0, GlobX, GlobY);
}

void Figure::set_def_color_for_all_board()
{
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            if(arrWithBoard[i][j]->getAnotherBrushColor() != arrWithBoard[i][j]->getDefColor())
                arrWithBoard[i][j]->setDefColor();
        }
    }
}

bool Figure::check_on_valid_block(Block *block)
{
    for(auto& elem : getValidNeighbourPositions()){
        if(elem->getBlockPos() == block->getBlockPos())
            return true;
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
        this->setPosition(getPosition());
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
    Block* validBlock = find_min_dist_for_blocks(block_vec).first;
    if(validBlock != nullptr){
        if(validBlock->getAnotherBrushColor() == Qt::yellow){
            this->setPosition(validBlock->getBlockPos());
            qDebug()<<"YELLOW";
        }
        if(validBlock->getAnotherBrushColor() == Qt::blue){
            this->setPosition(validBlock->getBlockPos());
            kill_functionality(validBlock);
            qDebug()<<"BLUE";
        }
        if(validBlock->getAnotherBrushColor() == Qt::green
                || validBlock->getAnotherBrushColor() == Qt::white
                || validBlock->getAnotherBrushColor() == Qt::red){
            this->setPosition(getPosition());
            qDebug()<<"GREEN"<<"WHITE"<<"RED";
        }
        if(validBlock->getAnotherBrushColor() == validBlock->getDefColor()){
            this->setPosition(getPosition());
            qDebug()<<"DEF";
        }
    }
    else{
        this->setPosition(getPosition());
        qDebug()<<"ANOTHER VARIANT";
    }

}

double Figure::calculatingDistance(int block_x, int block_y, int event_figure_x, int event_figure_y)
{
    return qSqrt(qPow((event_figure_x - block_x), 2) + qPow((event_figure_y - block_y), 2));
}

bool Figure::getFigOnBlock(Block *block)
{
    for(auto& elem : block->collidingItems()){
        Figure* f = dynamic_cast<Figure*>(elem);
        if(f != nullptr){
            qDebug()<<"FIG WAS CALLED";
            return true;
        }
    }
    return false;
}

void Figure::blockForStepKing()
{
    QVector<Figure*> fig_vec;
    for(auto& elem : vecFromGetKnowledge){
        for(auto& fig : elem->collidingItems()){
            Figure* f = dynamic_cast<Figure*>(fig);
            if(f != nullptr && f->getColor() == this->getColor() && f->getPosition() != this->getPosition()){
                fig_vec.push_back(f);
            }
        }
    }
    qDebug()<<Qt::endl;
    qDebug()<<"FIG VEC INFO";
    for(auto& fig : fig_vec){
        qDebug()<<fig->getPosition();
    }
    qDebug()<<Qt::endl;
    for(auto& fig : fig_vec){
        for(auto& block : fig->vecFromGetKnowledge){
            if(block->getBlockPos() == this->getPosition()){
                qDebug()<<"WE FIND A BITCH"<<fig->getPosition();
            }
        }
    }
}

void Figure::blockForCheckOnDefense()
{
    QVector<Figure*> fig_vec;
    for(auto& elem : this->vecFromGetKnowledge){
        for(auto& fig : elem->collidingItems()){
            Figure* f = dynamic_cast<Figure*>(fig);
            if(f != nullptr && f->getColor() == this->getColor() && f->getPosition() != this->getPosition()){
                fig_vec.push_back(f);
            }
        }
    }

    qDebug()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<fig_vec.size();

    for(auto& fig : fig_vec){
        for(auto& block : fig->vecFromGetKnowledge){
            if(block->getBlockPos() == this->getPosition()){
                this->getBoard()[this->getPosition().x()][this->getPosition().y()]->setAnotherBrushColor(Qt::red);
                qDebug()<<"TRUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
                break;
            }
        }
    }
}

void Figure::getAllFigures(QVector<QPair<Figure *, QPointF> > &collection)
{
    allFigures.clear();
    allFigures = collection;
}



void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->setOffset(0, 0);
    this->setOldPosition(this->pos().x(), this->pos().y());
    for(auto& block : getValidNeighbourPositions())
        block->setAnotherBrushColor(Qt::yellow);

    qDebug()<<"getValidNeighbourPositions()"<<getValidNeighbourPositions().size();

    for(auto& elem : getValidNeighbourPositions()){
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
    this->setOffset(0, 0);
    QVector<QPair<Figure*, double>> figure_list;
    QVector<QPair<Block*, double>> block_list;
    for(auto& elem_of_item_list : this->collidingItems()){//Вектор пересеченных фигур, которые можно уничтожить
        Figure* item = dynamic_cast<Figure*>(elem_of_item_list);
        if((item != nullptr)
                && ((this->getColor() && !item->getColor()) || (!this->getColor() && item->getColor()))){
            figure_list.push_back({item, calculatingDistance(
                                   (int)item->pos().x(),//aviable to delete +40
                                   (int)item->pos().y(),//aviable to delete +40
                                   (int)mapToScene(event->pos()).x(),
                                   (int)mapToScene(event->pos()).y())});
        }

        Block* block = dynamic_cast<Block*>(elem_of_item_list);
        if(block != nullptr && check_on_valid_block(block)
                && block->check_another_brush_color_on_def_color()){
            block_list.push_back({block, calculatingDistance(
                                           (int)block->pos().x() + FigureCenterX,
                                           (int)block->pos().y() + FigureCenterY,
                                           (int)mapToScene(event->pos()).x(),
                                           (int)mapToScene(event->pos()).y())});
        }
#define FIGURE_BLOCK this->getBoard()[this->getPosition().x()][this->getPosition().y()]
        block_list.push_back({FIGURE_BLOCK, calculatingDistance(
                              (int)FIGURE_BLOCK->pos().x() + FigureCenterX,
                              (int)FIGURE_BLOCK->pos().y() + FigureCenterY,
                              (int)mapToScene(event->pos()).x(),
                              (int)mapToScene(event->pos()).y())});
    }

    QPointF positionInMoment = this->getPosition();
    find_valid_positions(block_list);
    if(positionInMoment != this->getPosition()){
        emit updateFiguresPositions(this);
        emit signalAboutMoving();
    }
    set_def_color_for_all_board();
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOffset(-FigureCenterX, -FigureCenterY);
    this->setPos(mapToScene(event->pos()));
}

