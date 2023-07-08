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
    QObject::connect(this, &Pawn::signalOnAddPassageElem, this, &Pawn::slotOnAddPassageElem);
}

QVector<Block*> Pawn::getValidNeighbourPositions()
{
    QVector<Block*> positions;
    if(this->getPosition().y() == 0 && this->getColor()){
        return positions;
    }
    else if(this->getPosition().y() == 7 && !this->getColor()){
        return positions;
    }
    else{
        if(!leave_from_start_position()){
            for(int i = 1; i < 3; i++)
                forward_step(positions, i);
        }
        else{
            forward_step(positions, 1);
        }

        if(this->getColor() == true && this->getPosition().y() == 3){
            for(auto& elem : this->getKnowledge()){
#define BLOCK_WHITE this->getBoard()[elem->getBlockPos().x()][elem->getBlockPos().y() + 1]
                for(auto item : BLOCK_WHITE->collidingItems()){
                    Pawn* pawn = dynamic_cast<Pawn*>(item);
                    if(pawn != nullptr && pawn->getColor() != this->getColor()){
                        elem->setAnotherBrushColor(Qt::blue);
                    }
                }
            }
        }

        if(this->getColor() == false && this->getPosition().y() == 4){
            for(auto& elem : this->getKnowledge()){
#define BLOCK_BLACK this->getBoard()[elem->getBlockPos().x()][elem->getBlockPos().y() - 1]
                for(auto item : BLOCK_BLACK->collidingItems()){
                    Pawn* pawn = dynamic_cast<Pawn*>(item);
                    if(pawn != nullptr && pawn->getColor() != this->getColor()){
                        elem->setAnotherBrushColor(Qt::blue);
                    }
                }
            }
        }



        return positions;
    }
}

void Pawn::forward_step(QVector<Block*>& positions, int offset)
{
    if(this->getColor()){
        if(((getPosition().x() - offset >= 0) && (getPosition().x() - offset <= 7))
                || ((getPosition().y() - offset >= 0) && (getPosition().y() - offset <= 7))){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() - offset]);
            getBoard()[getPosition().x()][getPosition().y() - offset]->setAnotherBrushColor(Qt::yellow);
        }
    }

    if(!this->getColor()){
        if(((getPosition().x() - offset >= 0) && (getPosition().x() - offset <= 7))
                || ((getPosition().y() + offset >= 0) && (getPosition().y() + offset <= 7))){
            positions.push_back(getBoard()[getPosition().x()][getPosition().y() + offset]);
        }
    }

    step_length_limiter_for_pawn(positions);
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
    return left_right;
    /*for(auto& elem : left_right){
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
    }*/
}


void Pawn::slotPawnCollection(QVector< QPair <Figure*, QPointF> >& collection)
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


void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit updateFiguresPositions(this);
    this->setOffset(0, 0);
    this->setOldPosition(this->pos().x(), this->pos().y());

    for(auto& elem : getKnowledge()){
        QVector<QGraphicsItem*> vec = elem->getCollidingItemsForMousePressEvent();
        for(auto& vec_elem : vec){
            Figure* fig = dynamic_cast<Figure*>(vec_elem);
            if(fig != nullptr){
                if((this->getColor() && fig->getColor()) || (!this->getColor() && !fig->getColor()))
                    elem->setAnotherBrushColor(Qt::green);
                if((this->getColor() && !fig->getColor()) || (!this->getColor() && fig->getColor()))
                    elem->setAnotherBrushColor(Qt::blue);
            }
        }
    }

    for(auto& elem : getValidNeighbourPositions()){
        elem->setAnotherBrushColor(elem->getDefColor());

        qDebug()<<elem->getBlockPos();
        if(!this->getFigOnBlock(elem)){
            elem->setAnotherBrushColor(Qt::yellow);
        }
    }
}

void Pawn::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    this->setOffset(0, 0);
    QVector<QPair<Figure*, double> > figure_list;
    QVector<QPair<Block*, double> > block_list;

    for(auto& block : getValidNeighbourPositions()){
            block_list.push_back({block, calculatingDistance(
                                  (int)block->pos().x() + 40,//aviable to delete +40
                                  (int)block->pos().y() + 40,//aviable to delete +40
                                  (int)mapToScene(event->pos()).x(),
                                  (int)mapToScene(event->pos()).y())});
            for(auto& elem : block->getCollidingItemsForMouseReleaseEvent(this)){
                Figure* figure = dynamic_cast<Figure*>(elem);
                if(figure != nullptr){
                    block->setAnotherBrushColor(block->getDefColor());
                    break;
                }
            }
    }
    block_list.push_back({this->getBoard()[this->getPosition().x()][this->getPosition().y()], calculatingDistance(
                          (int)this->getBoard()[this->getPosition().x()][this->getPosition().y()]->pos().x() + 40,//aviable to delete +40
                          (int)this->getBoard()[this->getPosition().x()][this->getPosition().y()]->pos().y() + 40,//aviable to delete +40
                          (int)mapToScene(event->pos()).x(),
                          (int)mapToScene(event->pos()).y())});

    for(auto& block : getKnowledge()){
        if(block->getAnotherBrushColor() == Qt::green || block->getAnotherBrushColor() == Qt::blue)
        block_list.push_back({block, calculatingDistance(
                              (int)block->pos().x() + 40,//aviable to delete +40
                              (int)block->pos().y() + 40,//aviable to delete +40
                              (int)mapToScene(event->pos()).x(),
                              (int)mapToScene(event->pos()).y())});
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
            emit vahue(passagePawn);
            passagePos = nullptr;
        }
    }
    else{
        emit updateFiguresPositionsFromPawn(this);
    }

    set_def_color_for_all_board();
    if(((this->getColor() && this->getPosition().y() == 0))
            || ((!this->getColor() && this->getPosition().y() == 7))){
        emit vahue(this);
        emit createChangePawnWidget(this->getColor(), this->getPosition().x(), this->getPosition().y());
        qDebug()<<"CHANGE PAWN WIDGET WAS CALLED";
    }

    emit updateFiguresPositions(this);
}

void Pawn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Figure::mouseMoveEvent(event);
}
