#include "coreElems/ChangePawnElems/changepawnwidget.h"
#include "qdebug.h"

ChangePawnWidget::ChangePawnWidget(bool color, QWidget *parent)
    :QWidget(parent)
{
    this->resize(GlobX * pngWhiteFiguresVec.size(), GlobY);
    this->setWindowTitle("Change Pawn");

    if(color){
        for(auto& whiteFig : pngWhiteFiguresVec){
                whiteFiguresVec.push_back(new FigureLabel(offsetX, 0, whiteFig, true, this));
                offsetX = offsetX + GlobX;
        }
    }
    else{
        for(auto& blackFig : pngBlackFiguresVec){
                blackFiguresVec.push_back(new FigureLabel(offsetX, 0, blackFig, false, this));
                offsetX = offsetX + GlobX;
        }
    }
}

QVector<FigureLabel *> ChangePawnWidget::getFiguresVec(bool color)
{
    if(color)
        return whiteFiguresVec;
    else
        return blackFiguresVec;
}


