#include "myscene.h"

myScene::myScene(QWidget *parent) : QGraphicsScene(parent)
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            this->item[y][x] = new myItem;
            this->item[y][x]->setPos(x*124, y*126);
            this->addItem(this->item[y][x]);
        }
    }
    //this->item[2][3]->setPic(":/block/images/open_block.png");
}
