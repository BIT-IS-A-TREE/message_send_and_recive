#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <winsock2.h> 
#include <mysql.h>/*注意要包含这个头文件*/ 
#include <string>
#include<cstdio>
#include<ctime>
#pragma comment(lib,"libmysql") 
/*定义了一些数据库连接需要的宏*/ 
using namespace std;

#define HOST "localhost" 
#define USERNAME "root" 
#define PASSWORD "" 
#define DATABASE "test" 

class User{
public:
	char ip[50];
	char username[50];
	char password[50];
	
};

class Message{
public:
	char sender[15];//发件人手机号
	char receiver[15];//收件人手机号
	char content[300];//内容
	int sendRceiveFlag;//收发标识，1表示发送，2表示接收
	int lmesFlag;//短信标识，0表示短短信，x表示本条长短信一共有x条
	int lmesSt;//长短信顺序标记，0表示短短信，x表示本条短信为长短信的第x条
	time_t time;//收发时间
public:
	bool storeMessage();//存储新短信；返回是否成功;
};
