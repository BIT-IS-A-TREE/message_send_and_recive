#include"database.h"

class Database{
public:
	//��ѯ�ض��绰�����ip,����֮ǰҪ��
	string static return_ip_by_telephonenumber(string phonenumber){
		int row;
		for(row=1;row<=num;row++){
			if(key[row][0].compare(phonenumber)==0){  //������"1.1.1.1"
				return key[row][2];
			}
		}
		return "-1";
	}

	//�޸Ķ��ŵ��շ�����
	int static modifymessage(Message message_temp){//1��ʾ�ɹ� 0��ʾʧ��
		string sender(message_temp.sender);
		string receiver(message_temp.receiver);
		string time(ctime(&message_temp.time));
		int isendreceiveflag=message_temp.sendRceiveFlag;
		char temp[50];
		sprintf(temp, "%d", isendreceiveflag);
		string sisendreceiveflag=temp;
		string common="UPDATE message SET sendReceiverflag = "+sisendreceiveflag+" WHERE sender = '"+sender+"' and receiver = '"+receiver+"' "+" and time = "+time +"' ";  //����SQL���
		char *command=const_cast<char*>(common.data());   //STRINGת��Ϊchar*
		exe_sql(command);    //ִ�и���SQL���
		return 1;
	}

	//�洢���ŵ����ݿ�
	int static storemessage(Message message_temp){//1��ʾ�ɹ� 0��ʾʧ��
		string sender(message_temp.sender);
		string receiver(message_temp.receiver);
		string content(message_temp.content);
		string time(ctime(&message_temp.time));
		int isendreceiveflag=message_temp.sendRceiveFlag,iImesflag=message_temp.lmesFlag,iImesSt=message_temp.lmesSt;
		char temp[50];
		sprintf(temp, "%d", isendreceiveflag);
		string sisendreceiveflag=temp;
		sprintf(temp, "%d", iImesflag);
		string siImesflag=temp;
		sprintf(temp, "%d", iImesSt);
		string siImesSt=temp;
		message_num++;   //������Ŀ��һ
		sprintf(temp, "%d", message_num);
		string smessage_num=temp;
		string common="INSERT INTO message VALUES ('"+smessage_num+"','"+sender+"','"+receiver+"','"+content+"','"+sisendreceiveflag+"','"+siImesflag+"','"+siImesSt+"','"+time+"')";
		char *command=const_cast<char*>(common.data());   //STRINGת��Ϊchar*
		exe_sql(command);    //ִ�и���SQL���
		return 1;
		return 0;
	}

	//��������û��Ƿ���ע��ɹ�
	int static checkregister(User user){//�ɹ�����1 ���򷵻�0
		int row;
		string number(user.username);
		string keyword(user.password);
		string ipaddress(user.ip);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){//����ͬ�ı�ʾע��ʧ��
				return 0;
			}
		}
		string common="INSERT INTO key_ip VALUES ('"+number+"','"+keyword+"','"+ipaddress+"')"; //����SQL���
		char *command=const_cast<char*>(common.data());   //STRINGת��Ϊchar*
		exe_sql(command);    //ִ�и���SQL���
		num++;
		key[num][0]=number;
		key[num][1]=keyword;
		key[num][2]=ipaddress;
		return 1;
	}

	//����û��Ƿ��ܵ�¼�ɹ� �������ʺŷ���-2���û�����������󷵻�-1 ��¼�ɹ�����1
	int static checklogin(User user){
		int row;
		string number(user.username);
		string keyword(user.password);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){
				if(key[row][1].compare(keyword)==0){//������ȷ
					key[row][2]=user.ip;
					/*
						����ip��ͬʱ�������ݿ�
					*/
					string common="UPDATE key_ip SET ip = "+key[row][2]+" WHERE phonenumber = '"+key[row][0]+"' ";  //����SQL���
					char *command=const_cast<char*>(common.data());   //STRINGת��Ϊchar*
					exe_sql(command);    //ִ�и���SQL���
					return 1;
				}
				return -1;
			}
		}
		return -2;
	}

	//����û��ܷ��˳��ɹ�,1��ʾ�˳��ɹ���0��ʾ�˳�ʧ��
	int static logout(User user){
		int row;
		string number(user.username);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){ //�ҵ���Ӧ�ʺ�,�˳��ʺ�ip��Ϊ1.1.1.1
				key[row][2]="1.1.1.1";
				/*
					�������ݿ�
				*/
				string common="UPDATE key_ip SET ip = "+key[row][2]+" WHERE phonenumber = '"+key[row][0]+"' ";  //����SQL���
				char *command=const_cast<char*>(common.data());   //STRINGת��Ϊchar*
				exe_sql(command);    //ִ�и���SQL���
				return 1;
			}
		}
		return 0;
	}


