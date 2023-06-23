#include "coreElems/ChangePawnElems/figurelabel.h"
#include <QEvent>
#include <QApplication>
#include <QDebug>
#include <QScreen>
FigureLabel::FigureLabel(int x, int y, QString pixmapName, bool color, QWidget *parent)
{
    this->setParent(parent);
    this->setGeometry(x, y, GlobX, GlobY);
    this->pixmapName = pixmapName;
    this->color = color;
    this->setPixmap(QPixmap(pixmapName));
    if(pixmapName == pngWhiteElephant){fig = new Elephant(x, y, true);}
    else if(pixmapName == pngBlackElephant){fig = new Elephant(x, y, false);}
    else if(pixmapName == pngWhiteHorse){fig = new Horse(x, y, true);}
    else if(pixmapName == pngBlackHorse){fig = new Horse(x, y, false);}
    else if(pixmapName == pngWhiteRook){fig = new Rook(x, y, true);}
    else if(pixmapName == pngBlackRook){fig = new Rook(x, y, false);}
    else if(pixmapName == pngWhiteQueen){fig = new Queen(x, y, true);}
    else{fig = new Queen(x, y, false);}
}

void FigureLabel::mousePressEvent(QMouseEvent *event)
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::yellow);

    this->setAutoFillBackground(true);
    this->setPalette(sample_palette);
    emit createSelectedFigure(fig);
}

void FigureLabel::mouseReleaseEvent(QMouseEvent *event)
{

}

void FigureLabel::mouseMoveEvent(QMouseEvent *event)
{

}
