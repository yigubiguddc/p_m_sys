#ifndef VEHICLEDUTY_H
#define VEHICLEDUTY_H

#include <QWidget>
#include<QString>
#include<QDebug>
#include<QInputDialog>

#include <QRegularExpressionValidator>
#include<vehicle.h>
#include<header.h>

namespace Ui {
class vehicleduty;
}

class vehicleduty : public QWidget
{
    Q_OBJECT

public:
    explicit vehicleduty(QWidget *parent = nullptr);
    void VehicleRecording();
    ~vehicleduty();

private:
    //用于界面显示
    Ui::vehicleduty *ui;
    Vehicle car;        //车辆类


protected:
    void closeEvent(QCloseEvent *event);//关闭事件，虚函数重写

signals:
    void back();
    void hasbeenclicked();
private slots:
    void on_idinButton_clicked();//确认车牌号
    void on_identityButton_clicked();//确认车辆信息（校内/校外）
    void on_checkButton_clicked();//调试时用到的检查qDebug内容
    void on_VehicleInButton_clicked();//车辆进入按钮
    void on_VehicleOutButton_clicked();//车辆离校按钮
};

#endif // VEHICLEDUTY_H
