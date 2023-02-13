#ifndef WWE_H
#define WWE_H
#include <QPushButton>
#include <QLCDNumber>
#include <QMouseEvent>

class Calculator : public QWidget{
    Q_OBJECT
public:
    Calculator(QWidget* parent = 0);
public slots:
    void enteringNumber();
    void plusEvent();
    void clearEvent();
signals:
    void plusSignal();
private:
    void createWidgets();

    QPushButton* pushButton[9];
    QPushButton* pushButtonPlus;
    QPushButton* pushButtonC;
    QLCDNumber* lcdNumber;
    QString mainNum;
    QString cacheNum;
    int sum = 0;
};

#endif // WWE_H
