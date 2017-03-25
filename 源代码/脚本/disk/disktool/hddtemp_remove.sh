#!/bin/bash
#判断软件安装
hddtemp -v > /dev/null
if [ $? == 0 ];then
	#echo "hddtemp 已安装"
	#卸载hddtemp
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	sudo -S dpkg -r hddtemp > /dev/null
	if [ $? == 0 ]; then
		echo "hddtemp卸载成功！"
	else 
		echo "hddtemp卸载失败！"
	fi
else 
	echo "密码输入错误！"
fi
else 
	echo "hddtemp 未安装"

fi

