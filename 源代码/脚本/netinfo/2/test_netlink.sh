#!/bin/bash
# 无网返回0，有线网连接返回1，无线网连接返回2，有线网和无线网都连接返回3(有的电脑有线和无线都可以连接)
eth_link=0
eth_unlink=0
wlan_link=0
wlan_unlink=0

#判断有多少个有线网卡,有的电脑可能有eth0、eth1
enum=`cat /proc/net/dev |grep "eth" |wc -l`
if [ $enum -gt 0 ];then
	for((j=0;j<$enum;j++))
	do
		n=`ethtool eth$j | grep "Link detected: yes" |wc -l` > /dev/null #判断有线网是否连接
		if [ $n -eq 1 ] 
		then
			eth_link=1
			#echo "有线网已连接" 
		else
			eth_unlink=1
			#echo "有线网未连接"
		fi
	done
else
	echo "本机没有有线网卡"
fi

#############################################################################
#判断有多少个无线网卡,有的电脑可能有wlan0、wlan1
wnum=`cat /proc/net/dev |grep "wlan" |wc -l`
#判断本机有没有无线网卡
if [ $wnum -gt 0 ];then
	#循环求每个无线网卡的网速
	for((i=0;i<$wnum;i++))
	do
		m=`ethtool wlan$i |grep "Link detected: yes" |wc -l` > /dev/null #判断无线网是否连接
		if [ $m -eq 1 ] 
		then
			wlan_link=1
			#echo "无线网已连接" 
		else
			wlan_unlink=1
			#echo "无线网未连接"
		fi
	done
else
	echo "本机没有有线网卡"
fi

#无网返回0，有线网连接返回1，无线网连接返回2，有线网和无线网都连接返回3(有的电脑有线和无线都可以连接)
if [ $eth_unlink == 1 -a $wlan_unlink == 1 ];then
echo 0
elif [ $eth_link == 1 -a $wlan_unlink == 1 ];then
echo 1
elif [ $eth_unlink == 1 -a $wlan_link == 1 ];then
echo 2
elif [ $eth_link == 1 -a $wlan_link == 1 ];then
echo 3
fi




