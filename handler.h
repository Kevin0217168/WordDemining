#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
class handler;

#include <stdlib.h>
#include <QStringList>
#include <QList>
#include "myitem.h"

using namespace std;

// 这是一个单例，用于在图元与主窗口交互更新分数
// 只能创建一个对象
class handler : public QObject
{
    Q_OBJECT
public:
    // 获得单例
    static handler* getInstance();
    // 加分
    void addScore(int score);
    // 更新单词列表
    void UpdateWordList(QStringList *);
    // 获取随机数
    int RandomNum(int, int);
    // 在单词列表中随机一个
    QString randomWord();

    // 单词列表
    QStringList* WordList;
    // 是否出现打开一半的情况
    bool incomplete = false;
    // '不完整的'信号发送函数
    void SendIncompleted();
    // 未打开的图片列表
    QList<myItem*>* closePictureList;
private:
    // 卑微的构造函数
    explicit handler(QObject *parent = nullptr);
    // 卑微的析构函数
    ~handler();

signals:
    // 更新分数信号
    void UpdateScore(int);
    // 方块'不完整的'信号
    void Incompleted();

private:
    // 唯一的实例
    static handler *hand;

};

#endif // HANDLER_H
