#include "game.h"
#include <QDebug>
Game::Game()
{
    QObject::connect(this, &Game::signalStartCalculatingCheckMate, this, &Game::calculateCheckMateFunc);
}

void Game::initOfVecs(Figure* figure, bool isWhite)
{
    if(isWhite)
        vecOfWhiteFigures.push_back({figure, figure->getPosition()});
    else
        vecOfBlackFigures.push_back({figure, figure->getPosition()});
}

void Game::giveInfo()
{
    for(auto& elem : vecOfWhiteFigures){
        qDebug()<<elem.second.x()<<elem.second.y();
    }
    for(auto& elem : vecOfBlackFigures){
        qDebug()<<elem.second.x()<<elem.second.y();
    }
}

void Game::afterUs(QVector<Block*>queenVec, QVector<Block*>blackKingVec, QSet<Block*>& CEELO)
{
    for(auto& block : queenVec){
        for(auto& blackKingBlock : blackKingVec)
            if(block->getBlockPos() == blackKingBlock->getBlockPos()){
                qDebug()<<"BLOCK"<<block->getBlockPos();
                CEELO.insert(block);
            }
    }
}

void Game::calculateCheckMateFunc()
{
    QSet<Block*>CEELO;
    qDebug()<<"CALCULATE WAS STARTED";
    for(auto& elem : vecOfWhiteFigures){
        afterUs(elem.first->vecFromGetKnowledge, blackKing->getValidNeighbourPositions(), CEELO);
    }
    qDebug()<<blackKing->getValidNeighbourPositions().size();
    qDebug()<<"CEELO SIZE"<<CEELO.size();
    emit exportCEELOToKing(CEELO);
}

void Game::editVecs(QVector<Figure *>& vecs)
{
    vecOfWhiteFigures.clear();
    vecOfBlackFigures.clear();
    vecOfWhitePawnFigures.clear();
    vecOfBlackPawnFigures.clear();
    for(auto& elem : vecs){
        elem->clean_up(elem->getValidNeighbourPositions());
        //ХУЕВАЯ ИДЕЯ И НУЖНА ДОПОЛНИТЕЛЬНАЯ ФУНКЦИЯ ПРОВЕРКИ, ТАК КАК ТУТ МАССИВЫ ЧИСТИТЬСЯ НЕ БУДУТ
        //ЛУЧШЕ СДЕЛАТЬ ПРОВЕРКУ НА ФИГУРУ, А НЕ НА ЦВЕТ
        //В step_length_limiter
        Horse* horse = dynamic_cast<Horse*>(elem);
        Queen* queen = dynamic_cast<Queen*>(elem);
        Pawn* pawn = dynamic_cast<Pawn*>(elem);
        Rook* rook = dynamic_cast<Rook*>(elem);
        Elephant* elephant = dynamic_cast<Elephant*>(elem);
        if(horse != nullptr){
            horse->getValidNeighbourPositions();
        }
        if(elephant != nullptr){
            elephant->getKnowledge(elephant->clean_up(elephant->getValidNeighbourPositions()));
        }
        if(queen != nullptr){
            queen->getKnowledge(queen->clean_up(queen->getValidNeighbourPositions()));
        }
        if(pawn != nullptr){
            pawn->getKnowledge();
        }
        if(rook != nullptr){
            rook->getKnowledge(rook->clean_up(rook->getValidNeighbourPositions()));
        }

        if(elem->getColor()){
            vecOfWhiteFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfWhitePawnFigures.push_back({elem, elem->getPosition()});
            }

            King* king = dynamic_cast<King*>(elem);
            if(king != nullptr && king->getColor()){
                whiteKing = king;
                qDebug()<<"white king was finded"<<whiteKing->getPosition();
            }
            if(king != nullptr && !king->getColor()){
                blackKing = king;
                qDebug()<<"black king was finded"<<blackKing->getPosition();
            }
        }
        else{
            vecOfBlackFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfBlackPawnFigures.push_back({elem, elem->getPosition()});
            }
            King* king = dynamic_cast<King*>(elem);
            if(king != nullptr && king->getColor()){
                whiteKing = king;
                qDebug()<<"white king was finded"<<whiteKing->getPosition();
            }
            if(king != nullptr && !king->getColor()){
                blackKing = king;
                qDebug()<<"black king was finded"<<blackKing->getPosition();
            }
        }

    }

    whiteKing->getValidNeighbourPositions();
    blackKing->getValidNeighbourPositions();

    emit getPawnCollection(vecOfWhitePawnFigures, true);
    emit getPawnCollection(vecOfBlackPawnFigures, false);
    emit signalStartCalculatingCheckMate();
    blackKing->set_def_color_for_all_board();

    qDebug()<<vecOfWhitePawnFigures.size()<<"VEC OF WHITE PAWN FIGURES SIZE";
    qDebug()<<vecOfBlackPawnFigures.size()<<"VEC OF BLACK PAWN FIGURES SIZE";
}
