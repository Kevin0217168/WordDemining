#include "gamesetting.h"
#include "ui_gamesetting.h"

GameSetting::GameSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSetting)
{
    ui->setupUi(this);
}

GameSetting::~GameSetting()
{
    delete ui;
}
