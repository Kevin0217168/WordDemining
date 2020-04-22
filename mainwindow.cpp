#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建场景类
    this->sc = new myScene;
    // 添加场景
    this->ui->graphicsView->setScene(this->sc);

    // 获取图元交互单例
    this->hand = handler::getInstance();
    // 更新单词数组
    QStringList* string = new QStringList;
    string->push_back("1");
    string->push_back("2");
    string->push_back("3");
    string->push_back("4");
    string->push_back("5");
    string->push_back("6");
    string->push_back("7");
    string->push_back("8");
    string->push_back("9");
    string->push_back("10");
    string->push_back("11");
    string->push_back("12");
    string->push_back("13");
    string->push_back("14");
    string->push_back("15");
    string->push_back("16");

    this->hand->UpdateWordList(string);
    // 绑定更新分数事件
    connect(this->hand, SIGNAL(UpdateScore(int)), this, SLOT(displayScore(int)));
    // 绑定‘不完整的’信号
    connect(this->hand, SIGNAL(Incompleted()), this, SLOT(MessageIncompleted()));

    // 绑定清零分数按钮
    connect(ui->reset_btn, SIGNAL(clicked()), this, SLOT(resetScore()));

    // 绑定'随机一个'按钮
    connect(ui->random_btn, SIGNAL(clicked()), this, SLOT(randomPicture()));

    // 将一数分为两数乘积算法
//    QList<QList<int>*>* resultList = this->hand->SpiltNum(18, 2);
//    for (int i = 0; i < resultList->size(); i++){
//        qDebug() << resultList->at(i)->at(0) << "*" << resultList->at(i)->at(1) << endl;
//    }
//    delete resultList;
    // 导入单词菜单
    connect(this->ui->daoru_act, SIGNAL(triggered()), this, SLOT(importWord()));

    // 游戏设置菜单
    connect(this->ui->set_act, SIGNAL(triggered()), this, SLOT(gameSetting()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event){
    int ret = QMessageBox::question(this, "退出", "您确定要退出吗？", "退出", "取消");
    if (ret == 1){
        event->ignore();
    }
}

void MainWindow::displayScore(int add){
    this->score += add;
    this->ui->lcdNumber->display(this->score);
}

void MainWindow::resetScore(){
    this->score = 0;
    this->ui->lcdNumber->display(this->score);
}

void MainWindow::MessageIncompleted(){
    QMessageBox::information(this, "注意", "注意哦，您还有未打开完全的方块\n请打开完全后再来哦!", "我知道啦!");
}

void MainWindow::randomPicture(){
    int ret = this->sc->randomPicture();
    if (ret){
        QMessageBox::information(this, "已完成游戏", "您太棒了，界面上已经没有需要打开的卡片啦\n请点击重玩或游戏设置来自定义吧!", "知道啦");
    }
}

void MainWindow::importWord(){
    system("notepad.exe Words.ini");
}

void MainWindow::gameSetting(){
    if (this->setting == NULL){
        this->setting = new GameSetting;
    }
    this->setting->exec();
}
