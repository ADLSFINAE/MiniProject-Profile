#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QTextEdit>
#include <QLabel>


class ServerGui : public QWidget
{
    Q_OBJECT
public:
    ServerGui();

public slots:
    void addData(const QString& data);

private:
    QTextEdit* textEdit {nullptr};
    QLabel* label {nullptr};
};

#endif // SERVERGUI_H
