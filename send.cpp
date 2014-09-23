#include "send.h"
#include "ui_send.h"
#include "chat.h"
#include "mainwindow.h"

Send::Send(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Send)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置黑色背景
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);*/

}

Send::~Send()
{
    delete ui;
}

//返回主界面
void Send::on_returnButton_clicked()
{
    this->close();
    MainWindow *w=new MainWindow();
    w->show();

}
//定时短信
void Send::on_timeButton_clicked()
{

}
//取消定时
void Send::on_notimeButton_clicked()
{

}
//发送短信
void Send::on_sendButton_clicked()
{
    this->close();
    Chat *w=new Chat();
    w->show();
}
//添加多个联系人
void Send::on_addButton_clicked()
{

}
