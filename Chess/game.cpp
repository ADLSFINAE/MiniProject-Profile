#include "game.h"
#include <QDebug>
Game::Game()
{

}

void Game::initOfVecs(Figure* figure, bool isWhite)
{
    qDebug()<<"GOVNO HAPPENINGS";
    if(isWhite)
        vecOfWhiteFigures.push_back({figure, figure->getPosition()});
    else
        vecOfBlackFigures.push_back({figure, figure->getPosition()});
}

void Game::giveInfo()
{
    qDebug()<<"GAME GET INFO";
    for(auto& elem : vecOfWhiteFigures){
        qDebug()<<elem.second.x()<<elem.second.y();
    }
    for(auto& elem : vecOfBlackFigures){
        qDebug()<<elem.second.x()<<elem.second.y();
    }
}

void Game::editVecs(QVector<Figure *> vecs)
{
    vecOfWhiteFigures.clear();
    vecOfBlackFigures.clear();
    for(auto& elem : vecs){
        if(elem->getColor()){
            vecOfWhiteFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfWhitePawnFigures.push_back({elem, elem->getPosition()});
            }
        }
        else{
            vecOfBlackFigures.push_back({elem, elem->getPosition()});
            Pawn* pawn = dynamic_cast<Pawn*>(elem);
            if(pawn != nullptr){
                vecOfBlackPawnFigures.push_back({elem, elem->getPosition()});
            }
        }
    }
    qDebug()<<vecOfWhitePawnFigures.size()<<"VEC OF WHITE PAWN FIGURES SIZE";
    qDebug()<<vecOfBlackPawnFigures.size()<<"VEC OF BLACK PAWN FIGURES SIZE";
}
