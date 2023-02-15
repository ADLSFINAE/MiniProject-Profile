#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    Test();

signals:
    void sig();

public slots:
    void sigSlot();
};

#endif // TEST_H
