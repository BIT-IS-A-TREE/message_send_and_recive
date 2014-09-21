#include"LinkMan.h"


class LinkManList{
public:
    LinkMan linkManListTime[100];//按联系人最后短信时间排序
	int linkManNum;//联系人个数
public:
    bool searchLinkMan(char *);//查询是否有该手机号；若有返回true否则返回false
	void creatLinkManList();//创建
	void addLinkMan(LinkMan);//插入新号码
    void sortList();//重新进行排序
};
