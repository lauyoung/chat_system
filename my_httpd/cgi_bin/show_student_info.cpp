/*************************************************************************
	> File Name: show_student_info.cpp
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Fri 11 Mar 2016 04:52:02 PM PST
 ************************************************************************/
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<stdio.h>
#include "sql_connect.h"

const std::string remote_ip = "127.0.0.1";
const std::string remote_user = "lauyoung";
const std::string remote_passwd = "123456";
const std::string remote_db = "remote_db";
int main()
{
	int content_length=-1;
	char method[1024];
	char query_string[1024];
	char post_data[4096];
	memset(method,'\0',sizeof(method));
	memset(query_string,'\0',sizeof(query_string));
	memset(post_data,'\0',sizeof(post_data));
	std::cout<<"<html>"<<std::endl;
	std::cout<<"<head>SHOW STUDENT</head>"<<std::endl;
	std::cout<<"<body>"<<std::endl;
	const std::string _host = remote_ip;
	const std::string _user = remote_user;
	const std::string _passwd = remote_passwd;
	const std::string _db = remote_db;
	std::string _sql_data[1024][5];
	std::string header[5];
	int curr_row =-1;
	sql_connecter conn(_host,_user,_passwd,_db);
	conn.begin_connect();
	conn.select_sql(header,_sql_data,curr_row);
	std::cout<<"<table border=\"1\">"<<std::endl;
	std::cout<<"<tr>"<<std::endl;
	for(int i=0;i<5;i++)
	{
		std::cout<<"<th>"<<header[i]<<"</th>"<<std::endl;
	}
	std::cout<<"</tr>"<<std::endl;
	for(int i=0;i<curr_row;++i)
	{
		std::cout<<"<tr>"<<std::endl;
		for(int j=0;j<5;++j)
		{
			std::cout<<"<td>"<<_sql_data[i][j]<<std::endl;
		}
		std::cout<<"</tr>"<<std::endl;
	}
	std::cout<<"</body>"<<std::endl;
	std::cout<<"</html>"<<std::endl;
}
