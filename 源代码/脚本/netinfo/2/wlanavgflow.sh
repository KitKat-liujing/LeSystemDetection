#!/bin/bash
#测一定时间内无线网总流量和平均流量
#测试时间超过1小时提醒用户
n=3600
wnum=`cat /proc/net/dev |grep "wlan" |wc -l`
#判断本机有没有无线网卡
if [ $wnum -gt 0 ];then
	if [ $1 -gt 3600 ];then
		echo "测试时间段已超过1小时，您将要等待很长时间！"
	fi
	if [ $1 -gt 0 ]; then
		for((i=0;i<$wnum;i++))
		do
			m=`ethtool wlan$i |grep "Link detected: yes" |wc -l` > /dev/null #判断无线网是否连接
			if [ $m -eq 1 ] 
			then
				eth=wlan$i
				sec=$1
				echo "$eth "$sec"秒内的流量情况正在计算中..."
				infirst=$(awk '/'$eth'/{print $1 }' /proc/net/dev |sed 's/'$eth'://')
				outfirst=$(awk '/'$eth'/{print $10 }' /proc/net/dev)
				sumfirst=$(($infirst+$outfirst))
				sleep $sec"s"
				inend=$(awk '/'$eth'/{print $1 }' /proc/net/dev |sed 's/'$eth'://')
				outend=$(awk '/'$eth'/{print $10 }' /proc/net/dev)
				sumend=$(($inend+$outend))
				sum=$(($sumend-$sumfirst))
				#echo "$eth 网卡接口："
				#echo $sec" 秒内总流量为:"$sum"bytes"
				aver=$(($sum/$sec))
				echo "总流量："$sum"bytes，平均流量："$aver"bytes/s"
			else
				echo "无线网未连接，无法测试！"
			fi
		done
	else
		echo "测试时间输入不规范！"
	fi
else
	echo "本机没有无线网卡"
fi
