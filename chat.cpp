#include "chat.h"
#include "ui_chat.h"
#include "mainwindow.h"
#include "XmlOperations.h"

extern XmlOperations myXml;
extern LinkManList myList;

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置黑色背景
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);*/

    //显示各个对话
    QString qcontent;
    string content;
    Message tempMessage;
    TiXmlElement* pMessage;
    for(int i=1;i<=myList.linkManListTime[myList.nowLinkMAn].mes_num;i++)
    {
        myXml.pgetpMessage(myList.linkManListTime[myList.nowLinkMAn].phonenumber,i,pMessage);
        tempMessage=myXml.getMessge(pMessage);
        if(tempMessage.sendRceiveFlag==1)
        {
            content = "               ";
            content +=  tempMessage.sender;
            content += "\n";
            content += "               ";
            content += tempMessage.content;
            content += "\n";
            content += "               ";
            content+=ctime(&tempMessage.time);
            qcontent = QString::fromStdString(content);
            ui->messagelistWidget->addItem(qcontent);
        }
        else
        {
            content =  tempMessage.sender;
            content += "\n";
            content += tempMessage.content;
            content += "\n";
            content+=ctime(&tempMessage.time);
            qcontent = QString::fromStdString(content);
            ui->messagelistWidget->addItem(qcontent);
        }
    }

}

Chat::~Chat()
{
    delete ui;
}

//清空聊天框
void Chat::on_clearButton_clicked()
{
    ui->messagelistWidget->clear();
    myXml.delateAllLinkManMes(myList.linkManListTime[myList.nowLinkMAn].phonenumber);
    myList.linkManListTime[myList.nowLinkMAn].mes_num=0;
}
//删除所选短信
void Chat::on_deleteButton_clicked()
{
    if(ui->messagelistWidget->currentItem()!=Q_NULLPTR)
     {
        int row = ui->messagelistWidget->currentRow();//row是短信所在行
        QListWidgetItem * item = ui->messagelistWidget->takeItem(row);
        delete item;
        myXml.delateMessage(myList.linkManListTime[myList.nowLinkMAn].phonenumber,row+1);
        myList.linkManListTime[myList.nowLinkMAn].mes_num--;
     }
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
