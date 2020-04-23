#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取图元交互单例
    this->hand = handler::getInstance();

    // 初始化
    this->Init();

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

    // 绑定重玩按钮
    connect(this->ui->replay_btn, SIGNAL(clicked()), this, SLOT(restart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init(){
    // 读取配置文件
    QStringList* WordList = new QStringList;
    int* lei = new int;
    QList<int>* buju = new QList<int>;
    QList<QList<int>*>* fen = new QList<QList<int>*>;

    int ret = this->readSettingFile(WordList, lei, buju, fen);
    if (ret){
        return;
    }
    // 更新单词列表
    this->hand->UpdateWordList(WordList);
    // 复制一份静态单词列表
    QStringList* staticWordList = new QStringList;
    for (int i = 0; i < WordList->size(); i++){
        staticWordList->append(WordList->at(i));
    }
    this->hand->staticWordList = staticWordList;

    // 更新矩形布局
    this->hand->x = buju->at(0);
    this->hand->y = buju->at(1);
    delete buju;

    // 创建打开后的列表
    QStringList* opened_block = new QStringList;
    for (int i = 0; i < *lei; i++){
        opened_block->append("Boom");
    }
    for (int i = 0; i < fen->size(); i++){
        for (int x = 0; x < fen->at(i)->at(1); x++){
            opened_block->append(QString::number(fen->at(i)->at(0)));
        }
    }
    int shengyu = this->hand->x * this->hand->y - opened_block->size();
    for (int i = 0; i < shengyu; i++){
        opened_block->append("wu");
    }
    this->hand->opened_block = opened_block;
    delete fen;
    delete lei;

    // 创建场景类
    this->sc = new myScene;
    // 添加场景
    this->ui->graphicsView->setScene(this->sc);
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
int MainWindow::readSettingFile(QStringList* WordList, int* lei, QList<int>* buju, QList<QList<int>*>* fen){
    // 读取单词文件
    QFile file("setting.ini");
    // 判断是否打开失败
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // 弹窗提醒
        QMessageBox::critical(this, "出大问题!",
             "找不到单词配置文件!\n请检查'setting.ini'文件是否被删除、移动、重命名\n请在安装目录下重新创建'setting.ini'文件以继续", "我知道啦!");
        return 1;
    }

    // 创建文本流对象
    QTextStream in(&file);
    // 设置编码
    in.setCodec("utf-8");
    // 读取单词
    QString line;
    line = in.readLine();
    while (line != "======") {
        line.replace("|", "\n");
        WordList->append(line);
        line = in.readLine();
    }

    // 判断单词列表是否为空
    if (WordList->size() == 1 && WordList->at(0) == ""){
        QMessageBox::information(this, "注意", "单词列表内没有数据!\n请先在菜单栏选择'选项'->'导入单词'来输入单词哦\n注意一个单词占一行哦", "我知道啦!");
        return 2;
    }

    // 读取矩形组合(连读两行)
    buju->append(in.readLine().toInt());
    buju->append(in.readLine().toInt());
    // 读取雷数
    *lei = in.readLine().toInt();

    // 读取加分项
    while (!in.atEnd()) {
        QStringList list = in.readLine().split("|");
        QList<int>* i_list = new QList<int>;
        i_list->append(list.at(0).toInt());
        i_list->append(list.at(1).toInt());
        fen->append(i_list);
    }

    file.close();
    return 0;
}

void MainWindow::gameSetting(){
    GameSetting setting;
    connect(&setting, SIGNAL(Restart()), this, SLOT(restart()));
    setting.exec();
    disconnect(&setting, SIGNAL(Restart()), this, SLOT(restart()));
}

void MainWindow::restart(){
    // 垃圾清理带师
    delete this->hand->WordList;
    delete this->hand->staticWordList;
    delete this->hand->opened_block;
    delete this->sc;

    // 数据恢复带师
    this->hand->incomplete = false;
    this->hand->closePictureList->clear();
    this->score = 0;

    // 显示刷新带师
    this->ui->lcdNumber->display(this->score);

    // 调用构造函数重新开始
    this->Init();
}
