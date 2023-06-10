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
}

void FigureLabel::mousePressEvent(QMouseEvent *ev)
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::yellow);

    this->setAutoFillBackground(true);
    this->setPalette(sample_palette);
    emit createSelectedFigure(pixmapName, color);
}

void FigureLabel::mouseReleaseEvent(QMouseEvent *ev)
{

}

void FigureLabel::mouseMoveEvent(QMouseEvent *ev)
{

}
