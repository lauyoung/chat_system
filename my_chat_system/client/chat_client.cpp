/*************************************************************************
	> File Name: chat_client.cpp
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Tue 29 Mar 2016 08:07:38 PM PDT
 ************************************************************************/
#include "udp_client.h"

int main()
{
	udp_client client;
	client.init_client();
	std::string msg;
	std::string out_msg;
	while(1)
	{
		std::cout<<"Please Entry:";
		fflush(stdout);
		std::cin>>msg;
		client.reliable_send_msg(msg);
		client.reliable_recv_msg(out_msg);
	}
	return 0;
}
