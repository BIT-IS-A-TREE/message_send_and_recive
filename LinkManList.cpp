#include<XmlOperations.h>

extern XmlOperations myXml;

bool compMyList(struct LinkMan a,struct LinkMan b)
{
    return a.time>b.time;
}

void LinkManList::creatLinkManList()
{
    //读取联系人数目
   TiXmlElement * pLinkManNum= myXml.pDoc->FirstChildElement()->FirstChildElement();
   linkManNum = atoi(pLinkManNum->GetText());
   //将联系人信息提取到数组
   TiXmlElement *pLinkMan = pLinkManNum->NextSiblingElement();
   for(int i=0;i<linkManNum;i++)
   {
      linkManListTime[i] = myXml.getLinkMAn(pLinkMan);
      pLinkMan = pLinkMan->NextSiblingElement();
   }
   sortList();
}

void LinkManList::sortList()
{
    sort(linkManListTime,linkManListTime+linkManNum,compMyList);
}

void LinkManList::delateLinkMan(int st)
{
    myXml.delateLinkMan(linkManListTime[st-1].phonenumber);
    linkManListTime[st-1]=linkManListTime[linkManNum-1];
    linkManNum--;
}

void LinkManList::addLinkMan(LinkMan tempLinkMan)
{
    myXml.addLinkMan(tempLinkMan);
    linkManListTime[linkManNum++]=tempLinkMan;
    sortList();
}

bool LinkManList::isContain(char *str1,char *str2)
{
    int next[300];
        char str[300];
        int l1=strlen(str1);
        int l2=strlen(str2);
        int i,j,k;
        int cnt=0;
        for(i=0;i<l1;i++)
            str[cnt++]=str1[i];
        for(i=0;i<l2;i++)
            str[cnt++]=str2[i];

        i=0,k=-1;
        next[0]=-1;
        while(i<cnt){
            if(k==-1 || str[k]==str[i]){
                k++;
                i++;
                next[i]=k;
            }
            else
                k=next[k];
        }
        for(i=2*l1;i<=cnt;i++)
            if(next[i]>=l1)
                return true;
        return false;
}
