#!/bin/bash
echo $1 | sudo -S echo "" 2> /dev/null
if [ $? == 0 ];then
	ethtool wlan0 | grep "Link detected: yes" > /dev/null #判断是否是无线网
	if [ $? -eq 0 ] #判断网卡
	then
		eth=wlan0
		echo "当前网络类型：无线网" > netspeed
		echo "ip地址 `LC_ALL=C ifconfig wlan0 | grep 'inet addr:'| grep -v '127.0.0.1' |cut -d: -f2 | awk '{ print $1}'`" 
	else
		eth=eth0
		echo "当前网络类型：有线网" 
		echo "ip地址 `LC_ALL=C ifconfig eth0 | grep 'inet addr:'| grep -v '127.0.0.1' |cut -d: -f2 | awk '{print $1}'`" 
	fi

	#提取下载速度
	#求出一秒前后流量的差值,作为这一秒的下载网速, 从/proc/net/dev文件中.
	RXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')
	#sleep 1
	RXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')

	RX=$((${RXnext}-${RXpre}))

	#流量单位转换
	if [[ $RX -lt 1024 ]];then
		RX="${RX}B/s"
	elif [[ $RX -gt 1048576 ]];then
		RX=$(echo $RX | awk '{print $1/1048576 "MB/s"}')
	else
		RX=$(echo $RX | awk '{print $1/1024 "KB/s"}')
	fi	
	#输出下载速度
	echo -e "当前下载速度为 $RX" 

	#提取上传速度
	#求出一秒前后流量的差值,作为这一秒的上传网速, 从/proc/net/dev文件中
	TXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
	#sleep 1
	TXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
	TX=$((${TXnext}-${TXpre}))
	#流量单位转换	 
	if [[ $TX -lt 1024 ]];then
		TX="${TX}B/s"
	elif [[ $TX -gt 1048576 ]];then
		TX=$(echo $TX | awk '{print $1/1048576 "MB/s"}')
	else
		TX=$(echo $TX | awk '{print $1/1024 "KB/s"}')
	fi
	#输出下载速度
	echo -e "当前上传速度为 $TX" 


	#下载总流量
	a=`ifconfig $eth | awk -F"[()]" NR==8'{print $2}'` #修改分隔符,并得出下载总流量

	echo -e "下载总流量：$a"

	#上传总流量
	b=`ifconfig $eth | awk -F"[()]" NR==8'{print $4}'` #修改分隔符并得出上传总流量

	echo -e "上传总流量：$b" 
else
	echo "密码输入错误!"
fi
