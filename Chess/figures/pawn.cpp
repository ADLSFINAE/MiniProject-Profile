#include "figures/pawn.h"
#define PASSAGEBLOCK this->getBoard()[passagePos->x()][passagePos->y()]
Pawn::Pawn(int x, int y, bool isWhite) : Figure(x, y, isWhite)
{
    if(isWhite)
        this->setPixmap(QPixmap(pngWhitePawn));
    else
        this->setPixmap(QPixmap(pngBlackPawn));
    start_pos_x = x;
    start_pos_y = y;
    isMovedFromStart = false;
    QObject::connect(this, &Pawn::signalOnAddPassageElem, this, &Pawn::slotOnAddPassageElem);
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    if(!leave_from_start_position()){
        for(int i = 1; i < 3; i++)
            forward_step(positions, i);
    }
    else{
        forward_step(positions, 1);
        if(passagePos != nullptr && !isMovedFromStart)
            positions.push_back(PASSAGEBLOCK);
    }

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
    //Заполнение для блокировки атаки короля
    vecFromGetKnowledge = left_right;

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
    this->setOffset(0, 0);
    emit updateFiguresPositions(this);
    if(!(this->getColor() && this->getPosition().y() == 0)
            && !(!this->getColor() && this->getPosition().y() == 7)){
        Figure::mousePressEvent(event);
        for(auto& block : getKnowledge()){
            if(block != nullptr)
                block->setAnotherBrushColor(Qt::white);
            if(passagePos != nullptr && !isMovedFromStart){
                PASSAGEBLOCK->setAnotherBrushColor(Qt::yellow);
                if(this->getColor() && passagePawn->getPosition().y() != 3){
                    PASSAGEBLOCK->setAnotherBrushColor(Qt::white);
                }
                if(!this->getColor() && passagePawn->getPosition().y() != 4){
                    PASSAGEBLOCK->setAnotherBrushColor(Qt::white);
                }
            }
        }
        step_length_limiter_for_pawn(this->getValidNeighbourPositions());
        this->getKnowledge();
    }
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setOffset(0, 0);
    QVector<QPair<Figure*, double> > figure_list;
    QVector<QPair<Block*, double> > block_list;

    for(auto& elem_of_item_list : this->collidingItems()){//Вектор пересеченных фигур, которые можно уничтожить
        Figure* item = dynamic_cast<Figure*>(elem_of_item_list);
        if((item != nullptr && item != this)
                && ((this->getColor() && !item->getColor()) || (!this->getColor() && item->getColor()))){
            figure_list.push_back({item, calculatingDistance(
                                   (int)item->pos().x() + 40,//aviable to delete +40
                                   (int)item->pos().y() + 40,//aviable to delete +40
                                   (int)mapToScene(event->pos()).x(),
                                   (int)mapToScene(event->pos()).y())});
        }

        Block* block = dynamic_cast<Block*>(elem_of_item_list);
        if(block != nullptr && check_on_valid_block(block)
                && block->check_another_brush_color_on_def_color()){
            block_list.push_back({block, calculatingDistance(
                                  (int)block->pos().x() + 40,//aviable to delete +40
                                  (int)block->pos().y() + 40,//aviable to delete +40
                                  (int)mapToScene(event->pos()).x(),
                                  (int)mapToScene(event->pos()).y())});
        }
    }

    for(auto& block : getKnowledge()){
        for(auto& fig : figure_list){
            if(block != nullptr && fig.first != nullptr){
                block_list.push_back({block, calculatingDistance(
                                      (int)block->pos().x() + 40,//aviable to delete +40
                                      (int)block->pos().y() + 40,//aviable to delete +40
                                      (int)mapToScene(event->pos()).x(),
                                      (int)mapToScene(event->pos()).y())});
                if(this->getColor() && fig.first->getColor())
                    block->setAnotherBrushColor(Qt::green);
                if(this->getColor() && !fig.first->getColor())
                    block->setAnotherBrushColor(Qt::blue);
            }
        }
    }

    QPointF positionInMoment = this->getPosition();

    if(passagePos != nullptr){
        for(auto& elem : PASSAGEBLOCK->collidingItems()){
            if(elem == this){
                block_list.push_back({PASSAGEBLOCK, calculatingDistance(
                                      (int)PASSAGEBLOCK->pos().x() + 40,//aviable to delete +40
                                      (int)PASSAGEBLOCK->pos().y() + 40,//aviable to delete +40
                                      (int)mapToScene(event->pos()).x(),
                                      (int)mapToScene(event->pos()).y())});
                PASSAGEBLOCK->setAnotherBrushColor(Qt::yellow);
                break;
            }
        }
    }

    find_valid_positions(block_list);

    if(positionInMoment != this->getPosition()){
        emit signalAboutMoving();
    }

    if((passagePos != nullptr && positionInMoment.y() < this->getPosition().y() && this->getColor())
            || (passagePos != nullptr && positionInMoment.y() > this->getPosition().y() && !this->getColor())){
        emit updateFiguresPositionsFromPawn(this);
    }
    else if(passagePos != nullptr && this->getPosition().x() == passagePos->x()
            && this->getPosition().y() == passagePos->y()){
        emit updateFiguresPositionsFromPawn(this);
        if(passagePos != nullptr){
            isMovedFromStart = true;
            emit vahue(passagePawn);
            passagePos = nullptr;
        }
    }
    else{
        emit updateFiguresPositionsFromPawn(this);
        isMovedFromStart = false;
    }

    set_def_color_for_all_board();

    if(((this->getColor() && this->getPosition().y() == 0))
            || ((!this->getColor() && this->getPosition().y() == 7))){
        emit vahue(this);
        emit createChangePawnWidget(this->getColor(), this->getPosition().x(), this->getPosition().y());
    }

    emit updateFiguresPositions(this);
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}

void Pawn::slotPawnCollection(QVector< QPair <Figure*, QPointF> >& collection, bool color)
{

    if(this->getColor()){
        for(auto& pawn : collection){
            if(this->getPosition().y() == 3 && pawn.first->getPosition().y() == 3 && !pawn.first->getColor()){
                if(this->getPosition().x() + 1 == pawn.first->getPosition().x()
                        || this->getPosition().x() - 1 == pawn.first->getPosition().x()){
                    passagePawn = pawn.first;
                    emit signalOnAddPassageElem(QPointF(pawn.first->getPosition().x(), pawn.first->getPosition().y() - 1));
                    break;
                }
            }
        }
    }
    else{
        for(auto& pawn : collection){
            if(this->getPosition().y() == 4 && pawn.first->getPosition().y() == 4 && pawn.first->getColor()){
                if(this->getPosition().x() + 1 == pawn.first->getPosition().x()
                        || this->getPosition().x() - 1 == pawn.first->getPosition().x()){
                    passagePawn = pawn.first;
                    emit signalOnAddPassageElem(QPointF(pawn.first->getPosition().x(), pawn.first->getPosition().y() + 1));
                    break;
                }
            }
        }
    }
}

void Pawn::slotOnAddPassageElem(QPointF passageBlockPos)
{
    passagePos = new QPointF(passageBlockPos);
}

