#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取图元交互单例
    this->hand = handler::getInstance();
    this->hand->x = 4;
    this->hand->y = 4;

    // 更新单词数组
    QStringList* WordList = new QStringList;
    int ret = this->readFile(WordList);
    if (ret){
        return;
    }
    this->hand->UpdateWordList(WordList);
    QStringList* staticWordList = new QStringList;
    for (int i = 0; i < WordList->size(); i++){
        staticWordList->append(WordList->at(i));
    }
    this->hand->staticWordList = staticWordList;

    // 创建场景类
    this->sc = new myScene;
    // 添加场景
    this->ui->graphicsView->setScene(this->sc);

    // 绑定更新分数事件
    connect(this->hand, SIGNAL(UpdateScore(int)), this, SLOT(displayScore(int)));
    // 绑定‘不完整的’信号
    connect(this->hand, SIGNAL(Incompleted()), this, SLOT(MessageIncompleted()));

    // 绑定清零分数按钮
    connect(ui->reset_btn, SIGNAL(clicked()), this, SLOT(resetScore()));

    // 绑定'随机一个'按钮
    connect(ui->random_btn, SIGNAL(clicked()), this, SLOT(randomPicture()));

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

// 读取单词文件
int MainWindow::readFile(QStringList* WordList){
    // 读取单词文件
    QFile file("Words.ini");
    // 判断是否打开失败
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // 弹窗提醒
        QMessageBox::critical(this, "出大问题!",
             "找不到单词配置文件!\n请检查'Words.ini'文件是否被删除、移动、重命名\n请在安装目录下重新创建'Words.ini'文件以继续", "我知道啦!");
        return 1;
    }

    // 创建文本流对象
    QTextStream in(&file);
    // 设置编码
    in.setCodec("utf-8");
    // 读取单词
    while (!in.atEnd()) {
        QString line = in.readLine();
        line.replace("|", "\n");
        WordList->append(line);
    }

    // 判断单词列表是否为空
    if (WordList->size() == 1 && WordList->at(0) == ""){
        QMessageBox::information(this, "注意", "单词列表内没有数据!\n请先在菜单栏选择'选项'->'导入单词'来输入单词哦\n注意一个单词占一行哦", "我知道啦!");
        return 2;
    }
    return 0;
}

void MainWindow::gameSetting(){
    GameSetting setting;
    setting.exec();
}

void MainWindow::restart(){

}
