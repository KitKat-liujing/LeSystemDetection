#########################################################################
# File Name: firewall.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月21日 星期三 21时25分34秒
#########################################################################
#!/bin/bash
iptabnum=0
#查看防火墙状态
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	#适应中文的系统
	ufwnum=`sudo ufw status |grep "active" |wc -l`
	if [ $ufwnum == 0 ];then
		echo "ufw防火墙`sudo ufw status`"
	else
		#适应英文的系统
		ufwstatus=`sudo ufw status |awk '{print $2}'`
		if [ $ufwstatus = "active" ];then
			echo "ufw防火墙状态：激活"
		elif [ $ufwstatus = "inactive" ];then
			echo "ufw防火墙状态：不活动"
		fi
	fi

	echo " "
	inputnum=`sudo iptables -L |grep "Chain INPUT" |wc -l`
	if [ $inputnum -ne 0 ];then
		((iptabnum++))

	fi
	forwardnum=`sudo iptables -L |grep "Chain FORWARD" |wc -l`
	if [ $forwardnum -ne 0 ];then
		((iptabnum++))

	fi
	outputnum=`sudo iptables -L |grep "Chain OUTPUT" |wc -l`
	if [ $outputnum -ne 0 ];then
		((iptabnum++))

	fi
	if [ $iptabnum -ge 3 ];then
		echo "iptables防火墙默认防护已开启"
	else
		echo "iptables默认防护规则不完整"
	fi
	#echo "采用tcp协议，处于监听状态进程的绑定端口及IP信息如下："
	#sudo netstat -lntp
	#else
	#echo "采用tcp协议，处于监听状态进程的绑定端口及IP信息如下："
	#netstat -lntp
fi
