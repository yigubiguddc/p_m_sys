
#ifndef HEADER_H
#define HEADER_H
#include<QString>
#include<QMap>
#include<vehicle.h>
//由于使用QMap作为容器，QMap基于红黑树实现，容器内的元素本身就根据车牌(键--Key)的信息进行了排序，因此展示的时候也会是有序的形式
extern QMap<QString,Vehicle> vehicle;
#endif // HEADER_H
