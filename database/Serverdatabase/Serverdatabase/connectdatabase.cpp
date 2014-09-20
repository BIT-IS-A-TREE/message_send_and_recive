#include"database.h"

class Database{
public:
	//查询特定电话号码的ip,在这之前要先
	string static return_ip_by_telephonenumber(string phonenumber){
		int row;
		for(row=1;row<=num;row++){
			if(key[row][0].compare(phonenumber)==0){  //不在线"1.1.1.1"
				return key[row][2];
			}
		}
		return "-1";
	}

	//修改短信的收发属性
	int static modifymessage(Message message_temp){//1表示成功 0表示失败
		string sender(message_temp.sender);
		string receiver(message_temp.receiver);
		string time(ctime(&message_temp.time));
		int isendreceiveflag=message_temp.sendRceiveFlag;
		char temp[50];
		sprintf(temp, "%d", isendreceiveflag);
		string sisendreceiveflag=temp;
		string common="UPDATE message SET sendReceiverflag = "+sisendreceiveflag+" WHERE sender = '"+sender+"' and receiver = '"+receiver+"' "+" and time = "+time +"' ";  //生成SQL语句
		char *command=const_cast<char*>(common.data());   //STRING转化为char*
		exe_sql(command);    //执行更新SQL语句
		return 1;
	}

	//存储短信到数据库
	int static storemessage(Message message_temp){//1表示成功 0表示失败
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
		message_num++;   //短信数目加一
		sprintf(temp, "%d", message_num);
		string smessage_num=temp;
		string common="INSERT INTO message VALUES ('"+smessage_num+"','"+sender+"','"+receiver+"','"+content+"','"+sisendreceiveflag+"','"+siImesflag+"','"+siImesSt+"','"+time+"')";
		char *command=const_cast<char*>(common.data());   //STRING转化为char*
		exe_sql(command);    //执行更新SQL语句
		return 1;
		return 0;
	}

	//检查数据用户是否能注册成功
	int static checkregister(User user){//成功返回1 否则返回0
		int row;
		string number(user.username);
		string keyword(user.password);
		string ipaddress(user.ip);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){//有相同的表示注册失败
				return 0;
			}
		}
		string common="INSERT INTO key_ip VALUES ('"+number+"','"+keyword+"','"+ipaddress+"')"; //生成SQL语句
		char *command=const_cast<char*>(common.data());   //STRING转化为char*
		exe_sql(command);    //执行更新SQL语句
		num++;
		key[num][0]=number;
		key[num][1]=keyword;
		key[num][2]=ipaddress;
		return 1;
	}

	//检查用户是否能登录成功 不存在帐号返回-2，用户名或密码错误返回-1 登录成功返回1
	int static checklogin(User user){
		int row;
		string number(user.username);
		string keyword(user.password);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){
				if(key[row][1].compare(keyword)==0){//密码正确
					key[row][2]=user.ip;
					/*
						更新ip表同时更新数据库
					*/
					string common="UPDATE key_ip SET ip = "+key[row][2]+" WHERE phonenumber = '"+key[row][0]+"' ";  //生成SQL语句
					char *command=const_cast<char*>(common.data());   //STRING转化为char*
					exe_sql(command);    //执行更新SQL语句
					return 1;
				}
				return -1;
			}
		}
		return -2;
	}

	//检查用户能否退出成功,1表示退出成功，0表示退出失败
	int static logout(User user){
		int row;
		string number(user.username);
		for(row=1;row<=num;row++){
			if(key[row][0].compare(number)==0){ //找到对应帐号,退出帐号ip改为1.1.1.1
				key[row][2]="1.1.1.1";
				/*
					更新数据库
				*/
				string common="UPDATE key_ip SET ip = "+key[row][2]+" WHERE phonenumber = '"+key[row][0]+"' ";  //生成SQL语句
				char *command=const_cast<char*>(common.data());   //STRING转化为char*
				exe_sql(command);    //执行更新SQL语句
				return 1;
			}
		}
		return 0;
	}


private:

	int static num,message_num;
	string static key[10000][4];

	/*这个函数用来执行传入的sql語句*/ 
	void static exe_sql(char* sql)
	{ 
		MYSQL my_connection; /*这是一个数据库连接*/ 
		int res; /*执行sql語句后的返回标志*/ 
		/*初始化mysql连接my_connection*/ 
		mysql_init(&my_connection); 
		/*这里就是用了mysql.h里的一个函数，用我们之前定义的那些宏建立mysql连接，并 
		返回一个值，返回不为空证明连接是成功的*/ 
		if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, 
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {/*连接成功*/ 
			printf("数据库执行exe_sql连接成功！n"); 
		/*这句话是设置查询编码为utf8，这样支持中文*/ 
			mysql_query(&my_connection, "set names utf8"); 
		/*下面这句话就是用mysql_query函数来执行我们刚刚传入的sql語句， 
		这会返回一个int值，如果为0，证明語句执行成功*/ 
			res = mysql_query(&my_connection, sql); 
			if (res) {/*现在就代表执行失败了*/ 
				printf("Error： mysql_query !\n"); 
		/*不要忘了关闭连接*/ 
				mysql_close(&my_connection); 
			}
			else{/*现在就代表执行成功了*/ 
		/*mysql_affected_rows会返回执行sql后影响的行数*/ 
				printf("%d 行受到影响！\n", 
				mysql_affected_rows(&my_connection)); 
				/*不要忘了关闭连接*/ 
				mysql_close(&my_connection); 
			} 
		}else
		{ 
			/*数据库连接失败*/ 
			printf("数据库执行exe_sql连接失败！\n"); 
		} 
	} 

	//获得密码表内数据，将数据拷贝到key的二维数组中
	void get_phone_key_ip(){
		num=0;
		MYSQL my_connection; /*这是一个数据库连接*/ 
		int res; /*执行sql語句后的返回标志*/ 
		MYSQL_RES *res_ptr; /*指向查询结果的指针*/ 
		MYSQL_FIELD *field; /*字段结构指针*/ 
		MYSQL_ROW result_row; /*按行返回的查询信息*/ 
		int row, column; /*查询返回的行数和列数*/ 
		int i, j; /*只是控制循环的两个变量*/ 
		/*初始化mysql连接my_connection*/ 
		mysql_init(&my_connection); 
		/*这里就是用了mysql.h里的一个函数，用我们之前定义的那些宏建立mysql连接，并 
		返回一个值，返回不为空证明连接是成功的*/ 
		if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, 
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {/*连接成功*/ 
			printf("数据库查询query_sql连接成功！\n"); 
			/*这句话是设置查询编码为utf8，这样支持中文*/ 
			mysql_query(&my_connection, "set names utf8"); 
			/*将查询的結果给res_ptr*/ 
			res_ptr = mysql_store_result(&my_connection); 
			/*如果结果不为空，就把结果print*/ 
			if (res_ptr) { 
				/*取得結果的行数和*/ 
				column = mysql_num_fields(res_ptr);
				row = (int)mysql_num_rows(res_ptr) + 1; 
				printf("查询到 %lu 行 \n", row); 
				/*输出結果的字段名*/ 
				for (i = 0; field = mysql_fetch_field(res_ptr); i++) 
					printf("%st ", field->name); 
				printf("\n"); 
				/*按行输出結果*/ 
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
				
				/*不要忘了关闭连接*/ 
				mysql_close(&my_connection); 
			} 
		} 
	}

	//初始化key表
	Database::Database(){
		message_num=0;
		get_phone_key_ip();
	}
};




