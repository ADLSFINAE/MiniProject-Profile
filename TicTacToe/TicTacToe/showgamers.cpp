#include "showgamers.h"
#include <QPixmap>
ShowGamers::ShowGamers()
{
  m_pixmap = new QGraphicsPixmapItem();
  m_pixmap->setPixmap(QPixmap(":/player.png"));
  m_pixmap->setPos(0, 0);

  scene = new QGraphicsScene;
  scene->setSceneRect(0, 0, 60, 60);
  scene->addItem(m_pixmap);

  this->setScene(scene);
  this->setSceneRect(0, 0, 60, 60);
  this->setStyleSheet("QScrollBar {height:0px;}");
  this->setStyleSheet("QScrollBar {width:0px;}");
  this->show();
}

void ShowGamers::changePixmap(QPixmap pixmap)
{
  pixmap = pixmap.scaled(60, 60,Qt::IgnoreAspectRatio);
  m_pixmap->setPixmap(pixmap);
}

void ShowGamers::changePixmapForPlayer(QString string, ShowGamers* view)
{
  QPixmap pixmap = (QPixmap(string));
  pixmap = pixmap.scaled(60, 60,Qt::IgnoreAspectRatio);
  view->m_pixmap->setPixmap(pixmap);
}
