#include "Database.h"
#include "Server.h"

int head,rear;
string msgToBeDealed[1000];//string数组
CRITICAL_SECTION critical;
int num,message_num;
string key[10000][4];


//需要调试的部分：服务器端关闭后数据没有写入，导致第一次注册后关闭服务端第二次显示没有注册！

int main()
{
	Server myServer;
	head=rear=0;
	InitializeCriticalSection(&critical);
	Database *myDatabase;
	myDatabase=new Database();
	myServer.startServer();

	
}
