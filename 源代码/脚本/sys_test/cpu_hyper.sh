#! /bin/bash
#是否支持超线程（测评使用）
cpu_cores=$(cat /proc/cpuinfo | grep "cpu cores" | awk -F ':' 'NR==1 {print $2}')
siblings=$( cat /proc/cpuinfo | grep "siblings" | awk -F ':' 'NR==1 {print $2}')
val=`expr $siblings / $cpu_cores`

if [ $siblings -eq $cpu_cores ]
then
	echo 0 #不支持超线程
fi

if [ $val -eq 2 ]
then
	echo 1 #支持超线程
fi
