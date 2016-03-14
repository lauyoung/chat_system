/*************************************************************************
	> File Name: httpd.h
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Sat 05 Mar 2016 10:53:33 PM PST
 ************************************************************************/

#ifndef _HTTPD_H_
#define _HTTPD_H_

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<errno.h>
#include<pthread.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<unistd.h>
#include<arpa/inet.h>


#define HTTP_VERSION "HTTP/1.0"
#define _BACK_LOG_ 5
#define _COMM_SIZE_ 1024
#define MAIN_PAGE "index.html"


#endif
