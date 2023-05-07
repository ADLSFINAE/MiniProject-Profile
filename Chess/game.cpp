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
