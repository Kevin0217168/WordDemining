#include "handler.h"

// 构造函数
handler::handler(QObject *parent) : QObject(parent)
{

}

// 析构函数
handler::~handler(){
    // 释放单词列表
    delete this->WordList;
}

// 创建唯一的单例
handler* handler::hand = new handler;

// 获得单例
handler* handler::getInstance(){
    return hand;
}

// 添加分数
void handler::addScore(int score){
    // 发送信号，让主函数更新分数
    emit UpdateScore(score);
}

// 更新单词列表
void handler::UpdateWordList(QStringList * WordList){
    this->WordList = WordList;
}

// 获得随机数
int handler::RandomNum(int min_num = 0, int max_num = 32767)
{
    if (min_num > max_num)      //如果将区间下限和上限写反，则交换
    {
        swap(min_num,max_num);
    }
    int interval_num = max_num - min_num;
    if (interval_num <= 0)
    {
        return 0;
    }
    else if (interval_num < 32767)
    {
        return min_num + (rand() % interval_num);
    }
    else
    {
        return min_num + int(((rand() % 32767) * 1.0 / 32767) * interval_num);
    }
}

// 随机一个单词
QString handler::randomWord(){
    // 随机一个索引
    int index = this->RandomNum(0, this->WordList->size() - 1);
    // 获取到该索引的数据
    QString result = this->WordList->at(index);
    // 反手炸掉指挥部，防止重复
    this->WordList->removeAt(index);
    // 返回结果
    return result;
}
