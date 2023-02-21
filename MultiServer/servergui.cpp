#include "servergui.h"

#include <QVBoxLayout>

ServerGui::ServerGui()
{
    this->setFixedSize(400, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    label = new QLabel("Server", this);
    label->setFont(QFont("Arial", 50));

    layout->addWidget(label, 1);
    layout->addWidget(textEdit, 5);
}

void ServerGui::addData(const QString& data)
{
    textEdit->append(data);
}
