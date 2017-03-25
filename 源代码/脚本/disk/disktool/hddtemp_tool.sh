#########################################################################
# File Name: disk_speed.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月06日 星期二 20时06分08秒
#########################################################################
#!/bin/bash
#hdparm工具磁盘读写速度
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	#判断软件安装
    hddtemp -v > /dev/null
	if [ $? -ne 0 ];then
		echo "温度测试工具hddtemp安装失败（可能软件源有问题），无法检测"
	else 
		sudo hddtemp /dev/sda >hddtemp_test
		c=`cat hddtemp_test | awk '{print int($3)}'`
		if [ $c -lt 59 ];then
			echo "磁盘当前温度为：`cat hddtemp_test | awk -F: '{print $3}'` （硬盘工作温度正常！）" >hddtempinfo
		fi
		if [ $c -ge 70 ];then
			echo "磁盘当前温度为：`cat hddtemp_test | awk -F: '{print $3}'` （硬盘工作温度超过极限！）">hddtempinfo
		fi
	cat hddtempinfo
	rm hddtempinfo
	rm hddtemp_test
	fi
	
else
	echo "密码输入错误！"
fi
