#ifndef GAMESETTING_H
#define GAMESETTING_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

namespace Ui {
class GameSetting;
}

class GameSetting : public QDialog
{
    Q_OBJECT

public:
    explicit GameSetting(QWidget *parent = nullptr);
    ~GameSetting();

private:
    Ui::GameSetting *ui;

public slots:
    void ok_btn_clicked();
    void cancel_btn_clicked();

};

#endif // GAMESETTING_H
