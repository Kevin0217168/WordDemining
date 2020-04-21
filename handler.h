#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

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

private:
    explicit handler(QObject *parent = nullptr);

signals:
    // 更新分数信号
    void UpdateScore(int);

private:
    // 唯一的实例
    static handler *hand;

};

#endif // HANDLER_H
