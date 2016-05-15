#include"data_pool.h"
//a cicrl buff queue
//size is CAPACITY


data_pool::data_pool()
	:pool(CAPACITY),
	start(0),
	end(0)
{
	sem_init(&put_sem,0,CAPACITY);
	sem_init(&get_sem,0,0);
}
void data_pool::put_msg(const std::string &_msg)
{
	sem_wait(&put_sem);//P
	pool[end] ==_msg;
	end++;
	end = end %CAPACITY;
	sem_post(&get_sem);//V

}
const std::string& data_pool::get_msg(std::string &_out_msg)
{
	sem_wait(&get_sem);//P
	_out_msg = pool[start];
	++start;
	start %=CAPACITY;
	sem_post(&put_msg);//V
}
data_pool:~data_pool()
{}
