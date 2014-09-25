#ifndef _SETTIMEMESSAGEHANDLER_H_
#define _SETTIMEMESSAGEHANDLER_H_

#include "Message.h"
#include "User.h"
#include "SystemHead.h"
#include "Translation.h"


class SetTimeMessageHandler
{

private:
	//static priority_queue<Message> SetTimeMessageQueue;
	static Message SetTimeMessageQueue[1000];
	static CRITICAL_SECTION selfCritical;
	static int SetTimeMessageQueueTop;
	static DWORD WINAPI CheckTime(LPVOID arg)//定时短信部分需要Check
	{
		while (1)
		{
			time_t nowTime;//未初始化
			if (SetTimeMessageQueueTop!=0)
			{
				EnterCriticalSection(&selfCritical);		
				Message	headMessage=SetTimeMessageQueue[SetTimeMessageQueueTop];			
				LeaveCriticalSection(&selfCritical);
				//取出定时短信队首。

				time(&nowTime);//读取本地时间。

				if (difftime(nowTime,headMessage.setTime)<=100)//到时时间了。
				{
					headMessage.IssetTime=0;
					EnterCriticalSection(&critical);
					msgToBeDealed[rear]=TranslationHandler::messageToString(headMessage);
					rear++;
					LeaveCriticalSection(&critical);
					//添加到处理队列

					EnterCriticalSection(&selfCritical);
					SetTimeMessageQueueTop--;
					LeaveCriticalSection(&selfCritical);
					//修改定时短信队列
				}
			}
			Sleep(10);
		}
	}

	static int cmp(const void *a,const void *b)
	{
		Message *a1=(Message *)a;
		Message *b1=(Message *)b;
		if (a1->setTime-b1->setTime>0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
public:
	static void startWorking()
	{
		Sleep(5);
		InitializeCriticalSection(&selfCritical);
		HANDLE Handler=CreateThread(NULL,0,CheckTime,NULL,0,NULL);//应该是不会结束掉的
		printf("定时短信处理模块开始运行！\n");
	}


	static void addMessage(Message o)
	{
		EnterCriticalSection(&selfCritical);
		SetTimeMessageQueue[SetTimeMessageQueueTop]=o;
		SetTimeMessageQueueTop++;
		qsort(SetTimeMessageQueue,SetTimeMessageQueueTop,sizeof(Message),cmp);
		LeaveCriticalSection(&selfCritical);
	}
};
Message SetTimeMessageHandler::SetTimeMessageQueue[1000];
CRITICAL_SECTION SetTimeMessageHandler::selfCritical;
int SetTimeMessageHandler::SetTimeMessageQueueTop=0;











#endif
