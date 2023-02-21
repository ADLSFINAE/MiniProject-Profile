#include "server.h"
#include "client.h"
#include "servergui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server server;
    ServerGui gui;

    Client client;
    Client client2;

    QObject::connect(&server, &Server::dataReceived, &gui, &ServerGui::addData);

    gui.show();
    client.show();
    client2.show();

    return a.exec();
}
