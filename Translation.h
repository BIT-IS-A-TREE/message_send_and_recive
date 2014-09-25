#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_
#include "SystemHead.h"
#include "Message.h"
#include "User.h"
class TranslationHandler
{
public:
	static string messageToString(Message o)
	{
		///*string temp;
		//temp="Message@";
		//temp+=o.IssetTime +"@";
		//temp+=o.setTime+'@';
		//temp+=o.receiver+'@';
		//temp+=o.sender+'@';
		//temp+=o.sendRceiveFlag+'@';
		//temp+=o.lmesFlag+'@';
		//temp+=o.lmesSt+'@';
		//temp+=o.time+'@';
		//temp+=o.content;*/
		  char buf[1000];

        string temp;
		long long temptime;
        temp="";
        temp += "Message@";
		temptime=o.IssetTime;
			sprintf(buf, "%lld", temptime);
        temp+=buf;
              //  temp+=string(o.IssetTime);
				temp+='@';
				temptime=o.setTime;
                sprintf(buf, "%lld",temptime);
                temp+=buf;
                //temp+=string(o.setTime);
                temp+='@';
                temp+=o.receiver;
                temp+='@';
                temp+=o.sender;
                temp+='@';
				temptime=o.sendRceiveFlag;
				sprintf(buf, "%lld", temptime);
                temp+=buf;
                //temp+=string(o.sendRceiveFlag);
                temp+='@';
				temptime=o.lmesFlag;
				sprintf(buf, "%lld", temptime);
                temp+=buf;
                //temp+=string(o.lmesFlag);
                temp+='@';
				temptime=o.lmesSt;
				sprintf(buf, "%lld", temptime);
                temp+=buf;
                //temp+=string(o.lmesSt);
                temp+='@';
				temptime=o.time;
				sprintf(buf, "%lld", temptime);
                temp+=buf;
//              temp+=string(o.time);
                temp+='@';
                temp+=o.content;
		return temp;
	}

	static Message getRepeatMessage(string o,char reci[])
	{
		Message temp;
		strcpy(temp.content,o.c_str());
		temp.IssetTime=0;
		temp.lmesFlag=0;
		temp.lmesSt=0;
		memset(temp.receiver,0,sizeof(temp.receiver));
		strcpy(temp.receiver,reci);
		memset(temp.sender,0,sizeof(temp.sender));
		strcpy(temp.sender,"10086");
		temp.sendRceiveFlag=1;
		temp.setTime=time(&temp.setTime);
		temp.time=time(&temp.time);
		return temp;
	}

	static Message stringToMessage(string &o)
	{
		Message a;
		return a;
		
	}
	
};


#endif
