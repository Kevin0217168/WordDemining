#include "myitem.h"

myItem::myItem(QGraphicsTextItem* Text)
{
    this->Text = Text;
    this->setPixmap(QPixmap(":/block/images/close_block.png"));
    this->hand = handler::getInstance();
}

void myItem::setPic(QString Path){
    this->setPixmap(QPixmap(Path));
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "鼠标事件";
    this->Clicked();
    event->ignore();
}

void myItem::Clicked(){
    // 当前为未打开
    if (mark == 0){
        // 有其他方块不完整打开时
        if (this->hand->incomplete){
            // 不允许打开，发送信号交由主窗口弹窗提示
            this->hand->SendIncompleted();
            return;
        }
        this->setPic(":/block/images/open_block.png");
        qDebug() << "图片设置成功";
        this->hand->addScore(1);
        qDebug() << "分数添加成功";
        this->Text->setPlainText(this->hand->randomWord());
        qDebug() << "单词添加成功";
        this->Text->setDefaultTextColor(Qt::red);
        // 将自己设为未完全打开
        this->hand->incomplete = true;
    }
    // 打开一半
    else if (mark == 1){
        this->Text->setPlainText("");
        // 在未打开列表中把自己移除
        this->hand->closePictureList->removeOne(this);
        // 取消未完全打开标志
        this->hand->incomplete = false;
    }
    mark += 1;
}
