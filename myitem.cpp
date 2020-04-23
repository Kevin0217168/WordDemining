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
        this->Text->setPlainText(this->hand->randomWord());
        this->Text->setDefaultTextColor(Qt::blue);
        this->Text->setFont(QFont("consolas", 12));
        // 将自己设为未完全打开
        this->hand->incomplete = true;
    }
    // 打开一半
    else if (mark == 1){
        // 在未打开列表中把自己移除
        this->hand->closePictureList->removeOne(this);
        // 取消未完全打开标志
        this->hand->incomplete = false;
        // 获取打开后的情况
        QString qingkuang = this->hand->randomQingKuang();
        if (qingkuang == "Boom"){
            this->Text->setPlainText("");
            this->setPic(":/block/images/boom_block.png");
        }else if (qingkuang == "wu"){
            // 空
            this->Text->setPlainText("");
        }else{
            // 加分
            this->Text->setPlainText("+" + qingkuang + "分");
            this->Text->setDefaultTextColor(Qt::red);
            this->Text->setFont(QFont("consolas", 20));
            this->hand->addScore(qingkuang.toInt());
        }

    }
    mark += 1;
}
