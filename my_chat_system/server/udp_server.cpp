#include"udp_server.h"


static void print_log(std::string _log)
{
	std::cerr<<_log<<std::endl;
}

udp_server::udp_server(unsigned short _port):port(_port)
{
	//std::cout<<"udp_server"<<std::endl;
	sock = -1;
}
//注册函数
bool udp_server::register_user(struct sockaddr_in &client)
{
	std::string _ip_key=inet_ntoa(client.sin_addr);
	print_log(_ip_key);
	std::map<std::string,struct sockaddr_in>::iterator _iter=online_user.find(_ip_key);
	if(_iter != online_user.end())
	{
		return false;
	}
	online_user.insert(std::pair<std::string,struct sockaddr_in>(_ip_key,client));
	return true;
}

udp_server::~udp_server()
{
	if(sock !=-1)
	{
		close(sock);
	}
}

int udp_server::init_server()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock <0)
	{
		print_log(strerror(errno));
		exit(1);
	}
	//print_log("create sock success!");
	struct sockaddr_in local;
	local.sin_family =AF_INET;
	local.sin_port =htons(port);
	local.sin_addr.s_addr =htonl(INADDR_ANY);

	if(bind(sock, (struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno));
		exit(-1);
	}
	//print_log("bind sock success!");
	return 0;
}
int udp_server::reliable_recv_msg()
{
	std::string _out_msg;
	int ret= recv_msg(_out_msg);
	if(ret>0)
	{
		print_log(_out_msg);
		//pool.put_msg(_out_msg);
	}
	return ret;
}

//if recv success return _size
//else return -1;
int udp_server::recv_msg(std::string &_out_msg)
{
	char buf[G_BLOCK_SIZE];
	memset(buf,'\0',sizeof(buf));

	struct sockaddr_in cli;
	socklen_t len=sizeof(cli);
	bzero(&cli,len);
	ssize_t _size = recvfrom(this->sock,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	if(-1==_size)
	{
		print_log("recv data from cli failed!");
		return 1;
	}else if(_size >=0)
	{
		std::string _log="recv data from cli succeed";
		//print_log(_log);
		_out_msg=buf;
		//std::cout<<"FOR TEST"<<_out_msg<<std::endl;
		//保存消息到map
		register_user(cli);
	}
	return _size;
}
int udp_server::send_msg(const std::string &_in_msg,\
		const struct sockaddr_in& client,\
		socklen_t len)
{
	ssize_t _size= sendto(sock,_in_msg.c_str(),_in_msg.size(),0,(struct sockaddr*)&client,len);
	if(_size <0)
	{
		print_log(strerror(errno));
		return 1;
	}else
	{
	}
	return 0;
}
int udp_server::reliable_send_msg(const std::string &_in_msg,\
		const struct sockaddr_in& client,\
		socklen_t len)
{
	return send_msg(_in_msg,client,len);
}
int udp_server::broadcast_msg()
{
	std::string msg;
	//pool.get_msg(msg);
	std::map<std::string,struct sockaddr_in>::iterator _iter =online_user.begin();
	for(;_iter!=online_user.end();++_iter)
	{
		reliable_send_msg(msg,_iter->second,sizeof(_iter->second));
	}

}

