#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include "myitem.h"

class myScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myScene(QWidget *parent = nullptr);

signals:

public slots:

private:
    myItem * item[4][4];
};

#endif // MYSCENE_H
