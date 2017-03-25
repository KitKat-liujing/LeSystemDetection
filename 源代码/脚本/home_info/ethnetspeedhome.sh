#!/bin/bash

#计算每秒有线网网速
enum=`cat /proc/net/dev |grep "eth" |wc -l`
if [ $enum -gt 0 ];then
	for((j=0;j<$enum;j++))
	do
		n=`ethtool eth$j | grep "Link detected: yes" |wc -l` > /dev/null #判断有线网是否连接
		if [ $n -eq 1 ] 
		then
			eth=eth$j

			#提取下载速度
			#求出一秒前后流量的差值,作为这一秒的下载网速, 从/proc/net/dev文件中.
			eRXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')
			sleep 1
			eRXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')

			eRX=$((${eRXnext}-${eRXpre}))

			#流量单位转换
			if [[ $eRX -lt 1024 ]];then
				eRX="${eRX}B/s"
			elif [[ $eRX -gt 1048576 ]];then
				eRX=$(echo $eRX | awk '{print $1/1048576 "MB/s"}')
			else
				eRX=$(echo $eRX | awk '{print $1/1024 "KB/s"}')
			fi	
			#输出下载速度
			#echo -e "当前下载速度为 $eRX"

			#提取上传速度
			#求出一秒前后流量的差值,作为这一秒的上传网速, 从/proc/net/dev文件中
			eTXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
			sleep 1
			eTXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
			TX=$((${eTXnext}-${eTXpre}))

			#流量单位转换	 
			if [[ $eTX -lt 1024 ]];then
				eTX="${eTX}B/s"
			elif [[ $eTX -gt 1048576 ]];then
				eTX=$(echo $eTX | awk '{print $1/1048576 "MB/s"}')
			else
				eTX=$(echo $eTX | awk '{print $1/1024 "KB/s"}')
			fi
			#输出下载速度
			echo -e "有线网下载速度 $eRX 上传速度 $eTX" 
			else
				echo "有线网未连接"
		fi
	done
else
	echo "本机没有有线网卡"
fi


