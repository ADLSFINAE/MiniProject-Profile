#include "game.h"
#include <QDebug>
Game::Game()
{
    QObject::connect(this, &Game::signalStartCalculatingCheckMateFROMWHITE, this, &Game::calculateCheckMateFunc);
    QObject::connect(this, &Game::signalStartCalculatingCheckMateFROMBLACK, this, &Game::calculateCheckMateFunc);
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

void Game::afterUs(QVector<Block*>anotherVec, QVector<Block*>kingBlockVec, QSet<Block*>& CEELO)
{
    for(auto& block : anotherVec){
        for(auto& kingBlock : kingBlockVec)
            if(block->getBlockPos() == kingBlock->getBlockPos()){
                CEELO.insert(block);
            }
    }
}

void Game::calculateCheckMateFunc(bool colorOfTheKing)
{
    QSet<Block*>CEELO;
    if(colorOfTheKing){
        for(auto& elem : vecOfBlackFigures)
            afterUs(elem.first->vecFromGetKnowledge, whiteKing->getValidNeighbourPositions(), CEELO);
        qDebug()<<"FOR WHITE KING"<<CEELO.size();
        emit exportCEELOToKingFromWhite(CEELO);
    }

    else{
        for(auto& elem : vecOfWhiteFigures)
            afterUs(elem.first->vecFromGetKnowledge, blackKing->getValidNeighbourPositions(), CEELO);
        qDebug()<<"FOR BLACK KING"<<CEELO.size();
        emit exportCEELOToKingFromBlack(CEELO);
    }
}

void Game::editVecs(QVector<Figure *>& vecs)
{
    auto whiteFigVec = vecOfWhiteFigures;
    auto blackFigVec = vecOfBlackFigures;


    vecOfWhiteFigures.clear();
    vecOfBlackFigures.clear();
    vecOfWhitePawnFigures.clear();
    vecOfBlackPawnFigures.clear();
    for(auto& elem : vecs){
        //elem->clean_up(elem->getValidNeighbourPositions());
        Horse* horse = dynamic_cast<Horse*>(elem);
        Queen* queen = dynamic_cast<Queen*>(elem);
        Rook* rook = dynamic_cast<Rook*>(elem);
        Elephant* elephant = dynamic_cast<Elephant*>(elem);
        if(horse != nullptr){
            horse->getValidNeighbourPositions();
        }
        if(elephant != nullptr){
            elephant->getKnowledge(elephant->clean_up(elephant->getValidNeighbourPositions()));
        }
        if(queen != nullptr){
            qDebug()<<"QUEEN WAS CALLED";
            queen->getKnowledge(queen->clean_up(queen->getValidNeighbourPositions()));
        }
        if(rook != nullptr){
            rook->getKnowledge(rook->clean_up(rook->getValidNeighbourPositions()));
        }

        if(elem->getColor()){
            vecOfWhiteFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfWhitePawnFigures.push_back({elem, elem->getPosition()});
                pawn->getKnowledge();
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
                pawn->getKnowledge();
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
    emit signalStartCalculatingCheckMateFROMWHITE(whiteKing->getColor());
    emit signalStartCalculatingCheckMateFROMBLACK(blackKing->getColor());
    whiteKing->set_def_color_for_all_board();
    blackKing->set_def_color_for_all_board();

    int countWhite = 0;
    for(auto& whFig : whiteFigVec){
        for(auto& elem : vecOfWhiteFigures){
            if(whFig.first->getPosition() == elem.first->getPosition()){
                countWhite++;
                break;
            }
        }
    }
    if(countWhite == 16){
        for(auto& elem : vecOfWhiteFigures){
            elem.first->setEnabled(false);
        }
        for(auto& elem : vecOfBlackFigures){
            elem.first->setEnabled(true);
        }
    }

    int countBlack = 0;
    for(auto& blFig : blackFigVec){
        for(auto& elem : vecOfBlackFigures){
            if(blFig.first->getPosition() != elem.first->getPosition()){
                countBlack++;
                break;
            }
        }
    }

    if(countBlack == 16){
        for(auto& elem : vecOfWhiteFigures){
            elem.first->setEnabled(true);
        }
        for(auto& elem : vecOfBlackFigures){
            elem.first->setEnabled(false);
        }
    }


    qDebug()<<"GAME STEPS"<<countWhite<<countBlack;

    qDebug()<<vecOfWhitePawnFigures.size()<<"VEC OF WHITE PAWN FIGURES SIZE";
    qDebug()<<vecOfBlackPawnFigures.size()<<"VEC OF BLACK PAWN FIGURES SIZE";
}
