/*************************************************************************
	> File Name: sql_connect.h
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Wed 09 Mar 2016 03:29:53 AM PST
 ************************************************************************/

#ifndef _SQL_CONNECT_
#define _SQL_CONNECT_

#include<iostream>
#include<string>
#include<stdlib.h>
#include "mysql.h"

class sql_connecter
{
	public:
		sql_connecter(const std::string &_host,const std::string &_user,const std::string &_passwd,const std::string &_db);
		//connect remote mysql remote_db
		bool begin_connect();
		bool insert_sql(const std::string &data);
		bool delete_sql(const std::string &data);
		bool select_sql(std::string filed_name[],std::string _out_str[][5],int &out_row);

		//close remote link;
		bool close_connect();
		~sql_connecter();
		void show_info();
	private:
		MYSQL_RES *res;
		MYSQL *mysql_base;
		std::string host;
		std::string user;
		std::string passwd;
		std::string db;
};

#endif
