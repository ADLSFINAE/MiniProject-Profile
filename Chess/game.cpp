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
    for(auto& elem : vecOfWhiteFigures){
        qDebug()<<elem.second.x()<<elem.second.y();
    }
}

void Game::logicLoverBoy(bool isWhite, Figure *figure)
{
    /*int countOfBlocks = figure->getValidNeighbourPositions().size();
    QVector<Block*>vec = figure->getValidNeighbourPositions();
    if(isWhite){
        for(int i = 0; i < countOfBlocks; i++){
            if(vec[i]->pos() == )
        }
    }*/
}
