#ifndef FIGURELABEL_H
#define FIGURELABEL_H
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include "figures/king.h"
#include "figures/horse.h"
#include "figures/queen.h"
#include "figures/elephant.h"
#include "figures/rook.h"
#include "figures/figure.h"
#include "paramsNdefines.h"
using namespace GlobVal;

class FigureLabel : public QLabel{
    Q_OBJECT
public:
    FigureLabel(int x, int y, QString pixmap, bool color, QWidget *parent);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
signals:
    void createSelectedFigure(Figure* fig);
private:
    bool color;
    QString pixmapName;
    Figure* fig;
};


#endif // FIGURELABEL_H
