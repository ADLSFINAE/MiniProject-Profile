#include "figures/pawn.h"

Pawn::Pawn(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhitePawn));
    else
        this->setPixmap(QPixmap(pngBlackPawn));
    start_pos_x = x;
    start_pos_y = y;
    isMovedFromStart = false;
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    if(!leave_from_start_position()){
        for(int i = 1; i < 3; i++)
            forward_step(positions, i);
    }
    else
        forward_step(positions, 1);

    return positions;
}

void Pawn::forward_step(QVector<Block*>& positions, int offset)
{
    if(this->getColor()){
        if(((getPosition().x() - offset >= 0) && (getPosition().x() - offset <= 7))
                || ((getPosition().y() - offset >= 0) && (getPosition().y() - offset <= 7))){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() - offset]);
        }
    }

    if(!this->getColor()){
        if(((getPosition().x() - offset >= 0) && (getPosition().x() - offset <= 7))
                || ((getPosition().y() + offset >= 0) && (getPosition().y() + offset <= 7))){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() + offset]);
        }
    }

}

bool Pawn::leave_from_start_position()
{
    if((this->start_pos_x != this->getPosition().x()) || (this->start_pos_y != this->getPosition().y()))
        return true;
    if((this->start_pos_x != this->getPosition().x()) && (this->start_pos_y != this->getPosition().y()))
        return true;
    else
        return false;
}

void Pawn::step_length_limiter_for_pawn(QVector<Block *> vec_block)
{
    if(vec_block.size() == 0){
        this->setPosition(this->getPosition().x(), this->getPosition().y());
    }
    else{
        qDebug()<<vec_block.size();
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
}

QVector<Block *> Pawn::getKnowledge()
{
    QVector<Block*> left_right;
    if(this->getColor()){
        if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7)
                && (getPosition().y() - 1 >= 0) && (getPosition().y() - 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() - 1][getPosition().y() - 1]);
        if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7)
                && (getPosition().y() - 1 >= 0) && (getPosition().y() - 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() + 1][getPosition().y() - 1]);
    }
    else{
        if((getPosition().x() - 1 >= 0) && (getPosition().x() - 1 <= 7)
                && (getPosition().y() + 1 >= 0) && (getPosition().y() + 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() - 1][getPosition().y() + 1]);
        if((getPosition().x() + 1 >= 0) && (getPosition().x() + 1 <= 7)
                && (getPosition().y() + 1 >= 0) && (getPosition().y() + 1 <= 7))
            left_right.push_back(getBoard()[getPosition().x() + 1][getPosition().y() + 1]);
    }

    for(auto& elem : left_right){
        if(elem != nullptr){
            QVector<QGraphicsItem*> vec = elem->getCollidingItemsForMousePressEvent();
            for(auto& vec_elem : vec){
                Figure* fig = dynamic_cast<Figure*>(vec_elem);
                if(fig != nullptr){
                    if(((this->getColor() && fig->getColor())) || (!this->getColor() && !fig->getColor()))
                        elem->setAnotherBrushColor(Qt::green);
                    else
                        elem->setAnotherBrushColor(Qt::blue);

                }
            }
        }
    }

    return left_right;
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!(this->getColor() && this->getPosition().y() == 0)
            && !(!this->getColor() && this->getPosition().y() == 7)){
        Figure::mousePressEvent(event);

        step_length_limiter_for_pawn(this->getValidNeighbourPositions());
        getKnowledge();
    }
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!(this->getColor() && this->getPosition().y() == 0)
            && !(!this->getColor() && this->getPosition().y() == 7)){
    QVector<QPair<Figure*, double> > figure_list;
    QVector<QPair<Block*, double> > block_list;

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

    for(auto& block : getKnowledge()){
        for(auto& fig : figure_list){
            if(block != nullptr && fig.first != nullptr){
            block_list.push_back({block, calculatingDistance(
                                  (int)block->pos().x() + 40,//aviable to delete +40
                                  (int)block->pos().y() + 40,//aviable to delete +40
                                  (int)mapToScene(event->pos()).x() + 40,
                                  (int)mapToScene(event->pos()).y() + 40)});
            if(this->getColor() == fig.first->getColor())
                block->setAnotherBrushColor(Qt::green);
            else
                block->setAnotherBrushColor(Qt::blue);
            }
        }
    }

    find_valid_positions(block_list);
    set_def_color_for_all_board();
    }
    else{
        emit vahue(this);
        emit createChangePawnWidget(this->getColor());
    }
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

