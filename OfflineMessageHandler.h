#ifndef _OFFLINEMESSAGE_H_
#define _OFFLINEMESSAGE_H_
#include "SystemHead.h"
#include "Message.h"
#include "User.h"

class OfflineMessageHandler{




public:
	queue<Message> getMessage(char IP[])
	{
		queue<Message> IPMessage;//属于这个IP的短信
		return IPMessage;
	}
	void addMessage(Message o)
	{

	}
};


#endif
