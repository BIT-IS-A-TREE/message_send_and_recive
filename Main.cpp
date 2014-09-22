#include "Database.h"
#include "Server.h"

int head,rear;
string msgToBeDealed[1000];//string数组
CRITICAL_SECTION critical;
int num,message_num;
string key[10000][4];




int main()
{
	Server myServer;
	head=rear=0;
	InitializeCriticalSection(&critical);
	Database *myDatabase;
	myDatabase=new Database();
	myServer.startServer();

	
}
