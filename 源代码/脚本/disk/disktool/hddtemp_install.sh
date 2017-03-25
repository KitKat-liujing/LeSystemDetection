#!/bin/bash

#判断软件安装
hddtemp -v > /dev/null
if [ $? -ne 0 ];then
	#echo "hddtemp 未安装"
	#安装hddtemp
	#验证密码是否正确
	echo $1 | sudo -S echo -n 2> /dev/null
	if [ $? == 0 ];then
		sudo -S apt-get -y install hddtemp > /dev/null
		if [ $? == 0 ]; then
			echo "hddtemp安装完成！"
		else
			echo "hddtemp安装失败！"
		fi
	else 
		echo "密码输入错误！"
	fi
else 
	echo "hddtemp　已安装"
fi
