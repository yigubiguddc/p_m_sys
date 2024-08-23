#include "widget.h"
#include "ui_widget.h"
#include<QFont>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QLabel>
#include<iostream>
#include<QMap>
#include<header.h>

//时钟间隔时间
#define INTERVAL 1000


//extern 显式的说明了该存储空间是在程序的其他地方分配的，在文件中其他位置或者其他文件中寻找a这个变量



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
    //标题和图标设置
    setWindowTitle("中南民族大学停车收费系统");
    setWindowIcon(QIcon(":/picture/3.jpg"));


    //实现整体透明,可控度0 --- 1   setWindowOpacity(double value)
    setWindowOpacity(0.88);

    //实例化一个QTimer对象作为计时器，计时间隔时间为1s
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdata()));
    //void start(int msec);参数为定时器时间间隔，单位毫秒,作用是启动定时器
    timer->start(INTERVAL);


    //QPixmap pix = QPixmap("D:\\Qtprojects\\studying\\picture\\2.jpg");
    QPixmap pix = QPixmap(":/picture/2.jpg").scaled(this->ui->label->size());
    this->ui->label->setPixmap(pix);


    //所有窗口的进入和返回的信号和槽函数
    this->newindow = new vehicleduty;
    connect(ui->inButton,&QPushButton::clicked,this,[=](){
        this->hide();
        this->newindow->show();
    });
    connect(this->newindow,&vehicleduty::back,this,[=](){
        this->show();
        this->newindow->hide();
    });

    //同上
    this->newindow2 = new tips;
    connect(ui->tipsButton,&QPushButton::clicked,this,[=](){
        this->hide();
        this->newindow2->show();
    });
    connect(this->newindow2,&tips::back,this,[=](){
        this->show();
        this->newindow2->hide();
    });

    this->newindow3 = new ShowVehicle;
    connect(ui->showButton,&QPushButton::clicked,this,[=](){
        this->newindow3->show();
    });

    this->newindow4 = new FeeCalculate;
    connect(ui->feeButton,&QPushButton::clicked,this,[=](){
        this->hide();
        this->newindow4->show();
    });
    connect(this->newindow4,&FeeCalculate::back,this,[=](){
        this->show();
        this->newindow4->hide();
    });


    this->newindow5 = new FileOperation;
    connect(ui->fileButton,&QPushButton::clicked,this,[=](){
        this->hide();
        this->newindow5->show();
    });
    connect(this->newindow5,&FileOperation::back,this,[=](){
        this->show();
        this->newindow5->hide();
    });



    //希望实现缩放,效果不是很理想...
    /*QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName((QStringLiteral("horizontalLayout")));
    this->setLayout(horizontalLayout);
    horizontalLayout->addWidget(ui->feeButton);
    horizontalLayout->addWidget(ui->inButton);
    horizontalLayout->addWidget(ui->labelButton);
    horizontalLayout->addWidget(ui->label);
    horizontalLayout->addWidget(ui->label_2);
    horizontalLayout->addWidget(ui->label_3);
    horizontalLayout->addWidget(ui->outButton);
    horizontalLayout->addWidget(ui->tipsButton);
    horizontalLayout->addWidget(ui->text);
    horizontalLayout->addWidget(ui->showButton);*/

}

Widget::~Widget()
{
    delete ui;
}

//每当计时器发出信号就被执行
void Widget::timerUpdata()
{
    //三个参数的含义---字体:微软雅黑  字体大小  粗细程度(取值范围1 - 100)
    QFont font("Microsoft YaHei",16,20);
    QDateTime time = QDateTime::currentDateTime();  //获取当前时间
    QString str = time.toString("yyyy--MM--dd hh:mm:ss dddd");  //转换成字符串形式
    //绑定字体样式
    ui -> text ->setFont(font);
    this -> ui->text->setText(str);
}



//关闭页面
void Widget::on_outButton_clicked()
{
    this->close();
}


