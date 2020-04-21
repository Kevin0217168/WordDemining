#include "handler.h"

handler::handler(QObject *parent) : QObject(parent)
{

}

handler* handler::hand = new handler;

handler* handler::getInstance(){
    return hand;
}

void handler::addScore(int score){
    // 发送信号，让主函数更新分数
    emit UpdateScore(score);
}
