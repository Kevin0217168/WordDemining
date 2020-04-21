#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPixmapItem>
class myItem;
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include "handler.h"

class myItem : public QGraphicsPixmapItem
{
public:
    myItem(QGraphicsTextItem* Text);
    void setPic(QString);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void Clicked();

    // 判断标志，为零时是未打开，为一时已打开，为二时已翻开
    int mark = 0;
    handler* hand;
    QGraphicsTextItem* Text;
};

#endif // MYITEM_H
