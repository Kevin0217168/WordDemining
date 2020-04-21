#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建场景类
    this->sc = new myScene;
    // 添加场景
    this->ui->graphicsView->setScene(this->sc);

    // 获取图元交互单例
    handler* hand = handler::getInstance();
    // 绑定更新分数事件
    connect(hand, SIGNAL(UpdateScore(int)), this, SLOT(displayScore(int)));

    // 绑定清零分数按钮
    connect(ui->reset_btn, SIGNAL(clicked()), this, SLOT(resetScore()));
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
