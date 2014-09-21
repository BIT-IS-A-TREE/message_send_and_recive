#include "chat.h"
#include "ui_chat.h"
#include "mainwindow.h"

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::green);
    this->setPalette(palette);

}

Chat::~Chat()
{
    delete ui;
}

//清空聊天框
void Chat::on_clearButton_clicked()
{

}
//删除所选短信
void Chat::on_deleteButton_clicked()
{

}
//返回主界面
void Chat::on_returnButton_clicked()
{
    this->close();
    MainWindow *w=new MainWindow();
    w->show();

}
//发送短信
void Chat::on_sendButton_clicked()
{

}
