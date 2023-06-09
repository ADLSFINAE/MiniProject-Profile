#ifndef CHANGEPAWNWIDGET_H
#define CHANGEPAWNWIDGET_H
#include <QWidget>
#include <QPushButton>
#include "figurelabel.h"
#include "paramsNdefines.h"
using namespace GlobVal;

class ChangePawnWidget : public QWidget
{
    Q_OBJECT
public:
    ChangePawnWidget(bool color, QWidget* parent = nullptr);
private:
    QVector<FigureLabel*> blackFiguresVec;
    QVector<FigureLabel*> whiteFiguresVec;
    int offsetX = 0;
};

#endif // CHANGEPAWNWIDGET_H
