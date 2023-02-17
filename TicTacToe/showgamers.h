#ifndef SHOWGAMERS_H
#define SHOWGAMERS_H
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

class ShowGamers : public QGraphicsView
{
  Q_OBJECT
public:
  ShowGamers();
  void changePixmap(QPixmap pixmap);
public slots:
  void changePixmapForPlayer(QString string, ShowGamers* view);
private:
  QGraphicsScene* scene{nullptr};
  QGraphicsPixmapItem* m_pixmap{nullptr};
};

#endif // SHOWGAMERS_H
