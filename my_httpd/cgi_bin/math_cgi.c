/*************************************************************************
	> File Name: math_cgi.c
	> Author: lauyang
	> Mail: 1538697392@qq.com 
	> Created Time: Fri 11 Mar 2016 03:57:44 AM PST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void math_add(char *const data_string)//data1=aaa&data2=bbb
{
	if(!data_string)
	{
		return;
	}
	char *data1=NULL;
	char *data2=NULL;
	char *start= data_string;

	while(*start!='\0')
	{
		if(*start == '=' && data1==NULL)
		{
			data1=start+1;
			start++;
			continue;
		}
		if(*start == '&')
		{
			*start='\0';
		}
		if(*start =='=' && data1 !=NULL)
		{
			data2=start+1;
			break;
		}
		start++;
	}
	int int_data1 = atoi(data1);
	int int_data2 = atoi(data2);
	int add_res =int_data1 + int_data2;
	printf("<p>MATH ADD RESULT = %d</p>\n",add_res);
}
int main()
{
	int content_length=-1;
	char method[1024];
	char query_string[1024];
	char post_data[4096];

	memset(method,'\0',sizeof(method));
	memset(query_string,'\0',sizeof(query_string));
	memset(post_data,'\0',sizeof(post_data));

	printf("<html>\n");
	printf("<head>MATH</head>\n");
	printf("<body>\n");
	strcpy(method,getenv("REQUEST_METHOD"));
	if(strcasecmp(method,"GET")==0)
	{//get way
		strcpy(query_string,getenv("QUERY_STRING"));
		math_add(query_string);//data1=aaa&data2=vvv;
	}
	else if(strcasecmp(method,"POST")==0)
	{
		content_length = atoi(getenv("CONTENT_LENGTH"));
		int i=0;
		for(;i<content_length;++i)
		{
			read(0,&post_data[i],1);
		}
		post_data[i]='\0';
		math_add(post_data);
	}else
	{
		return 1;
	}

	printf("</body>\n");
	printf("</html>\n");

}

