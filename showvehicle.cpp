#include "showvehicle.h"
#include "ui_showvehicle.h"

ShowVehicle::ShowVehicle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowVehicle)
{
    ui->setupUi(this);
    ui->tableView->hide();
    setFixedSize(800,600);


    setWindowTitle("车辆信息展示");
    setWindowIcon(QIcon(":/picture/2.jpg"));
    //点击按钮，tableView展示，进入TableView函数
    connect(ui->TestButton,&QPushButton::clicked,this,[=](){
        ui->tableView->show();
        TableView();
    });
}

ShowVehicle::~ShowVehicle()
{
    delete ui;
}


void ShowVehicle::TableView()
{
    //窗口大小设定
    setFixedSize(1750,1400);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QHBoxLayout * alayout = new QHBoxLayout(this);
    alayout->addWidget(ui->tableView);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(300);//设置最小列宽
    model = new QStandardItemModel(this);   //开辟空间
    //伸缩到最后一页
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->setColumnCount(5);       //先固定好展示五列，分别展示如下内容
    QStringList title;
    title<<"车牌号"<<"车辆所属"<<"进入时间"<<"出校时间"<<"所需费用";
    //设置表头文本信息
    model->setHorizontalHeaderLabels(title);
    adding();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);
}


//添加数据行时调用adding函数,一次性向QStandatdItem中
void ShowVehicle::adding()
{
    auto it = vehicle.begin();
    if(vehicle.isEmpty())
    {
        QMessageBox::warning(this,"Warning","还没有可读取的数据，请试试先存入数据吧~");    //提示没有输入车辆信息
        setFixedSize(800,600);
        ui->tableView->hide();  //隐藏背景图片
        return;
    }
    while(it!=vehicle.end())//如果没有遍历到尾端
    {
        QList<QStandardItem*> adds;//一个以存储QStandaItem*类型数据的QList列表
        QString carid =it->getCarId();//获取车牌号、车辆信息、进出时间、所需费用等信息。
        QString identity;
        if(it->getCarIdentity())
        {
            identity = "校内";
        }
        else
        {
            identity = "校外";
        }
        QString enter = it->getStrEntertime();
        QString exit = it->getStrExitTime();

        double FeeOfVehicle = it->getFee();

        //构造函数初始化,参数为QString的重载函数（Qt中本身带有的重载函数）
        QStandardItem* caridItem = new QStandardItem(carid);
        QStandardItem* identityItem = new QStandardItem(identity);
        QStandardItem* enterItem = new QStandardItem(enter);
        QStandardItem* exitItem = new QStandardItem(exit);
        QStandardItem* feeItem;
        if(FeeOfVehicle>0)
        {
            feeItem= new QStandardItem(QString::number(FeeOfVehicle) + "元");    //这里要把double类型数据用QString的number转成QString类型
        }
        else
        {
            feeItem = new QStandardItem("免费");
        }

        qDebug()<<FeeOfVehicle;
        //先创建QStandardItem对象，设置为只读，因为知识展示数据，原则上不允许中途修改数据
        caridItem->setEditable(false);
        identityItem->setEditable(false);
        enterItem->setEditable(false);
        exitItem->setEditable(false);
        feeItem->setEditable(false);

        adds << caridItem<< identityItem<<enterItem <<exitItem <<feeItem;
        model->appendRow(adds);
        it++;           //迭代器后移
    }
}


void ShowVehicle::clearAll()
{
    model->clear();
}

void ShowVehicle::paintEvent(QPaintEvent *paint)
{
    QPainter painter(this);         //QPainter类对象构造
    QPixmap pix;
    painter.setOpacity(0.3);        //透明度设置
    pix.load(":/picture/6.jpg");    //图片加载
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

//窗口关闭事件发生时同时隐藏tableView，下次进入还是需要做选择
void ShowVehicle::closeEvent(QCloseEvent *event)
{
    //关闭界面后复原窗口大小
    setFixedSize(800,600);
    ui->tableView->hide();
}
