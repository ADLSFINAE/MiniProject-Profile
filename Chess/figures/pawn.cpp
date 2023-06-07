#include "figures/pawn.h"

Pawn::Pawn(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhitePawn));
    else
        this->setPixmap(QPixmap(pngBlackPawn));
    start_pos_x = x;
    start_pos_y = y;
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    if(!leave_from_start_position()){
        for(int i = 1; i < 3; i++)
            forward_step(positions, i);
    }
    else{
        for(int i = 1; i < 2; i++)
            forward_step(positions, i);
    }


    return positions;
}

bool Pawn::leave_from_start_position()
{
    if(start_pos_x != this->getPosition().x() || start_pos_y != this->getPosition().y())
        return true;
    else
        return false;
}

void Pawn::step_length_limiter_for_pawn(QVector<Block *> vec_block)
{
    for(int i = 0; i < vec_block.size(); i++){
        if(vec_block[i]->getAnotherBrushColor() == Qt::green
                || vec_block[i]->getAnotherBrushColor() == Qt::blue){
            for(int j = i; j < vec_block.size(); j++){
                vec_block[j]->setAnotherBrushColor(vec_block[j]->getDefColor());
            }
            break;
        }
    }
}

void Pawn::forward_step(QVector<Block*>& positions, int offset)
{
    if(this->getColor()){
        if((this->getPosition().y() - offset >= 0) && (this->getPosition().y() - offset <= 7)){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() - offset]);
        }
    }
    else{
        if((this->getPosition().y() + offset >= 0) && (this->getPosition().y() + offset <= 7)){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() + offset]);
        }
    }
}

void Pawn::getKnowledge(QVector<Block *> vec_block)
{
    step_length_limiter_for_pawn(vec_block);

    if(this->getColor()){
        if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() - 1][getPosition().y() - 1]);
        if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() + 1][getPosition().y() - 1]);
    }
    else{
        if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() - 1][getPosition().y() + 1]);
        if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() + 1][getPosition().y() + 1]);
    }

    for(auto& elem : left_right){
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

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mousePressEvent(event);

    getKnowledge(getValidNeighbourPositions());
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
        for(auto& elem : left_right){
            block_list.push_back({elem, calculatingDistance(
                                  (int)elem->pos().x() + 40,//aviable to delete +40
                                  (int)elem->pos().y() + 40,//aviable to delete +40
                                  (int)mapToScene(event->pos()).x() + 40,
                                  (int)mapToScene(event->pos()).y() + 40)});
        }
    }
    find_valid_positions(block_list);
    set_def_color_for_all_board();
    left_right.clear();
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

