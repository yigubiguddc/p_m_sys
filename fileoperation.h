#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <QWidget>
#include<QPixmap>
#include<QPushButton>
#include<QDebug>

#include<QFile>
#include<QTextStream>
#include<QStringList>
#include<QMessageBox>
#include<QInputDialog>
#include<QCheckBox>
#include<QtWidgets>

#include<vehicle.h>
#include<header.h>
#include<QCoreApplication>



namespace Ui {
class FileOperation;
}

class FileOperation : public QWidget
{
    Q_OBJECT

public:
    explicit FileOperation(QWidget *parent = nullptr);
    void fileGet();
    void fileWrite();
    ~FileOperation();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::FileOperation *ui;
    Vehicle temp;           //用来做中间变量，每次都重新赋值,作为键值对的值存入vehicle
    QString infilename;     //输入和输出文件名
    QString outfilename;

private slots:
    void onInCheckBoxStateChanged(int state);   //读取
    void onOutCheckBoxStateChanged(int state);   //写入

signals:
    void back();
};

#endif // FILEOPERATION_H
