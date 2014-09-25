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
				o.setTime=_atoi64(token);//定时时间
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
				//o.time=_i64toa(token);//收发时间
				o.time=_atoi64(token);
				token =strtok(NULL,"");//短信内容
				strcpy(o.content,token);
				//短信内容保存完毕！
				


				//恢复,要改，调整,这里是O.sender要改成O.reciver
				Database::storemessage(o);//存入数据库
				string ans=Database::return_ip_by_telephonenumber(string(o.receiver));//查询指定ip状况，查询发现是0.0.0.0。未注册！！！
				if (ans=="1.1.1.1")//不在线，调出OFFline，加入
				{
					myOfflineMessageHandler.addMessage(o);//加入完毕
					printf("加入离线队列\n");
					
					//回执
					string repeatIP=Database::return_ip_by_telephonenumber(string(o.sender));
					char tempIP[1000];
					strcpy(tempIP,repeatIP.c_str());
					CommunicationHandler *repeatCM=myCommunicationHandlerList.getHandler(tempIP);
					repeatCM->sendMessage(TranslationHandler::getRepeatMessage("Not send to B!\n",tempIP));

				}
				else if (ans!="0.0.0.0")//存在且在线
				{
					char temp[1000];
					memset(temp,0,sizeof(temp));
					strcpy(temp,ans.c_str());
					CommunicationHandler *CM=myCommunicationHandlerList.getHandler(temp);//找到指定的客户端
					CM->sendMessage(o);

					//回执
					string repeatIP=Database::return_ip_by_telephonenumber(string(o.sender));
					char tempIP[1000];
					strcpy(tempIP,repeatIP.c_str());
					CommunicationHandler *repeatCM=myCommunicationHandlerList.getHandler(tempIP);
					repeatCM->sendMessage(TranslationHandler::getRepeatMessage("Send to B!\n",tempIP));
				}
				else
				{
					printf("短信接收用户不存在！\n");
				}
				

			}
			else if (strcmp(token,"1")==0)//定时
			{
				o.IssetTime=1;//是否定时
				token = strtok (NULL, "@");
				o.setTime=_atoi64(token);//定时时间
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
				o.time=_atoi64(token);//收发时间
				token =strtok(NULL,"");
				//短信内容
				strcpy(o.content,token);
				//短信内容保存完毕！

				Database::storemessage(o);//短信存入数据库
				//加入到定时短信队列！
				printf("加入定时短信队列！\n");
				mySetTimeMessageHandler.addMessage(o);

			}
			else
			{
				printf("解析短信时报错！\n");
				return ;
			}
			return ;
		}//短信部分解析完毕

		//登陆加解密顺序:Login@用户名@密码@IP
		if (strcmp(token,"Login")==0)
		{
			User o;
			token = strtok (NULL, "@");
			strcpy(o.username,token);//username
			token = strtok (NULL, "@");
			strcpy(o.password,token);//password
			token = strtok (NULL, "@");
			strcpy(o.ip,token);//ip;

			//查询用户名密码是否正确。
			if (Database::checklogin(o)==1)//正确，IP上线
			{

				//test:
				/*Message temp;
				strcpy(temp.receiver,"2");
				strcpy(temp.content,"fds");
				myOfflineMessageHandler.addMessage(temp);*/
				//testover

				CommunicationHandler *CM=myCommunicationHandlerList.getHandler(o.ip);
				CM->sendRepeat("Login","1");//往下需要回复。登陆。
				//短信推送。
				Sleep(500);
				queue<Message> tempQueue=myOfflineMessageHandler.getMessage(o.username);
				myOfflineMessageHandler.deleteMessage(o.username);
				while (!tempQueue.empty())
				{
					Message tempMessage=tempQueue.front();
					CommunicationHandler *CM=myCommunicationHandlerList.getHandler(o.ip);
					CM->sendMessage(tempMessage);
					tempQueue.pop();

					//回执
					string repeatIP=Database::return_ip_by_telephonenumber(string(tempMessage.sender));
					char tempIP[1000];
					strcpy(tempIP,repeatIP.c_str());
					CommunicationHandler *repeatCM=myCommunicationHandlerList.getHandler(tempIP);
					repeatCM->sendMessage(TranslationHandler::getRepeatMessage("Send to B!\n",tempIP));
				}
				return ;
			}
			else
			{
				CommunicationHandler *CM=myCommunicationHandlerList.getHandler(o.ip);
				CM->sendRepeat("Login","0");//往下需要回复。登陆。
				printf("用户登录失败！\n");
			}
			return ;
		}

		//注册加解密顺序:Register@用户名@密码@IP
		if (strcmp(token,"Register")==0)
		{
			User o;
			token = strtok (NULL, "@");
			strcpy(o.username,token);//username
			token = strtok (NULL, "@");
			strcpy(o.password,token);//password
			token = strtok (NULL, "@");
			strcpy(o.ip,token);//ip;

			//查询是否可以注册
			if (Database::checkregister(o)==1)//正确，允许注册
			{
				CommunicationHandler *CM=myCommunicationHandlerList.getHandler(o.ip);
				CM->sendRepeat("Register","1");
				return ;
			}
			else
			{
				CommunicationHandler *CM=myCommunicationHandlerList.getHandler(o.ip);
				CM->sendRepeat("Register","0");
				printf("用户注册失败\n");
			}
			return ;
		}

		//回执加密顺序Repeat@IP@内容
		if (strcmp(token,"Repeat")==0)
		{
			token = strtok (NULL, "@");
			char IP[100];
			memset(IP,0,sizeof(IP));
			strcpy(IP,token);

			
			token = strtok (NULL, "");
			//temp+=string(token);
			//while (token!=NULL)
			//{
			//token = strtok (NULL, "@");
			//temp+=string(token);
			//}
			//读取后面所有的信息，不被@中断
			printf("接收到客户端%s的回执：%s\n",IP,token);
			return ;
		}

		//下线信息提醒Logout@username@password@ip
		if (strcmp(token,"Logout")==0)
		{

			User o;
			token = strtok (NULL, "@");
			strcpy(o.ip,token);//ip;
			//读取用户数据
			Sleep(500);
			Database::logout(string(o.ip));//让他下线
			Sleep(50);
		 	myCommunicationHandlerList.DeleteHandler(o.ip);//
			Sleep(50);
			return ;
		}
		
		
	
	}

	static DWORD WINAPI WaitForConnection(LPVOID pParam)
	{
		Sleep(50);
		while (1)
		{
		printf("启动监听\n");
		int len=sizeof(SOCKADDR);
		CommunicationHandler *CH=new CommunicationHandler();
		CH->sockConnect=accept(serSocket,(SOCKADDR*)&CH->addrClient,&len);
		CH->startConnecting();
		printf("检测到连接请求！\n");
		Sleep(100);//避免还没有初始化就压入队列了。
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
		addr.sin_addr.S_un.S_addr=inet_addr("10.4.20.130");//服务器IP地址
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
