#!/bin/bash
#判断软件安装
iostat > /dev/null
if [ $? == 0 ];then
	echo "sysstat 已安装"
else 
	#echo "sysstat 未安装"
	#安装sysstat
	#验证密码是否正确
	echo $1 | sudo -S echo -n 2> /dev/null
	if [ $? == 0 ];then
		sudo -S apt-get -y install sysstat > /dev/null
		if [ $? == 0 ]; then
			echo "sysstat安装完成！"
		else
			echo "sysstat安装失败！"
		fi
	else 
		echo "密码输入错误！"
	fi
fi


