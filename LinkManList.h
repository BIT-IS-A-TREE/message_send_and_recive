#include<time.h>

struct LinkMan
{
    char phonenumber[15];//手机号
    int mes_num;//短信数目
    time_t time;//该联系人的最新一条信息的时间,若无信息则置为0
};

class LinkManList{
public:
    LinkMan linkManListTime[100];//按联系人最后短信时间排序
	int linkManNum;//联系人个数
    int nowLinkMAn;//正在查看的联系人
public:
    bool isContain(char *str1,char *str2);//str1为子串，str2为母串，判断母串中是否有子串
	void creatLinkManList();//创建
    void addLinkMan(LinkMan);//插入新联系人
    void sortList();//重新进行排序
    void delateLinkMan(int st);//删除第st个LinkMan
};
