#include "handler.h"

// 构造函数
handler::handler(QObject *parent) : QObject(parent)
{
    closePictureList = new QList<myItem*>;
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

void handler::SendIncompleted(){
    // 发送信号
    emit Incompleted();
}

void handler::print()
{
    QList<int>* l = new QList<int>;
    l->append(a[1]);
    for (int i=2; i<=m; i++)
    {
        l->append(a[i]);
    }
    // 添加到结果列表
    this->resultList->append(l);
    //拆分结果个数自增
    totalKind++;
}

void handler::Split(int arrayIndex,int preDivisor,int newDivisor)
{
    //判断是否拆分结束，如果结束则输出该种拆分结果
    //拆分结束的条件是：
    //数组下标(即拆分的因数的个数)等于用户输入的拆分个数
    //并且当前因数大于前一个因数(即保证因数从小到大获取，避免重复)
    if (arrayIndex==m && newDivisor>=preDivisor)
    {
        //存储当前(新)的因数
        a[arrayIndex] = newDivisor;
        //输出当前拆分结果
        print(); //不是一直存储，是只要满足条件就打印
        //退出该函数
        return;
    }
    //如果拆分没有结束，则将当前(新)的因数继续拆分
    for (int i=preDivisor; i<=newDivisor; i++)
    {
        //如果当前因数能整除当前i值
        if (newDivisor%i == 0)
        {
            //再次获得因素
            a[arrayIndex]=i;
            //获得新的因数，继续拆分,递归
            Split(arrayIndex+1,i,newDivisor/i);
        }
    }
}


QList<QList<int>*>* handler::SpiltNum(int Num, int geshu)
{

    //计数器初始化
    totalKind=0;
    // 结果列表
    this->resultList = new QList<QList<int>*>;

    this->n = Num;
    this->m = geshu;
    for (int i=2; i<=Num; i++){
        //如果n能整除i
        if (Num%i==0)
        {
            //存储首个因数
            a[1]=i;
            //将整数除以因数i后得到的因数进行拆分
            Split(2,i,Num/i);
        }
    }
    return this->resultList;
}
