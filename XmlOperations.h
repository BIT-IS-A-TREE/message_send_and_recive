#include "tinyxml.h" // TinyXML的头文件
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<tchar.h>
#include"Message.h"
#include"LinkManList.h"
using namespace std;

class XmlOperations
{
public:
	char * fileName;//xml文件名
	TiXmlDocument *pDoc;//xml文件指针
public:
	void creatXml(char *);//创建xml文件
	void openXml(char *);//读取xml文件
	bool GetNodePointerByName(TiXmlElement* pRootEle,char * &strNodeName,TiXmlElement* &Node);//以节点名查找节点，更新指针
	bool pgetpLinkMan(char *, TiXmlElement* &pLinkMan);//找到特定号码，更新指针
	bool pgetpMessage(char *,int, TiXmlElement* &pMessage);//找到特定短信，更新指针
	void addLinkMan(LinkMan);//插入联系人
	void addMessage(char *,Message);//插入短信
	LinkMan getLinkMAn(TiXmlElement*);//提取联系人信息
	Message getMessge(TiXmlElement*);//提取短信息
	void delateLinkMan(char *);//删除联系人
	void delateAllLinkManMes(char *);//删除联系人的所有短信
	void delateMessage(char *,int );//删除短信
};

