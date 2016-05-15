#pragma once

#include<iostream>
#include<semaphore.h>
#include<string>
#include<vector>

#define CAPACITY 1024

class data_pool{
	public:
		data_pool();
		~data_pool();
		bool get_msg(std::string &_msg);
		bool put_msg(const std::string &_msg);
	private:
		const int pool_size;
		std::vector<std::string> pool;
		sem_t put_sem;
		sem_t get_sem;

		int start;
		int end;
};
#endif
