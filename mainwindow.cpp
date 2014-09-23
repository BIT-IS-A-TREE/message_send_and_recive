#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "send.h"
#include "search.h"
#include "chat.h"
#include "XmlOperations.h"
#include <QDialog>

extern XmlOperations myXml;
extern LinkManList myList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏


    //显示各个会话
    QString qcontent;
    string content;
    Message tempMessage;
    TiXmlElement* pMessage;
    for(int i=0;i<myList.linkManNum;i++)
    {
        if(myList.linkManListTime[i].mes_num==0)
        {
            content=myList.linkManListTime[i].phonenumber;
            content+="\n\n";
            qcontent = QString::fromStdString(content);
            ui->messagelistWidget->addItem(qcontent);
            continue;
        }
        myXml.pgetpMessage(myList.linkManListTime[i].phonenumber,myList.linkManListTime[i].mes_num,pMessage);
        tempMessage=myXml.getMessge(pMessage);
        if(tempMessage.sendRceiveFlag==1)content = tempMessage.receiver;
        else content = tempMessage.sender;
        content+="\n";
        char tsContent[30];
        int j;
        for(j=0;j<20;j++)
            tsContent[j]=tempMessage.content[j];
        tsContent[j]=0;
        content+=tsContent;
        content+="...";
        content+="\n";
        content+=ctime(&tempMessage.time);
        qcontent = QString::fromStdString(content);
        ui->messagelistWidget->addItem(qcontent);
    }


    /*设置黑色背景
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);*/

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
//删除选定的会话
void MainWindow::on_deleteButton_clicked()
{
    if(ui->messagelistWidget->currentItem()!=Q_NULLPTR)
     {
        int row = ui->messagelistWidget->currentRow();//row是短信所在行
        QListWidgetItem * item = ui->messagelistWidget->takeItem(row);
        delete item;
        myList.delateLinkMan(row+1);
     }
}

void MainWindow::on_messagelistWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui->messagelistWidget->currentRow();//row是短信所在行
    myList.nowLinkMAn=row;
    Chat *w=new Chat();
    w->show();
    this->close();
}
