#########################################################################
# File Name: is_install.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月11日 星期日 15时51分57秒
#########################################################################
#!/bin/bash
#判断软件安装
hddtemp -v > /dev/null
if [ $? == 0 ];then
	echo "Y"
else 
	echo "N"
fi