private:

	int static num,message_num;
	string static key[10000][4];

	/*�����������ִ�д����sql�Z��*/ 
	void static exe_sql(char* sql)
	{ 
		MYSQL my_connection; /*����һ�����ݿ�����*/ 
		int res; /*ִ��sql�Z���ķ��ر�־*/ 
		/*��ʼ��mysql����my_connection*/ 
		mysql_init(&my_connection); 
		/*�����������mysql.h���һ��������������֮ǰ�������Щ�꽨��mysql���ӣ��� 
		����һ��ֵ�����ز�Ϊ��֤�������ǳɹ���*/ 
		if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, 
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {/*���ӳɹ�*/ 
			printf("���ݿ�ִ��exe_sql���ӳɹ���n"); 
		/*��仰�����ò�ѯ����Ϊutf8������֧������*/ 
			mysql_query(&my_connection, "set names utf8"); 
		/*������仰������mysql_query������ִ�����Ǹոմ����sql�Z�䣬 
		��᷵��һ��intֵ�����Ϊ0��֤���Z��ִ�гɹ�*/ 
			res = mysql_query(&my_connection, sql); 
			if (res) {/*���ھʹ���ִ��ʧ����*/ 
				printf("Error�� mysql_query !\n"); 
		/*��Ҫ���˹ر�����*/ 
				mysql_close(&my_connection); 
			}
			else{/*���ھʹ���ִ�гɹ���*/ 
		/*mysql_affected_rows�᷵��ִ��sql��Ӱ�������*/ 
				printf("%d ���ܵ�Ӱ�죡\n", 
				mysql_affected_rows(&my_connection)); 
				/*��Ҫ���˹ر�����*/ 
				mysql_close(&my_connection); 
			} 
		}else
		{ 
			/*���ݿ�����ʧ��*/ 
			printf("���ݿ�ִ��exe_sql����ʧ�ܣ�\n"); 
		} 
	} 

	//�������������ݣ������ݿ�����key�Ķ�ά������
	void get_phone_key_ip(){
		num=0;
		MYSQL my_connection; /*����һ�����ݿ�����*/ 
		int res; /*ִ��sql�Z���ķ��ر�־*/ 
		MYSQL_RES *res_ptr; /*ָ���ѯ�����ָ��*/ 
		MYSQL_FIELD *field; /*�ֶνṹָ��*/ 
		MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/ 
		int row, column; /*��ѯ���ص�����������*/ 
		int i, j; /*ֻ�ǿ���ѭ������������*/ 
		/*��ʼ��mysql����my_connection*/ 
		mysql_init(&my_connection); 
		/*�����������mysql.h���һ��������������֮ǰ�������Щ�꽨��mysql���ӣ��� 
		����һ��ֵ�����ز�Ϊ��֤�������ǳɹ���*/ 
		if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, 
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {/*���ӳɹ�*/ 
			printf("���ݿ��ѯquery_sql���ӳɹ���\n"); 
			/*��仰�����ò�ѯ����Ϊutf8������֧������*/ 
			mysql_query(&my_connection, "set names utf8"); 
			/*����ѯ�ĽY����res_ptr*/ 
			res_ptr = mysql_store_result(&my_connection); 
			/*��������Ϊ�գ��Ͱѽ��print*/ 
			if (res_ptr) { 
				/*ȡ�ýY����������*/ 
				column = mysql_num_fields(res_ptr);
				row = (int)mysql_num_rows(res_ptr) + 1; 
				printf("��ѯ�� %lu �� \n", row); 
				/*����Y�����ֶ���*/ 
				for (i = 0; field = mysql_fetch_field(res_ptr); i++) 
					printf("%st ", field->name); 
				printf("\n"); 
				/*��������Y��*/ 
				for (i = 1; i < row; i++) { 
					result_row = mysql_fetch_row(res_ptr); 
					for (j = 0; j < column; j++) 
					{
						num++;
						key[num][j]=result_row[j];
						printf("%s ", result_row[j]); 
					}
					printf("\n"); 
				} 
				
				/*��Ҫ���˹ر�����*/ 
				mysql_close(&my_connection); 
			} 
		} 
	}

	//��ʼ��key��
	Database::Database(){
		message_num=0;
		get_phone_key_ip();
	}
};




