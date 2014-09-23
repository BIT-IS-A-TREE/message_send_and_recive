

#include<time.h>

class Message{
public:
	char sender[15];//发件人手机号
	char receiver[15];//收件人手机号
	char content[300];//内容
	int sendRceiveFlag;//收发标识，1表示发送，2表示接收
	int lmesFlag;//短信标识，0表示短短信，x表示本条长短信一共有x条
	int lmesSt;//长短信顺序标记，0表示短短信，x表示本条短信为长短信的第x条
    int setTimeFlag;//定时短信标识，0标识非定时，1表示定时
    time_t setTime;//定时的时间
	time_t time;//收发时间
public:
    void storeMessage();//存储新短信；
};

