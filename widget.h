
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QHBoxLayout>
#include<vehicle.h>
#include<vehicleduty.h>
#include<tips.h>
#include<showvehicle.h>
#include<feecalculate.h>
#include<fileoperation.h>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::widget *ui;
    //用来打开新窗口，在这里
    vehicleduty *newindow;
    tips *newindow2;
    ShowVehicle *newindow3;
    FeeCalculate *newindow4;
    FileOperation *newindow5;
private slots:
    //槽函数们
    void timerUpdata(void);
    void on_outButton_clicked();

signals:
    void Feeinquiries();
};

#endif // WIDGET_H
