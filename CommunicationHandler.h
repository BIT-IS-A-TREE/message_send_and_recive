#ifndef _COMMUNICATIONHANDLER_H_
#define _COMMUNICATIONHANDLER_H_
#include "User.h"
#include "Message.h"
#include "SystemHead.h"

class CommunicationHandler
{

private:
	CRITICAL_SECTION selfCritical;
	bool endFlag;
	static void Sending(void *arg)
	{
		CommunicationHandler *This=(CommunicationHandler *)arg;
		printf("同客户端：%s发送数据的通道已建立\n",inet_ntoa(This->addrClient.sin_addr));
		memset(This->msgToSend,0,sizeof(This->msgToSend));
		strcpy(This->msgToSend,"你好朋友！\n");
		while (!This->endFlag)//这个地方可能要加critical
		{
			EnterCriticalSection(&This->selfCritical);
			if (strlen(This->msgToSend)!=0)
			{
				send(This->sockClient,This->msgToSend,strlen(This->msgToSend)+1,0);
				printf("向客户端%s发送数据：%s\n",inet_ntoa(This->addrClient.sin_addr),This->msgToSend);
				memset(This->msgToSend,0,sizeof(This->msgToSend));
			}
			LeaveCriticalSection(&This->selfCritical);
			Sleep(10);
		}

	//	Sleep(10);
	//	shutdown(This->sockClient,1);

		printf("发送线程退出！\n");
	}
	static void Recieving(void * arg)
	{
		CommunicationHandler *This=(CommunicationHandler *)arg;
		printf("用于接收客户端：%s数据的通道已建立\n",inet_ntoa(This->addrClient.sin_addr));//打印格式化IP地址,这个地方要写出friend
		while (!This->endFlag)
		{
			char buf[10000]; 
			recv(This->sockClient,buf,10000,0);
			printf("从客户端%s接收到数据：%s\n",inet_ntoa(This->addrClient.sin_addr),buf);
			EnterCriticalSection(&critical);//全局critical
			msgToBeDealed[rear]=string(buf);
			rear++;
			LeaveCriticalSection(&critical);
			Sleep(10);
		}

		
		//shutdown(This->sockClient,0);

		printf("接收线程退出！\n");
	}
	static void Connecting(void *arg)
	{
		


		CommunicationHandler * This=(CommunicationHandler *)arg;

		This->endFlag=false;
		memset(This->msgToSend,0,sizeof(This->msgToSend));
		InitializeCriticalSection(&This->selfCritical);




		printf("客户端%s已连接上\n",inet_ntoa(This->addrClient.sin_addr));
		This->startRecieving();
		This->startSending();
		while (!This->endFlag)
		{
			;
		}
		Sleep(1000);
		
	//	shutdown(This->sockClient,3);
		closesocket(This->sockClient);//这个地方close会出错，再考虑考虑。
		
		printf("主线程退出！\n");
		Sleep(1000);
	}
	int startSending()
	{
		return _beginthread(Sending,0,(void *)this);
	}
	int startRecieving()
	{
		return _beginthread(Recieving,0,(void *)this);
	}
	
public:
	SOCKET sockClient,sockServer;
	char msgToSend[10000];
	SOCKADDR_IN addrClient;
	CommunicationHandler(SOCKET serSocket,SOCKET client,SOCKADDR_IN addr);
	
	void sendRepeat(string o)
	{
		string temp="";
		temp+="Repeat@";
		temp+=o;
		EnterCriticalSection(&this->selfCritical);
		strcpy(msgToSend,temp.c_str());
		LeaveCriticalSection(&this->selfCritical);
	}
	void sendMessage(Message o)
	{
		//短信加解密顺序：Message@是否定时@定时时间@收件人@发件人@发送标识@短信标识@长短信顺序标识@收发时间@内容   如果不是定时短信定时时间可以随便设定，反正最后也不会调用这个属性
		string temp;
		temp="Message@";
		temp+=o.IssetTime +"@";
		temp+=o.setTime+'@';
		temp+=o.receiver+'@';
		temp+=o.sender+'@';
		temp+=o.sendRceiveFlag+'@';
		temp+=o.lmesFlag+'@';
		temp+=o.lmesSt+'@';
		temp+=o.time+'@';
		temp+=o.content;
		EnterCriticalSection(&this->selfCritical);
		strcpy(msgToSend,temp.c_str());
		LeaveCriticalSection(&this->selfCritical);;
	}
	//void sendInformation(char * o)
	//{
	//	//string temp(o);
	//	EnterCriticalSection(&this->selfCritical);
	//	strcpy(msgToSend,o);
	//	LeaveCriticalSection(&this->selfCritical);
	//}
	void endSocket()
	{
		endFlag=true;
	}

	int startConnecting()
	{
		return _beginthread(Connecting,0,(void *)this);
	}
	
	
};



CommunicationHandler::CommunicationHandler(SOCKET serSocket,SOCKET client,SOCKADDR_IN addr)//先要声明一次。
{
	this->endFlag=false;
	this->addrClient=addr;
	this->sockClient=client;
	this->sockServer=serSocket;
}


#endif
