/*************************************************************************
	> File Name: sql_connect.cpp
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Wed 09 Mar 2016 03:29:31 AM PST
 ************************************************************************/

#include "sql_connect.h"

sql_connecter::sql_connecter(const std::string &_host,\
		const std::string &_user,\
		const std::string &_passwd,\
		const std::string &_db)
{
	//通过函数mysql_init函数返回一个mysqlbase 的句柄
	//mysql_init(),初始化句柄，参数为NULL时返回一个新的句柄
	this->mysql_base = mysql_init(NULL);
	this->res =NULL;
	this->host = _host;
	this->user = _user;
	this->passwd = _passwd;
	this->db = _db;
}
bool sql_connecter::begin_connect()
{
	if(mysql_real_connect(mysql_base,host.c_str(),user.c_str(),passwd.c_str(),db.c_str(),3306,NULL,0)==0)
	{
		std::cout<<"sql connect error"<<std::endl;
		return false;
	}
	else
	{
		std::cout<<"sql connected"<<std::endl;
	}
	return true;
}
bool sql_connecter::close_connect()
{
	mysql_close(mysql_base);//断开链接
	//std::cout<<"connect close.."<<std::endl;
}
bool sql_connecter::delete_sql(const std::string &data)
{
	std::string sql ="DELETE FROM student_info WHERE ";
	sql +=data;
	if(mysql_query(mysql_base,sql.c_str())==0)
	{
		std::cout<<"DELETE success !"<<std::endl;
		return true;
	}else
	{
		std::cerr<<"DELETE failed!"<<std::endl;
		return false;
	}
}
bool sql_connecter::select_sql(std::string field_name[],std::string _out_data[][5],int &_out_row)
{//传出参数

	std::string sql = "SELECT * FROM student_info";
	if(mysql_query(mysql_base,sql.c_str())==0)
	{
		//std::cout<<"query success!"<<std::endl;
	}else
	{
		//std::cerr<<"query failed!"<<std::endl;
	}
	//参数MYSQL——RES res主要存放mysql——query的查询结果
	//特别注意的是这个res是系统所开辟，因此必须手动free，
	//防止内存泄漏
	res =mysql_store_result(mysql_base);
	int row_num = mysql_num_rows(res);//数据列数
	int field_num =mysql_num_fields(res);//数据行数
	_out_row=row_num;

	//std::cout<<mysql_num_rows(res)<<std::endl;
	//std::cout<<mysql_num_fields(res)<<std::endl;
	//读出表头
	MYSQL_FIELD *fd =NULL;
	int i =0;
	for(;fd=mysql_fetch_field(res);)
	{
		field_name[i++] = fd->name;
	}

	for(int index=0;index < row_num;index++)
	{
		MYSQL_ROW _row =mysql_fetch_row(res);
		if(_row)
		{
			int start =0;
			for(;start<field_num;start++)
			{
				_out_data[index][start] = _row[start];
				//std::cout<<_row[start]<<"\t";
			}
			//std::cout<<std::endl;
		}
	}
	return true;
}
bool sql_connecter::insert_sql(const std::string &data)
{
	std::string sql ="INSERT INTO student_info (name,age,school,hobby) values ";
	sql +="(";
	sql +=data;
	sql+=")";
	if(mysql_query(mysql_base,sql.c_str())==0)
	{
		std::cout<<"query success !"<<std::endl;
		return true;
	}else
	{
		std::cerr<<"query failed!"<<std::endl;
		return false;
	}
}
sql_connecter::~sql_connecter()
{
	close_connect();
	if(res != NULL)
	{
		free(res);
	}
}
void sql_connecter::show_info()
{//返回客户端的版本信息
	std::cout<<mysql_get_client_info()<<std::endl;
}
#ifdef _DEBUG_
int main()
{
	std::string _sql_data[1024][5];
	std::string header[5];
	int curr_row =-1;
	const std::string _host = "127.0.0.1";
	const std::string _user = "lauyoung";
	const std::string _passwd = "123456";
	const std::string _db = "remote_db";
	const std::string data = "'common',23,'aaa','sleep'";
	const std::string data_for_del = "id=2";

	sql_connecter conn(_host,_user,_passwd,_db);
	conn.begin_connect();
	//conn.delete_sql(data_for_del);
	//conn.select_sql(header,_sql_data,curr_row);
	conn.insert_sql(data);
//	sleep(1);
//	for(int i=0;i<5;++i)
//	{//输出表头
//		std::cout<<header[i]<<"\t";
//	}
//	std::cout<<std::endl;
//
//	for(int i=0;i<curr_row;++i)
//	{
//		for(int j=0;j<5;++j)
//		{
//			std::cout<<_sql_data[i][j]<<"\t";
//		}
//		std::cout<<std::endl;
//	}
	conn.show_info();
	return 0;
}

#endif
