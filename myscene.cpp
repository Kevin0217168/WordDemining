#include "myscene.h"

myScene::myScene(QWidget *parent) : QGraphicsScene(parent)
{
    this->item = new QList<QList<myItem*>*>;

    // 获取工具类(单例)
    this->hand = handler::getInstance();

    QList<myItem*>* list_x;
    for (int x = 0; x < this->hand->x; x++) {
        for (int y = 0; y < this->hand->y; y++) {
            // 创建文本图元
            QGraphicsTextItem* Text = new QGraphicsTextItem;
            // 设置文本图元在图片图元内
            Text->setPos(x*124 + 5, y*126 + 30);
            // 放置在场景中
            this->addItem(Text);
            // 设置层次为最高，使其一直在图元上方
            Text->setZValue(999);

            // 创建图片图元，将文本图元交由图片图元控制
            if (y == 0){
                list_x = new QList<myItem*>;
            }
            myItem* item = new myItem(Text);
            // 设置图片图元
            item->setPos(x*124, y*126);
            // 添加到列表
            list_x->append(item);
            // 将图元记录到未打开列表内
            this->hand->closePictureList->append(item);
            // 放置在场景中
            this->addItem(item);
            if (x == this->hand->x - 1){
                this->item->append(list_x);
            }
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
