#include "server.h"
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Server server;
  Client client;
  server.show();
  client.show();
  return a.exec();
}
