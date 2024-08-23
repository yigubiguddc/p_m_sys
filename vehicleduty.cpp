#include "vehicleduty.h"
#include "ui_vehicleduty.h"
#include<QInputDialog>
#include<QPixmap>
#include<QMessageBox>


//四个要素:车牌   是否校内车辆    进入时间    驶离时间
//处理方式:

vehicleduty::vehicleduty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vehicleduty)
{
    ui->setupUi(this);
    setWindowTitle("有这么一辆车...");
    setWindowIcon(QIcon(":/picture/3.jpg"));
    //点击返回按钮发送返回信号
    setWindowTitle("车辆信息管理界面");
    //返回主界面信号
    connect(ui->backButton,SIGNAL(clicked(bool)),this,SIGNAL(back()));
    //保存按钮被按下时，执行VehicleRecording函数，记录所有的数据
    connect(ui->SaveButton,&QPushButton::clicked,this,[=](){
        QMessageBox::information(this,"提示","信息成功保存");
        VehicleRecording();
    });
}

//SaveButton的槽函数
void vehicleduty::VehicleRecording()
{
    //主动调用函数计算车辆相差时间，得到收费情况
    car.FeeCalculate();
    QString carid = car.getCarId();
    //限制车牌号只能输入六位，并且首位是英文(不区分大小写),后面是数字
    if(carid.length() == 6)
    {
    //如果您在函数内部定义一个正则表达式对象，而不使用static关键字将其声明为静态变量，那么每次调用该函数时都会创建一个新的正则表达式对象。这可能会导致性能问题，因为创建和销毁正则表达式对象需要时间和资源。
        static QRegularExpression regex("^[a-zA-Z][0-9]+$");        //这里用正则表达式做出限制,^和$表示字段的开头和结尾,以[a-z][A-Z]开头，后接[0-9]数字结尾，由于我在前面的if限制了只有六个字符，相当于只有一种情况符合要要求，也就是一个字母+五个数字的组合形式
        QRegularExpressionMatch match = regex.match(carid);
        if(match.hasMatch())
        {
            //使用QMap容器进行存储，依靠键值对进行排列
            vehicle[carid] = car;
            //测试是否成功保存了数据
            qDebug()<<vehicle[carid].getCarId();
        }
        else
        {
            QMessageBox::warning(this,"Warning","车牌号输入不合法，请检查、修改后再尝试保存");
            return;

        }
    }
    else
    {
        QMessageBox::warning(this,"warning","车牌号输入不合法，请检查、修改后再尝试保存");
    }
}


//车牌号获取
void vehicleduty::on_idinButton_clicked()
{
    //通过对话框获得输入数据.
    QInputDialog dialog;
    bool ok;
    QString Carid = dialog.getText(this,"输入车牌号","允许输入六位字符,由首位字母以及五个数字组成:",QLineEdit::Normal,"",&ok);
    if(ok)
    {
        Carid.truncate(6);  //截断
    }
    if(!Carid.isEmpty())
    {
        car.setCarId(Carid);        //已有数据则进行赋值
    }
    else
    {
        QMessageBox::warning(this,"Warning","未检测到输入车牌号,请检查是否正确输入。");
    }
}


//判断是否为校内车辆
void vehicleduty::on_identityButton_clicked()
{
    static bool hasBeenCalled = false;      //使用静态成员函数，暂时只允许输入时确认车辆身份，事后可以通过其他方法修改 --静态初始化变量只能被初始化一次，所以在后续的点击中这一步不会被执行，也就是说一直没法进入循环
    if(!hasBeenCalled)
    {
        //这里的reply可以检测哪个按钮被选中，他会记录，而QMessageBox::Yes和QMessageBox::No则是自带的两个按钮
        QMessageBox::StandardButton reply;
        //使用QMessageBox进行选项判断，只需要选择是或者否即可为车辆身份赋值
        //这里的nullptr表示它是一个独立窗口,是顶级窗口，不依赖其他窗口，不与它们发生联系，不参与对象树的析构
        reply = QMessageBox::question(nullptr, "车辆类型", "是否为校内车", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            car.SetCarIdentity(true);
        }
        else
        {
            car.SetCarIdentity(false);

        }
    }
    //这里设置一个connect，当返回上一个界面时，可以再次点击identityButton进行类型选择,只保证单次打开这个界面时只能进行一次操作，之后进入可以通过输入相同的车牌修改车辆身份信息
    connect(ui->backButton,&QPushButton::clicked,this,[=](){
        hasBeenCalled = false;          //重置hasBeenCalled

    });
    hasBeenCalled = true;
}



//qDebug检查一下数据(几乎看不见的小按钮，没删..)
void vehicleduty::on_checkButton_clicked()
{
    qDebug()<<"车牌号:";
    qDebug()<<car.getCarId();
    car.issuccessfulsetcaridentity();
    qDebug()<<car.getStrEntertime();
    qDebug()<<car.getStrExitTime();

}

//车辆进入和驶出时间记录，依靠按钮，车辆进入记录车牌是按一次inButton，再次进入先输入车牌号，按下outButton，记录出校时间，最后save一下即可
void vehicleduty::on_VehicleInButton_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    car.setEnterTime(currentDateTime);
    //这里加一个判断，以免随意点击
    if(car.getCarId() == "\0")      //根据我的构造函数可以知道我的QString类型数据初始值都是"\0".
    {
        QMessageBox::information(this,"wanrning","还未输入车牌数据！请先输入。");
        return;
    }
    QString enterStr = "车牌号为" + car.getCarId() +"的车辆进入";

    QMessageBox::information(this,"有车来了",enterStr);
}



void vehicleduty::on_VehicleOutButton_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    car.setExitTime(currentDateTime);
    if(car.getCarId() == "\0")
    {
        QMessageBox::information(this,"wanrning","还未输入车牌数据！请先输入。");
        return;
    }
    QString enterStr = "车牌号为" + car.getCarId() +"的车辆进入";
    QMessageBox::information(this,"车出去了",enterStr);
}

//析构函数，结束了罪恶的一生
vehicleduty::~vehicleduty()
{
    delete ui;
}

//如果关闭页面自动保存数据
void vehicleduty::closeEvent(QCloseEvent *event)
{
    VehicleRecording();
    emit back();//返回信号
    emit hasbeenclicked();//是否被点击信号，用来重置hasBeenClicked的值
}
