FIND_PATH= -I/home/lauyang/project/my_httpd/sql_connect -I/home/lauyang/project/my_httpd/sql_connect/mysql_lib/include/mysql -L/home/lauyang/project/my_httpd/sql_connect/mysql_lib/lib/mysql -lmysqlclient

.PHONY:all
all:debug_cgi math_cgi show_student_info register_cgi
debug_cgi:debug_cgi.c
	gcc -o $@ $^
math_cgi:math_cgi.c
	gcc -o $@ $^
show_student_info:show_student_info.cpp /home/lauyang/project/my_httpd/sql_connect/sql_connect.cpp
	g++ -o $@ $^ $(FIND_PATH) -ldl -lrt
register_cgi:register_cgi.cpp /home/lauyang/project/my_httpd/sql_connect/sql_connect.cpp 
	g++ -o $@ $^ $(FIND_PATH) -g -ldl -lrt 

.PHONY:output
output:
	cp debug_cgi ../output/htdocs/cgi_bin
	cp math_cgi  ../output/htdocs/cgi_bin
	cp show_student_info ../output/htdocs/cgi_bin
	cp register_cgi ../output/htdocs/cgi_bin
.PHONY:clean
clean:
	rm -rf debug_cgi math_cgi show_student_info register_cgi
