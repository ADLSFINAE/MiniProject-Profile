#include "showgamers.h"

ShowGamers::ShowGamers()
{
  scene = new QGraphicsScene;
  this->setScene(scene);
  m_pixmap = new QGraphicsPixmapItem();
  scene->setSceneRect(0, 0, 60, 60);
  scene->addItem(m_pixmap);
  m_pixmap->setPixmap(QPixmap(":/player.png"));
  m_pixmap->setPos(0, 0);
  this->setSceneRect(0, 0, 60, 60);
  this->setStyleSheet("QScrollBar {height:0px;}");
  this->setStyleSheet("QScrollBar {width:0px;}");
  this->show();
}

void ShowGamers::changePixmap(QPixmap pixmap)
{
  m_pixmap->setPixmap(pixmap);
}

void ShowGamers::changePixmapForPlayer(QString string)
{
  m_pixmap->setPixmap(QPixmap(string));
}
