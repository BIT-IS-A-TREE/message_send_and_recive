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
		return temp;
	}
	static Message stringToMessage(string &o)
	{
		Message a;
		return a;
		
	}
	
};


#endif
