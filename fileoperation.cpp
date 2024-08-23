#include "fileoperation.h"
#include "ui_fileoperation.h"

FileOperation::FileOperation(QWidget *parent) :QWidget(parent),ui(new Ui::FileOperation),infilename(":/data/input.txt"),outfilename("output.txt")
{
    ui->setupUi(this);
    //默认选中默认路径
    ui->inCheckBox->setChecked(1);
    ui->outCheckBox->setChecked(1);

    setWindowTitle("文件操作");
    setWindowIcon(QIcon(":/picture/3.jpg"));

    connect(ui->backButton,SIGNAL(clicked(bool)),this,SIGNAL(back()));
    connect(ui->inButton,&QPushButton::clicked,this,[=](){
        fileGet();      //正则表达式配合普通函数而非槽函数。
    });
    connect(ui->outButton,&QPushButton::clicked,this,[=](){
        fileWrite();
    });
    connect(ui->inCheckBox,&QCheckBox::stateChanged,this,&FileOperation::onInCheckBoxStateChanged);//这里需要提供类名，不然会报错
    connect(ui->outCheckBox,&QCheckBox::stateChanged,this,&FileOperation::onOutCheckBoxStateChanged);
    //connect(ui->wayCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));
}

FileOperation::~FileOperation()
{
    delete ui;
}

//文件读入操作(默认从input.txt写入)
void FileOperation::fileGet()
{
    QFile file(infilename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"无法打开文件，运行失败";
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd())  //文件流还没有到头继续执行
    {
        QString line = in.readLine();
        QStringList dataList = line.split(" ");     //以单个空格为间隔
        if(dataList.size()!=4)
        {
            qDebug()<<"数据格式错误";     //提示信息，格式读取有误
            QMessageBox::warning(this,"警告","数据格式错误");
            continue;
        }
        QString carid = dataList[0];
        QString caridentity = dataList[1];
        QString entertime = dataList[2];
        QString exittime = dataList[3];

        QDateTime inSchool = QDateTime::fromString(entertime,"yyyy.M.d-h:mm");
        QDateTime outSchool= QDateTime::fromString(exittime, "yyyy.M.d-h:mm");

        bool Caridentity;
        if(caridentity == "1")
        {
            Caridentity = 1;
        }
        else
        {
            Caridentity = 0;
        }

        temp.setCarId(carid);
        temp.SetCarIdentity(Caridentity);
        temp.setEnterTime(inSchool);
        temp.setExitTime(outSchool);
        //temp.Show();                             //暂时只是qDebug()输出一下,没有问题，下一步存入vehicle了
        temp.FeeCalculate();                     //这步骤不可缺少，要先手动调用计算费用函数，更新fee的数据之后再存入vehicle中.
        vehicle[carid] = temp;
    }
    connect(ui->inButton,&QPushButton::clicked,this,[=](){
        QMessageBox::information(this,"提示","文件已成功保存到input.txt");
    });
    file.close();
}

void FileOperation::fileWrite()
{
    //QString fileName = ":/data/output.txt";

    //QFile file(":\\data\\output.txt");

    //QFile file("D:\\Qtprojects\\studying\\output.txt");
    //QFile file("D:\\Qtprojects\\studying\\data\\output.txt");
    //QFile file(outfilename);
    //QFile file("D:\\Qtprojects\\studying\\output.txt"); //打开不存在的文件，会自动创建这个文件并输入内容
    //QFile file(":/data/outto.txt");
    //QFile file("D:\\Qtprojects\\studying\\data\\output.txt");
    //QFile file("output.txt");      //很烦，不让用相对路径,输入没问题，输出毛病还多...
    //QFile file(":/data/output.txt");
    QFile file(outfilename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"无法打开文件"<<file.errorString();
        QMessageBox::warning(this,"警告","文件无法打开");
        return;
    }
    QTextStream out(&file);
    auto it = vehicle.begin();
    while(it!=vehicle.end())
    {
        QString carid,caridentity,entertime,exittime;

        carid = it->getCarId();
        caridentity = it->getCarIdentityStr();
        entertime = it->getStrEntertime();
        exittime = it->getStrExitTime();
        QString line = carid + " "+ caridentity+" " + entertime+" " + exittime;     //一行一行来
        out<<line<<"\n";
        it++;
    }
    connect(ui->outButton,&QPushButton::clicked,this,[=](){
        QMessageBox::information(this,"提示","文件已成功保存到" + outfilename);
    });
    file.close();
}


void FileOperation::onInCheckBoxStateChanged(int state)
{
    if(state == Qt::Checked)
    {
        qDebug()<<"checked";
        //默认路径，不改变什么
    }
    else
    {
        qDebug()<<"unchecked";
        //手动输入需要的文件名
        QInputDialog dialog;
        bool ok;                        //选择确认  true   选择 取消或者关闭页面  false
        QString filename = dialog.getText(this,"the path","输入读入文件路径",QLineEdit::Normal,"",&ok);
        if(ok)  //用户选择确认
        {
            infilename = filename;      //改名
        }
    }
}


void FileOperation::onOutCheckBoxStateChanged(int state)
{
    if(state == Qt::Checked)
    {
        qDebug()<<"checked";
        //默认路径，不改变什么
    }
    else
    {
        qDebug()<<"unchecked";
        QInputDialog dialog;
        bool ok;
        QString filename = dialog.getText(this,"the path","输入写入文件路径",QLineEdit::Normal,"",&ok); //第五个参数是文本框默认值，不用管
        if(ok)
        {
            outfilename = filename;
        }
    }
}


void FileOperation::closeEvent(QCloseEvent *event)
{
    emit back();
}
