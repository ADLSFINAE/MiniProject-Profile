#include "game.h"

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

void Game::afterUs(Figure* figure, King *king, QSet<Block*>& CEELO, QVector<Figure*>& figVec)
{
    QVector<Block*> vec = king->getValidNeighbourPositions();
    vec.push_back(king->getBoard()[king->getPosition().x()][king->getPosition().y()]);
    figure->isHaveKing = false;
    for(auto& block : figure->vecFromGetKnowledge){
        for(auto& kingBlock : vec)
            if(block->getBlockPos() == kingBlock->getBlockPos()){
                CEELO.insert(block);
                if(block->getBlockPos() == king->getPosition()){
                    figure->isHaveKing = true;
                    figure->kingPosition = king->getPosition();
                }
            }
    }

    for(auto& kingBlock : king->getValidNeighbourPositions()){
        for(auto& figElem : vecOfAllFigures){
            if(king->getColor() != figElem.first->getColor()){
                if(kingBlock->getBlockPos() == figure->getPosition()){
                    figVec.push_back(figure);
                }
            }
        }
    }
}

void Game::countOfSteps()
{
    /*count++;
    if(count % 2 == 1){
        for(auto& elem : vecOfWhiteFigures)
            elem.first->setEnabled(false);

        for(auto& elem : vecOfBlackFigures)
            elem.first->setEnabled(true);
    }
    else{
        for(auto& elem : vecOfWhiteFigures)
            elem.first->setEnabled(true);

        for(auto& elem : vecOfBlackFigures)
            elem.first->setEnabled(false);
    }*/
}

void Game::calculateCheckMateFunc(bool colorOfTheKing)
{
    QSet<Block*>CEELO;
    QVector<Figure*> figVec;

    if(colorOfTheKing){
        for(auto& elem : vecOfBlackFigures)
            afterUs(elem.first, whiteKing, CEELO, figVec);
        emit exportCEELOToKingFromWhite(CEELO);
        emit exportFiguresVec(figVec);
    }

    else{
        for(auto& elem : vecOfWhiteFigures)
            afterUs(elem.first, blackKing, CEELO, figVec);
        emit exportCEELOToKingFromBlack(CEELO);
        emit exportFiguresVec(figVec);
    }
}

void Game::editVecs(QVector<Figure *>& vecs)
{
    for(auto& elem : vecOfAllFigures){
        QObject::disconnect(this, &Game::sendAllFigures, elem.first, &Figure::getAllFigures);
    }
    vecOfWhiteFigures.clear();
    vecOfBlackFigures.clear();
    vecOfWhitePawnFigures.clear();
    vecOfBlackPawnFigures.clear();
    vecOfAllFigures.clear();
    for(auto& elem : vecs){
        Horse* horse = dynamic_cast<Horse*>(elem);
        Queen* queen = dynamic_cast<Queen*>(elem);
        Rook* rook = dynamic_cast<Rook*>(elem);
        Elephant* elephant = dynamic_cast<Elephant*>(elem);
        if(horse != nullptr){
            horse->getValidNeighbourPositions();
        }
        if(elephant != nullptr){
            elephant->getKnowledge(elephant->getValidNeighbourPositions());
        }
        if(queen != nullptr){
            qDebug()<<"QUEEN WAS CALLED";
            queen->getKnowledge(queen->getValidNeighbourPositions());
        }
        if(rook != nullptr){
            rook->getKnowledge(rook->getValidNeighbourPositions());
        }

        if(elem->getColor()){
            vecOfWhiteFigures.push_back({elem, elem->getPosition()});
            vecOfAllFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfWhitePawnFigures.push_back({elem, elem->getPosition()});
                pawn->getKnowledge();
            }

            King* king = dynamic_cast<King*>(elem);
            if(king != nullptr && king->getColor()){
                whiteKing = king;
                king->getValidNeighbourPositions();
                qDebug()<<"white king was finded"<<whiteKing->getPosition();
            }
            if(king != nullptr && !king->getColor()){
                blackKing = king;
                king->getValidNeighbourPositions();
                qDebug()<<"black king was finded"<<blackKing->getPosition();
            }
        }
        else{
            vecOfBlackFigures.push_back({elem, elem->getPosition()});
            vecOfAllFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfBlackPawnFigures.push_back({elem, elem->getPosition()});
                pawn->getKnowledge();
            }
            King* king = dynamic_cast<King*>(elem);
            if(king != nullptr && king->getColor()){
                whiteKing = king;
                king->getValidNeighbourPositions();
                qDebug()<<"white king was finded"<<whiteKing->getPosition();
            }
            if(king != nullptr && !king->getColor()){
                blackKing = king;
                king->getValidNeighbourPositions();
                qDebug()<<"black king was finded"<<blackKing->getPosition();
            }
        }

    }

    for(auto& elem : vecOfAllFigures){
        QObject::connect(this, &Game::sendAllFigures, elem.first, &Figure::getAllFigures);
    }

    whiteKing->getValidNeighbourPositions();
    blackKing->getValidNeighbourPositions();

    emit getPawnCollection(vecOfWhitePawnFigures);
    emit getPawnCollection(vecOfBlackPawnFigures);
    emit signalStartCalculatingCheckMateFROMWHITE(whiteKing->getColor());
    emit sendAllFigures(vecOfAllFigures);
    emit signalStartCalculatingCheckMateFROMBLACK(blackKing->getColor());
    whiteKing->set_def_color_for_all_board();
    blackKing->set_def_color_for_all_board();
}
