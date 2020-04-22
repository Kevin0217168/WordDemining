#include "gamesetting.h"
#include "ui_gamesetting.h"

GameSetting::GameSetting(QWidget *parent) :QDialog(parent), ui(new Ui::GameSetting)
{
    ui->setupUi(this);

    this->hand = handler::getInstance();

    this->initListView();
    this->init();

    // 确定按钮事件绑定
    connect(this->ui->ok_btn, SIGNAL(clicked()), this, SLOT(ok_btn_clicked()));

    // 取消按钮事件绑定
    connect(this->ui->cancel_btn, SIGNAL(clicked()), this, SLOT(cancel_btn_clicked()));

}

void GameSetting::initListView(){
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(*this->hand->staticWordList);
    this->ui->wordList->setModel(model);
    this->ui->wordList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void GameSetting::init(){
    // 设置单词总数
    QString zong = this->ui->zongshu_l->text();
    zong.replace(QString("NAN"), QString::number(this->hand->staticWordList->size()));
    this->ui->zongshu_l->setText(zong);

    // 设置矩形组合选择框
    // 将一数分为两数乘积算法
    QList<QList<int>*>* resultList = this->hand->SpiltNum(this->hand->staticWordList->size(), 2);

    QStringList list;
    for (int i = 0; i < resultList->size(); i++){
        list.append(QString::number(resultList->at(i)->at(0)) + QString(" * ") + QString::number(resultList->at(i)->at(1)));
    }
    this->ui->zhuhe_cbb->addItems(list);
    delete resultList;
}

GameSetting::~GameSetting()
{
    delete ui;
}

void GameSetting::ok_btn_clicked(){
    // 读取矩形组合
    QStringList zuhe = this->ui->zhuhe_cbb->currentText().split("*");
    // 判断是否反转
    if (this->ui->reverse_cb->isChecked()){
        // 交换数据
        zuhe.swapItemsAt(0, 1);
    }

    // 读取雷数
    QString lei = this->ui->lei_lin->text();

    // 读取加分项
    QList<QList<QString>*>* jiafen = new QList<QList<QString>*>;
    // 查找分数栏下的输入框
    QList<QLineEdit *> fen_shu = this->ui->fenshu_gb->findChildren<QLineEdit *>();
    QList<QString>* list;
    for (int i = 0; i < 5; i++){
        if (fen_shu.at(i)->text() != ""){
            list = new QList<QString>;
            list->append(fen_shu.at(i)->text());
            list->append(fen_shu.at(i+5)->text());
            jiafen->append(list);
        }
    }

    // 加分项组合(用于确认信息)
    QString queren;
    for (int i = 0; i < jiafen->size(); i++){
        queren += "+" + jiafen->at(i)->at(0) + "分";
        queren += "：";
        queren += jiafen->at(i)->at(1) + "个";
        queren += "\n";
    }

    QMessageBox::information(this, "确认", "最后确定一下哦，将保存设置啦!\n矩形组合：宽:" + zuhe.at(0) + " 高:" + zuhe.at(1) +
        "\n共有雷数：" + lei + "\n加分项：\n" + queren, "我再确认一下", "就是它了!");

    delete jiafen;
    delete list;
}

void GameSetting::cancel_btn_clicked(){
    int ret = QMessageBox::question(this, "退出", "你确定要退出吗?\n您所做的设置将不会保存!", "取消", "仍要退出");
    if (ret){
        this->close();
    }
}
