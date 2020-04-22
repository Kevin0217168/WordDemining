#include "myscene.h"

myScene::myScene(QWidget *parent) : QGraphicsScene(parent)
{
    // 获取工具类(单例)
    this->hand = handler::getInstance();

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            // 创建文本图元
            QGraphicsTextItem* Text = new QGraphicsTextItem;
            // 设置文本图元在图片图元内
            Text->setPos(x*124 + 5, y*126 + 50);
            // 放置在场景中
            this->addItem(Text);
            // 设置层次为最高，使其一直在图元上方
            Text->setZValue(999);

            // 创建图片图元，将文本图元交由图片图元控制
            this->item[y][x] = new myItem(Text);
            // 设置图片图元
            this->item[y][x]->setPos(x*124, y*126);
            // 将图元记录到未打开列表内
            this->hand->closePictureList->append(this->item[y][x]);
            // 放置在场景中
            this->addItem(this->item[y][x]);
        }
    }
}

int myScene::randomPicture(){
    if (!this->hand->closePictureList->size()){
        return 1;
    }
    int index = this->hand->RandomNum(0, this->hand->closePictureList->size());
    this->hand->closePictureList->at(index)->Clicked();
    return 0;
}
