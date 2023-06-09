#ifndef FIGURELABEL_H
#define FIGURELABEL_H
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include "paramsNdefines.h"
using namespace GlobVal;

class FigureLabel : public QLabel{
    Q_OBJECT
public:
    FigureLabel(int x, int y, QString pixmap, bool color, QWidget *parent);
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
signals:
    void createSelectedFigure(QString pixmapName, bool color);
private:
    bool color;
    QString pixmapName;
};


#endif // FIGURELABEL_H
