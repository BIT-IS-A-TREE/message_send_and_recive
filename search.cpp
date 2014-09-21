#include "search.h"
#include "ui_search.h"
#include "mainwindow.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置背景*/
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::blue);
    this->setPalette(palette);

}

Search::~Search()
{
    delete ui;
}

//搜索
void Search::on_searchButton_clicked()
{

}

//返回主界面
void Search::on_returnButton_clicked()
{
    this->close();
    MainWindow *w=new MainWindow();
    w->show();

}
