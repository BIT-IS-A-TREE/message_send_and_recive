#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <winsock2.h> 
#include <mysql.h>/*ע��Ҫ�������ͷ�ļ�*/ 
#include <string>
#include<cstdio>
#include<ctime>
#pragma comment(lib,"libmysql") 
/*������һЩ���ݿ�������Ҫ�ĺ�*/ 
using namespace std;

#define HOST "localhost" 
#define USERNAME "root" 
#define PASSWORD "" 
#define DATABASE "test" 

class User{
public:
	char ip[50];
	char username[50];
	char password[50];
	
};

class Message{
public:
	char sender[15];//�������ֻ���
	char receiver[15];//�ռ����ֻ���
	char content[300];//����
	int sendRceiveFlag;//�շ���ʶ��1��ʾ���ͣ�2��ʾ����
	int lmesFlag;//���ű�ʶ��0��ʾ�̶��ţ�x��ʾ����������һ����x��
	int lmesSt;//������˳���ǣ�0��ʾ�̶��ţ�x��ʾ��������Ϊ�����ŵĵ�x��
	time_t time;//�շ�ʱ��
public:
	bool storeMessage();//�洢�¶��ţ������Ƿ�ɹ�;
};
