#ifndef _OFFLINEMESSAGE_H_
#define _OFFLINEMESSAGE_H_
#include "SystemHead.h"
#include "Message.h"
#include "User.h"

class OfflineMessageHandler{

private:
	list<Message>  myOfflineMessageList;


public:
	queue<Message> getMessage(char Name[])//不能传ip要传用户名
	{
		queue<Message> NameMessage;//属于这个IP的短信
		list<Message>::iterator it;
		for (it=myOfflineMessageList.begin();it!=myOfflineMessageList.end();it++)
		{
			if (strcmp(it->receiver,Name)==0)
			{
				NameMessage.push(*it);
			}
		}

		//待完善。
		return NameMessage;
	}
	void addMessage(Message o)
	{
		myOfflineMessageList.push_back(o);
	}
};


#endif
