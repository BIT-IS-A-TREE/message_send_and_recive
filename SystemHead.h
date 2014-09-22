#include <time.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <list>
#include <stdio.h>
//#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"libmysql") 
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <winsock2.h> 
#include <mysql.h>/*注意要包含这个头文件*/ 
#include <string>
#include<cstdio>
#include<ctime>
//#include "Message.h"
//#include "User.h"
#include <WINSOCK2.H>
using namespace std;
extern int head,rear;
extern string msgToBeDealed[1000];
extern CRITICAL_SECTION critical;
