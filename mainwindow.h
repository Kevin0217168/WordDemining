#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myscene.h"
#include <QMessageBox>
#include "handler.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    myScene *sc;
    handler* hand;

    int score = 0;

public slots:
    // 刷新分数
    void displayScore(int);
    // 重置分数
    void resetScore();
    // 随机一个图片点击
    void randomPicture();
    // '不完整的'信号，弹窗提醒
    void MessageIncompleted();

protected:
    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
