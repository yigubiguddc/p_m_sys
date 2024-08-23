#ifndef FEECALCULATE_H
#define FEECALCULATE_H

#include <QWidget>
#include<QPushButton>
#include<QString>
#include<QMessageBox>
#include<QDebug>
#include<QTextBrowser>
#include <QTextCharFormat>
#include<QPixmap>
//要使用容器的文件都需要包含这个头文件
#include<header.h>


namespace Ui {
class FeeCalculate;
}

//用于查询单独车辆的基本信息和费用
class FeeCalculate : public QWidget
{
    Q_OBJECT

public:
    explicit FeeCalculate(QWidget *parent = nullptr);
    void getCarid();
    void refreshText();
    ~FeeCalculate();
protected:
    void closeEvent(QCloseEvent *event);


private:
    Ui::FeeCalculate *ui;

signals:
    void back();
};

#endif // FEECALCULATE_H
