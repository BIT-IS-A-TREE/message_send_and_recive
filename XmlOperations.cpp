#include"XmlOperations.h"

time_t FormatTime2(const char * a)  
{  
	char szTime[15];
	int cnt=0;
	for(int i=20;i<=23;i++)
		szTime[cnt++]=a[i];
	char s[4];
	s[0]=a[4],s[1]=a[5],s[2]=a[6],s[3]='\0';
	if(strcmp(s,"Jan")==0) szTime[cnt++]='0',szTime[cnt++]='1';
	else if(strcmp(s,"Feb")==0) szTime[cnt++]='0',szTime[cnt++]='2';
	else if(strcmp(s,"Mar")==0) szTime[cnt++]='0',szTime[cnt++]='3';
	else if(strcmp(s,"Apr")==0) szTime[cnt++]='0',szTime[cnt++]='4';
	else if(strcmp(s,"May")==0) szTime[cnt++]='0',szTime[cnt++]='5';
	else if(strcmp(s,"Jun")==0) szTime[cnt++]='0',szTime[cnt++]='6';
	else if(strcmp(s,"Jul")==0) szTime[cnt++]='0',szTime[cnt++]='7';
	else if(strcmp(s,"Aug")==0) szTime[cnt++]='0',szTime[cnt++]='8';
	else if(strcmp(s,"Sep")==0) szTime[cnt++]='0',szTime[cnt++]='9';
	else if(strcmp(s,"Oct")==0) szTime[cnt++]='1',szTime[cnt++]='0';
	else if(strcmp(s,"Now")==0) szTime[cnt++]='1',szTime[cnt++]='1';
	else if(strcmp(s,"Dec")==0) szTime[cnt++]='1',szTime[cnt++]='2';
	szTime[cnt++]=a[8];
	szTime[cnt++]=a[9];
	szTime[cnt++]=a[11];
	szTime[cnt++]=a[12];
	szTime[cnt++]=a[14];
	szTime[cnt++]=a[15];
	szTime[cnt++]=a[17];
	szTime[cnt++]=a[18];
    struct tm tm1;  
    time_t time1;  
  
    sscanf(szTime, "%4d%2d%2d%2d%2d%2d",      
          &tm1.tm_year,   
          &tm1.tm_mon,   
          &tm1.tm_mday,   
          &tm1.tm_hour,   
          &tm1.tm_min,  
          &tm1.tm_sec);  
          
    tm1.tm_year -= 1900;  
     tm1.tm_mon --;  
    tm1.tm_isdst=-1;  
    time1 = mktime(&tm1);  
    return time1;  
}  

void XmlOperations :: creatXml(char * fileName)
{
	// 定义一个TiXmlDocument类指针
	pDoc = new TiXmlDocument;
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration(_T("1.0"),_T(""),_T(""));
	pDoc->LinkEndChild(pDeclaration);
	// 生成一个根节点：MyList
	TiXmlElement *pRootEle = new TiXmlElement(_T("MyList"));
	pDoc->LinkEndChild(pRootEle);
	//存入LinkMan数
	TiXmlElement *pLinkManNum = new TiXmlElement(_T("LinkManNum"));
	TiXmlText *LinkManNum = new TiXmlText("0");
	pLinkManNum->LinkEndChild(LinkManNum);
	pRootEle->LinkEndChild(pLinkManNum);
	//保存
	pDoc->SaveFile(fileName);
}

void XmlOperations :: openXml(char * fileName)
{
	pDoc->LoadFile(fileName);
}

bool XmlOperations :: GetNodePointerByName(TiXmlElement* pRootEle,char * &strNodeName,TiXmlElement* &Node)
{
	 // 假如等于根节点名，就退出
     if (strcmp( strNodeName,pRootEle->Value())==0)
     {
         Node = pRootEle;
		 return true;
     }
	  TiXmlElement* pEle = pRootEle;  
      for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())  
    {  
          //递归处理子节点，获取节点指针
          if(GetNodePointerByName(pEle,strNodeName,Node))
			  return true;
     }  
	 return false;
}

