#!/bin/bash

gvar=1048576
gvar1=2

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
			wla=wlan$i
			echo "无线网已连接" 
			echo "ip地址 `LC_ALL=C ifconfig wlan0 | grep 'inet addr:'| grep -v '127.0.0.1' |cut -d: -f2 | awk '{ print $1}'`" 
			###############################################################
			#packets 接收的报文总数
			wrpackets1=`cat /proc/net/dev |grep "wlan$i"|awk '{print $3}'`

			#packets 发送的报文总数
			wtpackets1=`cat /proc/net/dev |grep "wlan$i"|awk '{print $11}'`

			wtotalpackets1=$[$wrpackets1+$wtpackets1]
			###############################################################

			RXpre=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $2}')
			TXpre=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $10}')
			sleep 1
			TXnext=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $10}')
			RXnext=$(cat /proc/net/dev | grep $wla | tr : " " | awk '{print $2}')
			##################################################################
			#packets 接收的报文总数
			wrpackets2=`cat /proc/net/dev |grep "wlan$i"|awk '{print $3}'`

			#packets 发送的报文总数
			wtpackets2=`cat /proc/net/dev |grep "wlan$i"|awk '{print $11}'`

			wtotalpackets2=$[$wrpackets2+$wtpackets2]
			##################################################################

			#提取下载速度
			#求出一秒前后流量的差值,作为这一秒的下载网速, 从/proc/net/dev文件中.
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
			a=`ifconfig $wla | awk -F"[()]" NR==8'{print $2}'` #修改分隔符,并得出下载总流量

			echo -e "开机以来无线网下载总流量：$a"

			#上传总流量
			b=`ifconfig $wla | awk -F"[()]" NR==8'{print $4}'` #修改分隔符并得出上传总流量

			echo -e "开机以来无线网上传总流量：$b" 
			#############################求每秒平均网络负载################################
			wsub=$[$wtotalpackets2-$wtotalpackets1]
			wnetavg=`awk 'BEGIN{printf"%.2f\n",'$wsub' / '$gvar1'}'`
			echo "wlan$i每秒平均网络负载为：$wnetavg"
			##############################################################################
		else
			echo "无线网未连接"
			#下载总流量
			a=`ifconfig $eth | awk -F"[()]" NR==6'{print $2}'` #修改分隔符,并得出下载总流量

			echo -e "开机以来无线网下载总流量：$a"

			#上传总流量
			b=`ifconfig $eth | awk -F"[()]" NR==6'{print $4}'` #修改分隔符并得出上传总流量

			echo -e "开机以来无线上传总流量：$b" 
		fi
	done
else
	echo "本机没有无线网卡"
fi
#else
#	echo "密码输入错误!" 
#fi
echo ""
#######################################################################
#判断有多少个有线网卡,有的电脑可能有eth0、eth1
enum=`cat /proc/net/dev |grep "eth" |wc -l`
if [ $enum -gt 0 ];then
	for((j=0;j<$enum;j++))
	do
		n=`ethtool eth$j | grep "Link detected: yes" |wc -l` > /dev/null #判断有线网是否连接
		if [ $n -eq 1 ] 
		then
			eth=eth$j
			echo "有线网已连接" 
			echo "ip地址 `LC_ALL=C ifconfig $eth | grep 'inet addr:'| grep -v '127.0.0.1' |cut -d: -f2 | awk '{ print $1}'`" 
			###################################################################
			#packets 接收的报文总数
			erpackets1=`cat /proc/net/dev |grep "eth$j"|awk '{print $3}'`

			#packets 发送的报文总数
			etpackets1=`cat /proc/net/dev |grep "eth$j"|awk '{print $11}'`
			etotalpackets1=$[$erpackets1+$etpackets1]
			###################################################################

			RXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')
			TXpre=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
			sleep 1
			TXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $10}')
			RXnext=$(cat /proc/net/dev | grep $eth | tr : " " | awk '{print $2}')

			######################################################################################
			#packets 接收的报文总数
			erpackets2=`cat /proc/net/dev |grep "eth$j"|awk '{print $3}'`

			#packets 发送的报文总数
			etpackets2=`cat /proc/net/dev |grep "eth$j"|awk '{print $11}'`

			etotalpackets2=$[$erpackets2+$etpackets2]
			#######################################################################################
			#提取下载速度
			#求出一秒前后流量的差值,作为这一秒的下载网速, 从/proc/net/dev文件中.
			RX=$((${RXnext}-${RXpre}))

			RX1=$((${RX}*8))

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
			TX=$((${TXnext}-${TXpre}))

			TX1=$((${TX}*8))

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
			c=`ifconfig $eth | awk -F"[()]" NR==8'{print $2}'` #修改分隔符,并得出下载总流量
			echo -e "开机以来有线网下载总流量：$c"

			#上传总流量
			d=`ifconfig $eth | awk -F"[()]" NR==8'{print $4}'` #修改分隔符并得出上传总流量
			echo -e "开机以来有线网上传总流量：$d" 

			##############################求有线网每秒平均网络负载#####################################################
			esub=$[$etotalpackets2-$etotalpackets1]
			enetavg=`awk 'BEGIN{printf"%.2f\n",'$esub' / '$gvar1'}'`
			echo "eth$j每秒平均网络负载为：$enetavg"
			###################################################################################
			###############################求有线网上下行网络利用率#############################################
			v_judge=`ethtool eth0 |wc -l`	
			#检测是否在虚拟环境下，虚拟机和物理机ethtool命令执行出来的结果不一样，虚拟环境下无法查看有线网卡工作带宽	
			if [ $v_judge -ge 19 ];then
			ethbandwidth=`ethtool eth$j |grep "Speed:" |awk '{print int($2)}'`
			ethbandwidth1=`awk 'BEGIN{printf"%.2f\n",'$ethbandwidth' * '$gvar'}'`
			netutil1=`awk 'BEGIN{printf"%.6f\n",'$RX1' / '$ethbandwidth1' * 100 }'`
			echo "下行网络利用率为：$netutil1%"

			netutil2=`awk 'BEGIN{printf"%.6f\n",'$TX1' / '$ethbandwidth1' * 100 }'`
			echo "上行网络利用率为：$netutil2%"
			fi
			###################################################################################################

		else
			echo "有线网未连接"	
			#下载总流量
			c=`ifconfig $eth | awk -F"[()]" NR==6'{print $2}'` #修改分隔符,并得出下载总流量
			echo -e "开机以来有线下载总流量：$c"

			#上传总流量
			d=`ifconfig $eth | awk -F"[()]" NR==6'{print $4}'` #修改分隔符并得出上传总流量
			echo -e "开机以来有线上传总流量：$d" 
		fi
	done
else
	echo "本机没有有线网卡"
fi
echo ""

#机器当前的TCP连接数
ce=`cat /proc/net/snmp |grep -A1 "CurrEstab" |awk NR==2'{print int($10)}'`
echo "机器当前的TCP连接数：$ce"

#计算TCP重传率
retseg=` cat /proc/net/snmp |grep "Tcp"|grep -A1 "RetransSegs" |awk NR==2'{print int($13)}'`
outseg=`cat /proc/net/snmp |grep "Tcp"|awk NR==2'{print int($12)}'`
retrate=`awk 'BEGIN{printf"%.6f\n",'$retseg' / '$outseg'}'`
echo "TCP重传率：$retrate%"




