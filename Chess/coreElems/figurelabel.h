#ifndef FIGURELABEL_H
#define FIGURELABEL_H
#include <QLabel>
#include <QWidget>
#include <QPixmap>

class FigureLabel : public QLabel{
    Q_OBJECT
public:
    FigureLabel(int x, int y, QPixmap pixmap, QWidget* parent);
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
};


#endif // FIGURELABEL_H
