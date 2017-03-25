#!/bin/bash
#判断软件安装
iostat > /dev/null
if [ $? -ne 0 ];then
	echo "sysstat 未安装"
else 
	#echo "sysstat 已安装"
#卸载sysstat
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	sudo apt-get -y remove sysstat > /dev/null
	if [ $? == 0 ]; then
		echo "sysstat卸载成功！"
	else 
		echo "sysstat卸载失败！"
	fi
else 
	echo "密码输入错误！"
fi
fi
