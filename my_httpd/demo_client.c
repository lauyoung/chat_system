/*************************************************************************
	> File Name: demo_client.c
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Sun 06 Mar 2016 04:27:01 AM PST
 ************************************************************************/

#include"demo_client.h"
void usage(const char* msg)
{
	printf("Usage : %s [IP] [PORT]\n");
}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		usage(argv[0]);
		exit(1);
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		perror("socket");
		exit(1);
	}
	int port = atoi(argv[2]);
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(argv[1]);

	if( connect(sock,(struct sockaddr*)&remote,sizeof(remote))<0)
	{
		perror("connect");
		exit(2);
	}
	close(sock);
	return 0;
}
