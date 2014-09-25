#ifndef _COMMUNICATIONHANDLERLIST_H_
#define _COMMUNICATIONHANDLERLIST_H_

#include "SystemHead.h"
#include "CommunicationHandler.h"

class CommunicationHandlerList
{
	
private:
	char NowIP[1000];
	list<CommunicationHandler *> myList;

	/*struct IsHandler {
	 bool operator() (const CommunicationHandler& value) 
	 { return value.addrClient.sin_addr.S_un.S_addr==inet_addr(this->NowIP); }
	};
	*/

public:

	/*bool IsHandler (const CommunicationHandler& value)
		{
			return value.addrClient.sin_addr.S_un.S_addr==inet_addr(this->NowIP);
		}*/

	void push_back(CommunicationHandler *o)
	{
		myList.push_back(o);
	}
	CommunicationHandler* getHandler(char IP[])
		
	{
		for(list <CommunicationHandler *>::iterator b=myList.begin();b!=myList.end();b++) 
		{
			if ((*b)->addrClient.sin_addr.S_un.S_addr==inet_addr(IP))
			{
				return (*b);
			}
		}
	}
	void DeleteHandler(char IP[])
	{
		strcpy(this->NowIP,IP);
		//myList.remove_if(IsHandler());
		for(list <CommunicationHandler *>::iterator b=myList.begin();b!=myList.end();b++) 
		{
			if ((*b)->addrClient.sin_addr.S_un.S_addr==inet_addr(IP))
			{
				b=myList.erase(b);
			}
		}
	}

};


#endif
