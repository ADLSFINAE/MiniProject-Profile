#include "figurelabel.h"
#include <QDebug>
FigureLabel::FigureLabel(int x, int y, QPixmap pixmap, QWidget *parent)
{
    this->setParent(parent);
    this->setGeometry(x, y, 80, 80);
    this->setPixmap(pixmap);
    qDebug()<<"WAS CALLED BY"<<x<<y;
}

void FigureLabel::mousePressEvent(QMouseEvent *ev)
{
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::yellow);

    this->setAutoFillBackground(true);
    this->setPalette(sample_palette);
}

void FigureLabel::mouseReleaseEvent(QMouseEvent *ev)
{

}

void FigureLabel::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug()<<QCursor::pos()<<QLabel::mapFromGlobal(QCursor::pos());;
}
