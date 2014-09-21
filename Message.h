#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include "SystemHead.h"

class Message{
public:
	char sender[15];//发件人手机号
	char receiver[15];//收件人手机号
	char content[300];//内容
	int sendRceiveFlag;//收发标识，1表示发送，2表示接收
	int lmesFlag;//短信标识，0表示短短信，x表示本条长短信一共有x条
	int lmesSt;//长短信顺序标记，0表示短短信，x表示本条短信为长短信的第x条
	time_t time;//收发时间
	bool setTime;
public:
	bool storeMessage();//存储新短信；返回是否成功;
	friend bool operator< (Message a,Message b)
	{
		return a.time<b.time;
	}
};

struct arg{
	SOCKET Client;
	SOCKET Server;
	SOCKADDR_IN addrClient;
};

#endif
