#include "player.h"

Player::Player(QString nameOfPlayer, bool color)
{
    this->color = color;
    this->nameOfPlayer = nameOfPlayer;
}

void Player::getVecOfFigures(QVector<Figure*>& vec){
    vecWithFigures.clear();
    vecWithFigures = vec;
}

void Player::workWithVec(int number)
{
    if(number % 2 == 1){
        for(auto& elem : vecWithFigures){
            elem->setEnabled(false);
        }
    }
    else{
        for(auto& elem : vecWithFigures){
            elem->setEnabled(false);
        }
    }
}
