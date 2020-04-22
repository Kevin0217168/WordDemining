#include "gamesetting.h"
#include "ui_gamesetting.h"

GameSetting::GameSetting(QWidget *parent) :QDialog(parent), ui(new Ui::GameSetting)
{
    ui->setupUi(this);

    // 确定按钮事件绑定
    connect(this->ui->ok_btn, SIGNAL(clicked()), this, SLOT(ok_btn_clicked()));

    // 取消按钮事件绑定
    connect(this->ui->cancel_btn, SIGNAL(clicked()), this, SLOT(cancel_btn_clicked()));
}

GameSetting::~GameSetting()
{
    delete ui;
}

void GameSetting::ok_btn_clicked(){

}

void GameSetting::cancel_btn_clicked(){
    int ret = QMessageBox::question(this, "退出", "你确定要退出吗?\n您所做的设置将不会保存!", "取消", "仍要退出");
    if (ret){
        this->close();
    }
}
