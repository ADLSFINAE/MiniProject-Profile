#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MainWindow : public QGraphicsView
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    ~MainWindow();

private:
    QGraphicsScene* scene;
    QGraphicsRectItem* rect;
    int i = 0;
};
#endif // MAINWINDOW_H
