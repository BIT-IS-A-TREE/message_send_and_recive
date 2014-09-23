#include "search.h"
#include "ui_search.h"
#include "mainwindow.h"
#include "XmlOperations.h"

extern XmlOperations myXml;
extern LinkManList myList;

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置黑色背景
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);*/

}

Search::~Search()
{
    delete ui;
}

//搜索
void Search::on_searchButton_clicked()
{
    ui->messagelistWidget->clear();
     QString qcontent;
     string content;
     QString qSearchWord = ui->contentEdit->text();
     string SearchWord = qSearchWord.toStdString();
     char * pSearchWord=new char[300];
     strcpy(pSearchWord,SearchWord.c_str());
     //遍历每一条短信
     Message tempMessage;
     TiXmlElement* pMessage;
     for(int i=0;i<myList.linkManNum;i++)
     {
         for(int j=1;j<=myList.linkManListTime[i].mes_num;j++)
         {
             myXml.pgetpMessage(myList.linkManListTime[i].phonenumber,j,pMessage);
             tempMessage=myXml.getMessge(pMessage);
             if(myList.isContain(pSearchWord,tempMessage.content)==1)
             {
                 content="From:";
                 content+=tempMessage.sender;
                 content+="\nTo:";
                 content+=tempMessage.receiver;
                 content+="\n";
                 content+=tempMessage.content;
                 content+="\n";
                 content+=ctime(&tempMessage.time);
                 qcontent = QString::fromStdString(content);
                 ui->messagelistWidget->addItem(qcontent);
             }
         }
     }

}

//返回主界面
void Search::on_returnButton_clicked()
{
    this->close();
    MainWindow *w=new MainWindow();
    w->show();

}