void XmlOperations :: addLinkMan(LinkMan tempLinkMan)
{
	TiXmlElement *pRootEle = pDoc->FirstChildElement();
	//生成联系人节点
	TiXmlElement *pLinkMan = new TiXmlElement(_T("LinkMan"));
	pRootEle->LinkEndChild(pLinkMan);
	//链接电话号码
	TiXmlElement *phoneNumber = new TiXmlElement(_T("phoneNumber"));
	TiXmlText *phoneNumberText = new TiXmlText(tempLinkMan.phonenumber);
	phoneNumber->LinkEndChild(phoneNumberText);
	pLinkMan->LinkEndChild(phoneNumber);
	//链接短信数量
	TiXmlElement *mesNum = new TiXmlElement(_T("mesNum"));
	char str[10];
	sprintf(str,"%d",tempLinkMan.mes_num);
	TiXmlText *mesNumText = new TiXmlText(str);
	mesNum->LinkEndChild(mesNumText);
	pLinkMan->LinkEndChild(mesNum);
	//链接最后短信时间
	TiXmlElement *plastMessageTime = new TiXmlElement(_T("plastMessageTime"));
	TiXmlText *lastMessageTime = new TiXmlText(ctime(&tempLinkMan.time));
	plastMessageTime->LinkEndChild(lastMessageTime);
	pLinkMan->LinkEndChild(plastMessageTime);
	//链接节点Messages
	TiXmlElement *pMessages = new TiXmlElement(_T("Messages"));
	pLinkMan->LinkEndChild(pMessages);
	//修改联系人数目
	TiXmlElement * pLinkManNum=pRootEle->FirstChildElement();
	int number=atoi(pLinkManNum->GetText());
	number++;	
	sprintf(str,"%d",number);
	TiXmlText *LinkManNum = new TiXmlText(str);
	pLinkManNum->Clear();
	pLinkManNum->LinkEndChild(LinkManNum);
	//保存
	pDoc->SaveFile(fileName);
}

bool XmlOperations :: pgetpLinkMan(char * tempPhoneNumber, TiXmlElement* &pLinkMan)
{
	TiXmlElement* pEle;
	for(pEle=pDoc->FirstChildElement()->FirstChildElement()->NextSiblingElement(); pEle; pEle = pEle->NextSiblingElement())  
    {  
		if(strcmp(tempPhoneNumber,pEle->FirstChildElement()->GetText())==0)
		{
			pLinkMan=pEle;	
			return true;
		}
     }  
	return false;
}

void XmlOperations :: addMessage(char * tempPhoneNumber,Message tempMessage)
{
	//找到所属联系人
	TiXmlElement* pLinkMan;
	pgetpLinkMan(tempPhoneNumber,pLinkMan);
	//找到对应messages
	TiXmlElement* pMessages;
	char * ts="Messages";
	GetNodePointerByName(pLinkMan,ts,pMessages);
	//新建message
	TiXmlElement* pMessage = new TiXmlElement(_T("Message"));  
	//链接发件人号码
	TiXmlElement *pSender = new TiXmlElement(_T("sender"));
	TiXmlText *senderText = new TiXmlText(tempMessage.sender);
	pSender->LinkEndChild(senderText);
	pMessage->LinkEndChild(pSender);
	//链接收件人号码
	TiXmlElement *pReceiver = new TiXmlElement(_T("receiver"));
	TiXmlText *receiverText = new TiXmlText(tempMessage.receiver);
	pReceiver->LinkEndChild(receiverText);
	pMessage->LinkEndChild(pReceiver);
	//链接短信内容
	TiXmlElement *pContent = new TiXmlElement(_T("content"));
	TiXmlText *contentText = new TiXmlText(tempMessage.content);
	pContent->LinkEndChild(contentText);
	pMessage->LinkEndChild(pContent);
	//链接短信收发标识
	TiXmlElement *pFlag = new TiXmlElement(_T("flag"));
	TiXmlText *flagText;
	if(tempMessage.lmesFlag==1)
		flagText = new TiXmlText("receive");
	else
		flagText = new TiXmlText("send");
	pFlag->LinkEndChild(flagText);
	pMessage->LinkEndChild(pFlag);
	//链接短信时间
	TiXmlElement *pMessageTime = new TiXmlElement(_T("time"));
	TiXmlText *MessageTime = new TiXmlText(ctime(&tempMessage.time));
	pMessageTime->LinkEndChild(MessageTime);
	pMessage->LinkEndChild(MessageTime);
	//链接整个短信                                
	pMessages->LinkEndChild(pMessage);
	//修改短信数目
	TiXmlElement * pmesNum=pLinkMan->FirstChildElement()->NextSiblingElement();
	int number=atoi(pmesNum->GetText());
	number++;	
	char str[10];
	sprintf(str,"%d",number);
	TiXmlText *mesNum = new TiXmlText(str);
	pmesNum->Clear();
	pmesNum->LinkEndChild(mesNum);
	//修改联系人最后短信时间
	TiXmlElement *plastMessageTime = pLinkMan->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
	plastMessageTime->Clear();
	TiXmlText *lastMessageTime = new TiXmlText(ctime(&tempMessage.time));
	plastMessageTime->LinkEndChild(lastMessageTime);
	//保存
	pDoc->SaveFile(fileName);
}

