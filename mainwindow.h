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

    int score = 0;

public slots:
    void displayScore(int);
    void resetScore();

protected:
    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
