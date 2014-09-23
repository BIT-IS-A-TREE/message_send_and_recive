#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "XmlOperations.h"
#include "stdio.h"
#include "string"
#include "User.h"
#include<string.h>
using namespace std;

XmlOperations myXml;
LinkManList myList;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    /*设置黑色背景
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);*/;

}

Login::~Login()
{
    delete ui;
}

int judgeIfLegal(string a,string b)
{
    int flag=0;
    int len=a.length();
    if(len!=11) return 1;
    for(int i=0;i<11;i++)
    {
        if(a[i]<'0' || a[i]>'9')
        {
            flag=1;
            break;
        }
    }
    if(flag==1) return 1;
    len=b.length();
    if(len<6||len>12) return 2;
    return 0;
}
//点击登陆
void Login::on_loginButton_clicked()
{
    char * hint1="用户名格式不正确~";
    QString Hint1;
    Hint1 += hint1;
    char * hint2="密码格式不正确~";
    QString Hint2;
    Hint2 += hint2;
    char * hint3="密码不正确~";
    QString Hint3;
    Hint3 += hint3;
    QString qnumber = ui->numberEdit->text();
    string number = qnumber.toStdString();
    char * pnumber=new char[15];
    strcpy(pnumber,number.c_str());
    QString qpassword = ui->passwordEdit->text();
    string password = qpassword.toStdString();
    char * ppassword=new char[30];
    strcpy(ppassword,password.c_str());
    int flag=judgeIfLegal(number,password);
    if(flag==1)
        ui->hintlabel1->setText(Hint1);
    else if(flag==2)
        ui->hintlabel2->setText(Hint2);
    else
    {
        User newUser;
        strcpy(newUser.username,pnumber);
        strcpy(newUser.password,ppassword);
        ;//函数，loginSend(number,password);用户登录，返回1登录成功，返回2密码不正确
        int temp=1;//赋值为上面函数返回值*************
        if(temp==1)
        {
           myXml.fileName = pnumber;
           myXml.openXml(pnumber);
           myList.creatLinkManList();
            ;//读取用户本地数据
           this->close();
           MainWindow *w=new MainWindow();
           w->show();
        }
        else
            ui->hintlabel1->setText(Hint3);
    }
}

//点击注册
void Login::on_registerButton_clicked()
{
    char * hint1="用户名格式不正确~";
    QString Hint1;
    Hint1 += hint1;
    char * hint2="密码格式不正确~";
    QString Hint2;
    Hint2 += hint2;
    char * hint3="注册成功~请登录~";
    QString Hint3;
    Hint3 += hint3;
    char * hint4="该电话已被注册~";
    QString Hint4;
    Hint4 += hint4;
    QString qnumber = ui->numberEdit->text();
    string number = qnumber.toStdString();
    char * pnumber=new char[15];
    strcpy(pnumber,number.c_str());
    QString qpassword = ui->passwordEdit->text();
    string password = qpassword.toStdString();
    char * ppassword=new char[30];
    strcpy(ppassword,password.c_str());
    int flag=judgeIfLegal(number,password);
    if(flag==1)
        ui->hintlabel1->setText(Hint1);
    else if(flag==2)
        ui->hintlabel2->setText(Hint2);
    else
    {
        User newUser;
        strcpy(newUser.username,pnumber);
        strcpy(newUser.password,ppassword);
        ;//函数，regSend(User newUser);注册用户，返回1注册成功，返回2电话已存在
        int temp=1;//赋值为上面函数返回值*************
        if(temp==1)
        {
            XmlOperations newXml;
            newXml.creatXml(pnumber);//添加一个用户
            ui->hintlabel1->setText(Hint3);
        }
        else
            ui->hintlabel1->setText(Hint4);
    }
}
