#! /bin/bash
#是否支持虚拟化（测评使用）
cpu_virtual=`egrep -o '(vmx | svm)' /proc/cpuinfo | awk 'NR==1'`

if [ $cpu_virtual = "vmx" -o $cpu_virtual = "svm" ]  #判断CPU是否支持虚拟化
then
{
	if [ $cpu_virtual = "vmx" ]  #Intel提供的虚拟化
	then
		echo 2
	fi
	if [ $cpu_virtual = "svm" ] #AMD提供的虚拟化
	then
		echo 1
	fi
}
else
	echo 0 #不支持虚拟化
fi
