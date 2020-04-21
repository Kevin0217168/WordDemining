#include "myitem.h"

myItem::myItem()
{
    this->setPixmap(QPixmap(":/block/images/close_block.png"));
    this->hand = handler::getInstance();
}

void myItem::setPic(QString Path){
    this->setPixmap(QPixmap(Path));
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (mark == 0){
        this->setPic(":/block/images/open_block.png");
        this->hand->addScore(1);
    }else if (mark == 1){

    }

    mark += 1;
}