bool XmlOperations :: pgetpMessage(char * tempPhoneNumber,int st, TiXmlElement* &pMessage)//找到特定短信，更新指针
{
	//找到所属联系人
	TiXmlElement* pLinkMan;
	pgetpLinkMan(tempPhoneNumber,pLinkMan);
	//判断是否有该短信
	TiXmlElement * pmesNum=pLinkMan->FirstChildElement()->NextSiblingElement();
	int number=atoi(pmesNum->GetText());
	if(st<=0 || st>number)
		return false;
	//找到对应messages
	TiXmlElement* pMessages;
	char * ts="Messages";
	GetNodePointerByName(pLinkMan,ts,pMessages);
	//找到对应短信
	TiXmlElement* pEle=pMessages->FirstChildElement();
	int i;
	for(i=1;i<st;i++)
	{
		pEle=pEle->NextSiblingElement();
	}
	pMessage=pEle;
	return true;
}

LinkMan XmlOperations :: getLinkMAn(TiXmlElement* pLinkMan)//提取联系人信息
{
	LinkMan tempLinkMan;
	//赋值电话号码
	strcpy(tempLinkMan.phonenumber,pLinkMan->FirstChildElement()->GetText());
	//赋值短信数量
	int number=atoi(pLinkMan->FirstChildElement()->NextSiblingElement()->GetText());
	tempLinkMan.mes_num=number;
	//赋值最后短信时间
	tempLinkMan.time=FormatTime2(pLinkMan->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->GetText());
	return tempLinkMan;
}

Message XmlOperations :: getMessge(TiXmlElement* pMessage)//提取短信息
{
	Message tempMessage;
	//赋值发件人号码
	strcpy(tempMessage.sender,pMessage->FirstChildElement()->GetText());
	//赋值收件人号码
	strcpy(tempMessage.receiver,pMessage->FirstChildElement()->NextSiblingElement()->GetText());
	//赋值短信内容
	strcpy(tempMessage.content,pMessage->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->GetText());
	//赋值收发标识
	char ts[10];
	strcpy(ts,pMessage->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->GetText());
	if(ts[0]=='s')tempMessage.sendRceiveFlag=1;
	else tempMessage.sendRceiveFlag=2;
	//赋值时间
	tempMessage.time=FormatTime2(pMessage->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->GetText());
	return tempMessage;
}

void XmlOperations :: delateMessage(char * tempPhoneNumber,int st)//删除短信
{
	//找到所属联系人
	TiXmlElement* pLinkMan;
	pgetpLinkMan(tempPhoneNumber,pLinkMan);
	//找到特定短信
	TiXmlElement* pMessage;
	pgetpMessage(tempPhoneNumber,st,pMessage);
	//删除短信
	TiXmlNode *pParNode =  pMessage->Parent();
	TiXmlElement* pParentEle = pParNode->ToElement();
	pParentEle->RemoveChild(pMessage);
	//修改短信数目
	TiXmlElement * pmesNum=pLinkMan->FirstChildElement()->NextSiblingElement();
	int number=atoi(pmesNum->GetText());
	number--;	
	char str[10];
	sprintf(str,"%d",number);
	TiXmlText *mesNum = new TiXmlText(str);
	pmesNum->Clear();
	pmesNum->LinkEndChild(mesNum);
	//保存
	pDoc->SaveFile(fileName);
}


void XmlOperations :: delateAllLinkManMes(char * tempPhoneNumber)
{
	//找到所属联系人
	TiXmlElement* pLinkMan;
	pgetpLinkMan(tempPhoneNumber,pLinkMan);
	//找到对应messages
	TiXmlElement* pMessages;
	char * ts="Messages";
	GetNodePointerByName(pLinkMan,ts,pMessages);
	//删除所有短信
	pMessages->Clear();
	//修改短信数目
	TiXmlElement * pmesNum=pLinkMan->FirstChildElement()->NextSiblingElement();
	int number=atoi(pmesNum->GetText());
	number=0;	
	char str[10];
	sprintf(str,"%d",number);
	TiXmlText *mesNum = new TiXmlText(str);
	pmesNum->Clear();
	pmesNum->LinkEndChild(mesNum);
	//保存
	pDoc->SaveFile(fileName);
}

void XmlOperations::delateLinkMan(char * tempPhoneNumber)
{
	//找到所属联系人
	TiXmlElement* pLinkMan;
	pgetpLinkMan(tempPhoneNumber,pLinkMan);
	//删除联系人
	TiXmlNode *pParNode =  pLinkMan->Parent();
	TiXmlElement* pParentEle = pParNode->ToElement();
	pParentEle->RemoveChild(pLinkMan);
	//修改联系人数目
	//存入LinkMan数
	TiXmlElement *pLinkManNum = pDoc->FirstChildElement()->FirstChildElement();
	int number=atoi(pLinkManNum->GetText());
	number=0;	
	char str[10];
	sprintf(str,"%d",number);
	TiXmlText *LinkManNum = new TiXmlText(str);
	pLinkManNum->Clear();
	pLinkManNum->LinkEndChild(LinkManNum);
	pDoc->SaveFile(fileName);
}
