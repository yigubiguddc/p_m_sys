
#include "vehicle.h"

//构造函数
Vehicle::Vehicle()
{
    CarIdentity =   1;      //默认是校内车辆
    CarId       =   "\0";
    //初始化为对象创立时间
    EnterTime = QDateTime::currentDateTime();
    ExitTime  = QDateTime::currentDateTime();
    strEnterTime=   "\0";
    strExitTime =   "\0";
    fee = 0;
}


void Vehicle::SetCarIdentity(bool judge)
{
    CarIdentity = judge;
}


void Vehicle::setEnterTime(QDateTime& time)
{
    EnterTime = time;
}

void Vehicle::setExitTime(QDateTime& time)
{
    ExitTime = time;
}

//检验赋值是否成功
void Vehicle::issuccessfulsetcaridentity()
{
    if(CarIdentity == true)
    {
        qDebug()<<"True";
    }
    else
    {
        qDebug()<<"False";
    }
}

void Vehicle::setCarId(QString Carid)
{
    CarId = Carid;
}

QString Vehicle::getCarId()
{
    return CarId;
}


//QDateTime类型数据,可以直接计算时间差
QDateTime Vehicle::getEnterTime()
{
    return EnterTime;
}

QDateTime Vehicle::getExitTime()
{
    return ExitTime;
}

//在类外获得进入和出校的时间的字符串形式
QString Vehicle::getStrEntertime()
{
    //strEnterTime = EnterTime.toString(Qt::ISODate);
    strEnterTime = EnterTime.toString("yyyy-MM-dd hh:mm:ss");

    return strEnterTime;
}

QString Vehicle::getStrExitTime()
{
    //strExitTime = ExitTime.toString(Qt::ISODate);
    strExitTime = ExitTime.toString("yyyy-MM-dd hh:mm:ss");
    return strExitTime;
}

bool Vehicle::getCarIdentity()
{
    //true---是校内车辆   false---不是校内车辆
    if(CarIdentity)
    {
        return true;
    }
    return false;
}

QString Vehicle::getCarIdentityStr()
{
    if(CarIdentity)
    {
        return "校内车辆";
    }
    else
    {
        return "校外车辆";
    }
}

//显示车辆信息
void Vehicle::Show()
{
    qDebug()<<CarId<<" "<<getStrEntertime()<<" "<<getStrExitTime();
}

//对于费用，在手动输入车牌并记录的模式中在save按钮被按下之后执行Feecalculate，所以fee是被赋值过的
//在文件操作批量输入的过程中也有相应的处理方式，所以fee都是赋值过了的
void Vehicle::FeeCalculate()
{
    //是校内车辆
    if(CarIdentity)
    {
        fee = 0;
        return;         //函数结束
    }
    //下面就是CarIdentity为false(非校内车辆)
    //小于30分钟则驶离时免费同行，大于30分钟则按3元/小时收取停车费，不足1小时按1小时收取
    double intervalTime = EnterTime.secsTo(ExitTime);   //计算时间差是 早的时间到晚的时间，不然得出的结果会是负数
    double intervalHour = intervalTime / 3600;          //转换成小时数,用浮点数

    if(intervalHour<0.5)
    {
        fee = 0;
    }
    else if(intervalHour>0.5||((intervalHour-0.5)<1e-9))
    {
        //浮点数在等号判断时需要这样操作
        //表达大于或等于0.5小时
        if(intervalHour<1||((intervalHour)-1)<1e-9)
        {
            fee = 3;
        }
        else
        {
            fee = 3 * intervalHour;
        }
    }
    return;
}


double Vehicle::getFee()
{
    return fee;
}
