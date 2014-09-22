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
		//if (strcmp(o.c_str(),"Online")==0)//上线
		//{
		//	char arg[1000];//假设就是Ip
		//	strcpy(arg,o.c_str());
		//	queue<Message> tempQueue=myOfflineMessageHandler.getMessage(arg);
		//	CommunicationHandler CM=myCommunicationHandlerList.getHandler(arg);
		//	while (!tempQueue.empty())
		//	{
		//		CM.sendInformation(tempQueue.front());
		//		tempQueue.pop();
		//	}
		//}
		//if (strcmp(o.c_str(),"Send")==0)//发送
		//{
		//	if (strcmp(o.c_str(),"SetTime")==0)//定时短信。
		//	{
		//		;
		//	}


		//	//int CheckOnline=check();
		//	//if (online)
		//	//{
		//	//	send;
		//	//}
		//	//else
		//	//{
		//	//	myOfflienMessageHandler.addMessage();
		//	//}
		//}




		char tempString[1000];
		strcpy(tempString,o.c_str());
		char *token=strtok(tempString,"@");
		
		//短信加解密顺序：Message@是否定时@定时时间@收件人@发件人@发送标识@短信标识@长短信顺序标识@收发时间@内容   如果不是定时短信定时时间可以随便设定，反正最后也不会调用这个属性
		if (strcmp(token,"Message")==0)//表示是短信
		{
			Message o;
			token = strtok (NULL, "@");
			if (strcmp(token,"0")==0)//非定时
			{
				o.IssetTime=0;//是否定时
				token = strtok (NULL, "@");
				o.setTime=atoi(token);//定时时间
				token = strtok (NULL, "@");
				strcpy(o.receiver,token);//收件人
				token = strtok (NULL, "@");
				strcpy(o.sender,token);//发件人
				token = strtok (NULL, "@");
				o.sendRceiveFlag=atoi(token);//发送标识
				token = strtok (NULL, "@");
				o.lmesFlag=atoi(token);//短信标识
				token = strtok (NULL, "@");
				o.lmesSt=atoi(token);//长短信顺序标识
				token = strtok (NULL, "@");
				o.time=atoi(token);//收发时间
				token =strtok(NULL,"@");
				string temp="";
				while (token!=NULL)
				{
					temp+=string(token);
					token =strtok(NULL,"@");
				}//把内容都存起来
				strcpy(o.content,temp.c_str());
				//短信内容保存完毕！
				
				//在线！查找CM,发送
				//不在线，调出OFFline，加入


			}
			else if (strcmp(token,"1")==0)//定时
			{
				o.IssetTime=1;//是否定时
				token = strtok (NULL, "@");
				o.setTime=atoi(token);//定时时间
				token = strtok (NULL, "@");
				strcpy(o.receiver,token);//收件人
				token = strtok (NULL, "@");
				strcpy(o.sender,token);//发件人
				token = strtok (NULL, "@");
				o.sendRceiveFlag=atoi(token);//发送标识
				token = strtok (NULL, "@");
				o.lmesFlag=atoi(token);//短信标识
				token = strtok (NULL, "@");
				o.lmesSt=atoi(token);//长短信顺序标识
				token = strtok (NULL, "@");
				o.time=atoi(token);//收发时间
				token =strtok(NULL,"@");
				string temp="";
				while (token!=NULL)
				{
					temp+=string(token);
					token =strtok(NULL,"@");
				}//把内容都存起来
				strcpy(o.content,temp.c_str());
				//短信内容保存完毕！


				//加入到定时短信队列！
				mySetTimeMessageHandler.addMessage(o);

			}
			else
			{
				printf("解析定时时报错！\n");
				return ;
			}
			return ;
		}
	//	if (strcmp(token,""))


		
	
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
