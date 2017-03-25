
#########################################################################
# File Name: hardwareinfo.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月07日 星期三 19时23分25秒
#########################################################################
#!/bin/bash
echo $1 |sudo -S echo "" 2> /dev/null
if [ $? == 0 ]
then
	echo "Y" 
else
	echo "N"
fi


