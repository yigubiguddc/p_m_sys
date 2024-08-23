#ifndef SHOWVEHICLE_H
#define SHOWVEHICLE_H
#include<QIcon>
#include <QWidget>
#include<QPushButton>
#include<QMessageBox>
//配套食用，基于MVC设计模式设计的，可以理解为Model是相片，QTableView作为相框，二者结合显示图像
//M(Model)是QStandardItemModel数据模型，不能单独显示出来。V(view)是指QTableView视图，要来显示数据模型，C(controllor)控制在Qt中被弱化，与View合并到一起
#include<QTableView>
#include<QTableWidget>

#include<QStandardItemModel>
#include<QHBoxLayout>

//设置背景图片
#include<QPixmap>
#include<QPainter>

//这里时为了把vehicle中的数据遍历并且输出
#include<header.h>



namespace Ui {
class ShowVehicle;
}

class ShowVehicle : public QWidget
{
    Q_OBJECT

public:
    explicit ShowVehicle(QWidget *parent = nullptr);
    void TableView();
    void adding();
    void clearAll();
    ~ShowVehicle();

private:
    Ui::ShowVehicle *ui;
    //如果要添加新的功能这么做会比较方便
    QStandardItemModel *model;

protected:
    void paintEvent(QPaintEvent *paint);
    void closeEvent(QCloseEvent *event);
};

#endif // SHOWVEHICLE_H
