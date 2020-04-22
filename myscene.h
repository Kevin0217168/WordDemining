#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "myitem.h"
#include "handler.h"
#include <QList>

class myScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScene(QWidget *parent = nullptr);
    int randomPicture();

    handler* hand;

signals:

public slots:

private:
    QList<QList<myItem*>*>* item;
};

#endif // MYSCENE_H
