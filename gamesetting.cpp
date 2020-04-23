#include "gamesetting.h"
#include "ui_gamesetting.h"

GameSetting::GameSetting(QWidget *parent) :QDialog(parent), ui(new Ui::GameSetting)
{
    ui->setupUi(this);

    this->hand = handler::getInstance();

    // 重新读取单词文件
    QStringList* WordList = new QStringList;
    int ret = this->hand->readFile(WordList);
    // 检查是否读取失败
    if (ret){
        if (ret == 1){
            QMessageBox::critical(this, "出大问题!",
                 "找不到单词配置文件!\n请检查'Words.ini'文件是否被删除、移动、重命名\n请在安装目录下重新创建'Words.ini'文件以继续", "我知道啦!");

        }else if (ret == 2){
            QMessageBox::information(this, "注意", "单词列表内没有数据!\n请先在菜单栏选择'选项'->'导入单词'来输入单词哦\n注意一个单词占一行哦", "我知道啦!");
        }
        delete WordList;
        this->close();
    }
    // 释放旧空间
    delete this->hand->staticWordList;
    // 添加新数据
    this->hand->staticWordList = WordList;


    // 初始化单词列表显示
    this->initListView();
    // 初始化其他显示
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

    int ret = QMessageBox::information(this, "确认", "最后确定一下哦，将保存设置啦!\n矩形组合：宽:" + zuhe.at(0) + " 高:" + zuhe.at(1) +
        "\n共有雷数：" + lei + "\n加分项：\n" + queren, "我再确认一下", "就是它了!");
    if (!ret){
        return;
    }

    // 写入配置文件
    QFile file("setting.ini");
    // 打开文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, "出大问题!",
             "找不到单词配置文件!\n请检查'setting.ini'文件是否被删除、移动、重命名\n请在安装目录下重新创建'setting.ini'文件以继续", "我知道啦!");
        delete jiafen;
        delete list;
        this->close();
    }

    QTextStream in(&file);
    // 设置编码
    in.setCodec("utf-8");

    // 添加单词
    for (int i = 0; i < this->hand->staticWordList->size(); i++){
        QString word = this->hand->staticWordList->at(i);
        word.replace("\n", "|");
        in << word << endl;
    }
    in << "======" << endl;

    // 添加长宽
    in << zuhe.at(0) << endl << zuhe.at(1) << endl;
    // 添加雷数
    in << lei << endl;

    // 添加加分项
    for (int i = 0; i < jiafen->size(); i++){
        in << jiafen->at(i)->at(0) << "|" << jiafen->at(i)->at(1) << endl;
    }
    file.close();

    delete jiafen;
    delete list;
    // 发送信号，告诉主窗口重新读取配置文件
    emit Restart();
    this->close();
}

void GameSetting::cancel_btn_clicked(){
    int ret = QMessageBox::question(this, "退出", "你确定要退出吗?\n您所做的设置将不会保存!", "取消", "仍要退出");
    if (ret){
        this->close();
    }
}
