#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "send.h"
#include "search.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置背景*/
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//关机
void MainWindow::on_closeButton_clicked()
{
    this->close();
}
//跳转到新建消息界面
void MainWindow::on_tosendButton_clicked()
{
    this->close();
    Send *w=new Send();
    w->exec();

}
//跳转到搜索界面
void MainWindow::on_searchButton_clicked()
{
    this->close();
    Search *w=new Search();
    w->show();
}
//删除选定的短信
void MainWindow::on_deleteButton_clicked()
{

}
