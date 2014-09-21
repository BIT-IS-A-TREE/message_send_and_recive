#ifndef _SERVER_H_
#define _SERVER_H_
#include "User.h"
#include "SystemHead.h"
#include "CommunicationHandler.h"
#include "Message.h"
#include "OfflineMessageHandler.h"
#include "CommunicationHandlerList.h"
#include "SetTimeMessageHandler.h"

#include "Translation.h"

class Server
{

private:
	
	static OfflineMessageHandler myOfflineMessageHandler;
	static SetTimeMessageHandler mySetTimeMessageHandler;



	static void Decode(string o)//这个地方都是要改的，
	{
		//比如说第一个是发送。
		if (strcmp(o.c_str(),"Online")==0)//上线
		{
			char arg[1000];//假设就是Ip
			strcpy(arg,o.c_str());
			queue<Message> tempQueue=myOfflineMessageHandler.getMessage(arg);
			CommunicationHandler CM=myCommunicationHandlerList.getHandler(arg);
			while (!tempQueue.empty())
			{
				CM.sendInformation(tempQueue.front());
				tempQueue.pop();
			}
		}
		if (strcmp(o.c_str(),"Send")==0)//发送
		{
			if (strcmp(o.c_str(),"SetTime")==0)//定时短信。
			{
				;
			}


			//int CheckOnline=check();
			//if (online)
			//{
			//	send;
			//}
			//else
			//{
			//	myOfflienMessageHandler.addMessage();
			//}
		}
		
	
	}

	static DWORD WINAPI WaitForConnection(LPVOID pParam)
	{
		Sleep(50);
	while (1)
		{
		printf("启动监听\n");
		int len=sizeof(SOCKADDR);
		SOCKADDR_IN addrClient;
		SOCKET sockClient=accept(serSocket,(SOCKADDR*)&addrClient,&len);
		printf("检测到连接请求！\n");
		CommunicationHandler CH(serSocket,sockClient,addrClient);
		CH.startConnecting();
		myCommunicationHandlerList.push_back(CH);

	//	Sleep(1000);
	//	CH.endSocket();


		//CommunicationHandler *CM=&CH;
		//CM->startConnecting();
		//CH.startConnecting(serSocket,sockClient,addrClient);
		/*struct arg Arg;
		Arg.addrClient=addrClient;
		Arg.Client=sockClient;
		Arg.Server=serSocket;
		unsigned int ID;
		HANDLE hHandle =(HANDLE)_beginthreadex(NULL,0,CH.startConnecting,&Arg,0,&ID);*/
		}
	}
	static DWORD WINAPI dealMessage(LPVOID pParam)
	{
		Sleep(2);
		printf("短信处理模块开始运行！\n");
		while (1)
		{
			EnterCriticalSection(&critical);
			while (head!=rear)//队列不为空
			{
				string temp=msgToBeDealed[head];
				head++;
				Decode(temp);
			}
			head=rear=0;
			LeaveCriticalSection(&critical);
			Sleep(20);
		}
	}


public:
	static SOCKET serSocket;
	static CommunicationHandlerList myCommunicationHandlerList;
	
	



	void startServer()
	{
		WORD myVersionRequest;
		WSADATA wsaData;
		myVersionRequest=MAKEWORD(1,1);
		int err;
		err=WSAStartup(myVersionRequest,&wsaData);
		if (!err)
		{
			printf("已打开套接字\n");

		} 
		else
		{
			printf("打开套接字失败！\n");
			return ;
		}
		serSocket=socket(AF_INET,SOCK_STREAM,0);//妈的注意这句话的位置！
		SOCKADDR_IN addr;
		addr.sin_family=AF_INET;
		addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//服务器IP地址
		addr.sin_port=htons(6000);//port
		bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
		listen(serSocket,10);
		printf("服务器启动成功！\n");
		HANDLE ConnectionHandler=CreateThread(NULL,0,WaitForConnection,NULL,0,NULL);
		HANDLE MessageHandler=CreateThread(NULL,0,dealMessage,NULL,0,NULL);
		mySetTimeMessageHandler.startWorking();
		while (1)
		{
			;
		}
	}
};
SOCKET Server::serSocket;
CommunicationHandlerList Server::myCommunicationHandlerList;
OfflineMessageHandler Server::myOfflineMessageHandler;
SetTimeMessageHandler Server::mySetTimeMessageHandler;

#endif
