#ifndef VEHICLE_H
#define VEHICLE_H
#include<QString>
#include<QDateTime>
#include<QDebug>
#include<QMessageBox>
#include <QPlainTextEdit>
#include<QDialog>
#include<QList>
#include<QMap>

class Vehicle
{
public:
    Vehicle();
    void SetCarIdentity(bool judge);                //设置车辆身份(是否为校内车辆)
    bool getCarIdentity();                          //获取身份
    QString getCarIdentityStr();                    //获取文字
    void issuccessfulsetcaridentity();              //test
    void setCarId(QString Carid);                   //设置车牌
    QString getCarId();                             //获取车牌
    void setEnterTime(QDateTime& time);             //设置进入时间
    QDateTime getEnterTime();                       //获取进入时间
    void setExitTime(QDateTime& time);              //设置出校时间
    QDateTime getExitTime();                        //获取出校时间
    //获取字符串形式的入校和出校时间(用来显示,要进行操作肯定还是用QDateTime)
    QString getStrEntertime();                      //获取入校时间（字符串）
    QString getStrExitTime();                       //获取出校时间（字符串）
    void FeeCalculate();                            //计算费用
    double getFee();                                //获取所需费用
    void Show();                                    //qDebug时使用，输出车辆数据

private:
    bool CarIdentity;       //是或者否  是校内车辆--免费   不是校内车辆--按照流程收费
    QString CarId;          //车牌号，方便存储数据
    QDateTime EnterTime;    //进入时间
    QDateTime ExitTime;     //出校时间
    //转化成str吧，方便使用
    QString strEnterTime;
    QString strExitTime;
    double fee;
};

#endif // VEHICLE_H
