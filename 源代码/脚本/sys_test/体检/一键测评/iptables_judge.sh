#查看iptables三个基本防护规则是否存在
flag=0
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	ipnum=`sudo iptables -L |grep "prot opt source" |wc -l`
	if [ $ipnum == 3 ];then
		((flag++))
		echo $flag  #iptables防火墙基本防护已开启
	else
		echo $flag
	fi
fi
