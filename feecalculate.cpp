#include "feecalculate.h"
#include "ui_feecalculate.h"

//
FeeCalculate::FeeCalculate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeeCalculate)
{
    //一如既往，先设置一下标题，图标
    ui->setupUi(this);
    setWindowIcon(QIcon(":/picture/1.jpg"));
    connect(ui->backButton,SIGNAL(clicked(bool)),this,SIGNAL(back()));
    connect(ui->FeeButton,&QPushButton::clicked,this,[=](){
        getCarid();     //点击确认即可获取输入栏(LineEdit)信息
    });
    setWindowTitle("单独车辆付费查询");
    connect(ui->backButton,&QPushButton::clicked,this,[=]() //每次返回都清空操作
    {
        refreshText();
    });

}

//析构函数
FeeCalculate::~FeeCalculate()
{
    delete ui;
}

void FeeCalculate::getCarid()
{
    QTextCharFormat format; //字体设置
    format.setFontPointSize(16);
    format.setFontWeight(QFont::Bold);  //粗体
    ui->infoBrowser->setCurrentCharFormat(format);
    ui->feeBrowser->setCurrentCharFormat(format);

    ui->infoBrowser->clear();
    ui->infoBrowser->append("查询到的车辆信息");    //每次都清空原来存留的信息，添加文本标题
    ui->feeBrowser->clear();
    ui->feeBrowser->append("应付的费用");

    QString carid = ui->CaridLineEdit->text();
    //qDebug()<<carid;
    auto it = vehicle.find(carid);
    if(it!=vehicle.end())       //说明找到了,如果没找到就会返回迭代器的末尾
    {

        bool Identity     = it->getCarIdentity();
        QString Entertime = it->getStrEntertime();
        QString Exittime  = it->getStrExitTime();
        double  Fee       = it->getFee();
        QString identity;
        if(Identity)
        {
            identity = "校内车辆";
        }
        else
        {
            identity = "校外车辆";
        }

        QTextCharFormat format;
        format.setFontPointSize(12);
        ui->infoBrowser->setCurrentCharFormat(format);  //自定义字体样式并绑定

        ui->infoBrowser->append(identity);
        ui->infoBrowser->append(Entertime);
        ui->infoBrowser->append(Exittime);
        ui->feeBrowser->append(QString::number(Fee) + "元");
    }
    else
    {
        //it = vehicle.end()
        QMessageBox::information(this,">>>前排提醒<<<","---这时候试着输入正确的车牌号---");
    }
}

void FeeCalculate::refreshText()
{
    QTextCharFormat format;
    format.setFontPointSize(16);
    format.setFontWeight(QFont::Bold);  //粗体
    ui->infoBrowser->setCurrentCharFormat(format);

    //每次都清空原来存留的信息
    ui->CaridLineEdit->clear();//输入框
    ui->infoBrowser->clear();
    ui->infoBrowser->append("查询到的车辆信息");//图题还是保留下来
    ui->feeBrowser->clear();
    ui->feeBrowser->append("应付的费用");
}

//重写closeEvent
void FeeCalculate::closeEvent(QCloseEvent *event)
{
    emit back();        //关闭界面也返回主界面
}
