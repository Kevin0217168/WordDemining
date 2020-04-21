#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "myitem.h"
#include "handler.h"

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
    myItem * item[4][4];
};

#endif // MYSCENE_H
