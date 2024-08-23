
#include "widget.h"

#include <QApplication>
#include<ctime>
#include<cmath>
#include<iostream>
#include<QMap>

//核心:停车收费系统
//作用:对停留时间进行收费管理
//车辆类型:校内车辆/校外车辆
//收费规格:对于校内车辆不收取任何停车费；对于社会车辆，如果在校内停留时间小于30分钟则驶离时免费同行，大于30分钟则按3元/小时收取停车费，不足1小时按1小时收取。

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    std::time_t now = std::time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo,&now);
    std::cout << "The current date and time is: "
              << timeinfo.tm_year + 1900 << '-'
              << timeinfo.tm_mon + 1 << '-'
              << timeinfo.tm_mday << ' '
              << timeinfo.tm_hour << ':'
              << timeinfo.tm_min << ':'
              << timeinfo.tm_sec << std::endl;
    QDir::setCurrent(a.applicationDirPath());//添加这句即可正常使用相对路径

    w.show();
    return a.exec();
}
