#########################################################################
# File Name: start.sh
# Author: lauyang
# mail: 1538697392@qq.com
# Created Time: Wed 09 Mar 2016 02:48:04 AM PST
#########################################################################
#!/bin/bash
#WORK_PATH=$(pwd)
#HTTPD_PATH=$WORK_PATH/conf/httpd.conf
#HTTPD=$WORK_PATH/httpd
#
#firewall_switch=$(grep -Ei 'FIREWALL_SWITCH')
./my_httpd 127.0.0.1 8080
