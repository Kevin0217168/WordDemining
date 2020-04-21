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
    if (mark == 0){
        this->setPic(":/block/images/open_block.png");
        this->hand->addScore(1);
        this->Text->setPlainText(this->hand->randomWord());
        this->Text->setDefaultTextColor(Qt::red);
    }else if (mark == 1){
        this->Text->setPlainText("");
    }

    mark += 1;
}
