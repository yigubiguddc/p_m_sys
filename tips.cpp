#include "tips.h"
#include "ui_tips.h"

tips::tips(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tips)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/picture/1.jpg"));
    //setFixedSize(1300,1400);
    setWindowTitle("提示");

    //给出使用提示
    this->ui->tipBrowser->hide();

    //QPixmap pix = QPixmap(":/picture/2.jpg").scaled(this->ui->label->size());
    QPixmap pix = QPixmap(":/picture/2.jpg").scaled(this->size());
    this->ui->label->setPixmap(pix);

    ui->backButton->raise();
    ui->tipsButton->raise();

    connect(ui->backButton,SIGNAL(clicked(bool)),this,SIGNAL(back()));
    connect(ui->tipsButton,&QPushButton::clicked,this,[=](){
        this->ui->label->hide();
            ShowTips();
        });
}

tips::~tips()
{
    delete ui;
}


void tips::ShowTips()
{
    ui->tipBrowser->show();
    //ui->tipBrowser->setFixedSize(1300,1400);
    ui->tipsButton->raise();
    ui->tipsButton->hide();
}


void tips::closeEvent(QCloseEvent *event)
{
    ui->tipBrowser->hide();
}
