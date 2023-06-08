#include "changepawnwidget.h"
#include "qdebug.h"

ChangePawnWidget::ChangePawnWidget(bool color, QWidget *parent)
    :QWidget(parent)
{
    this->resize(GlobX * pngWhiteFiguresVec.size(), GlobY);
    this->setWindowTitle("Change Pawn");

    if(color){
        qDebug()<<"WHITE FIG SIZE"<<pngWhiteFiguresVec.size();
        for(auto& whiteFig : pngWhiteFiguresVec){
                whiteFiguresVec.push_back(new FigureLabel(offsetX, 0, QPixmap(whiteFig), this));
                offsetX = offsetX + GlobX;
        }
        qDebug()<<"WHITE FIG VEC SIZE"<<whiteFiguresVec.size();
    }
    else{
        qDebug()<<"BLACK FIG SIZE"<<pngBlackFiguresVec.size();
        for(auto& blackFig : pngBlackFiguresVec){
                blackFiguresVec.push_back(new FigureLabel(offsetX, 0, QPixmap(blackFig), this));
                offsetX = offsetX + GlobX;
        }
        qDebug()<<"BLACK FIG VEC SIZE"<<blackFiguresVec.size();
    }
}


