echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then

	#lshw命令测试有线网卡
	sudo lshw > net_lshw
	if [ $? == 0 ];then
		num=`cat net_lshw |grep "description: Ethernet interface" |wc -l`
		if [ $num -ne 0 ];then
			echo "本机网卡硬件信息"
			echo -e "类型：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep " description:" |awk -F: '{print $2}'`（以太网接口）"
			echo -e "产品：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "product:" |awk -F: '{print $2}'`"
			echo -e "供应商：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "vendor:" |awk -F: '{print $2}'`"
			echo -e "逻辑名称：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "logical name:" |awk -F: '{print $2}'`"
			echo -e "版本：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "version:" |awk -F: '{print $2}'`"
			echo -e "串口：\t\t\t `cat net_lshw |grep -A13 "description: Ethernet interface" |grep "serial:" |awk '{print $2}'`"
			echo -e "带宽容量：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "capacity:" |awk -F: '{print $2}'`"
			echo -e "宽度：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "width:" |awk -F: '{print $2}'`"
			echo -e "时钟：\t\t\t`cat net_lshw |grep -A13 "description: Ethernet interface" |grep "clock:" |awk -F: '{print $2}'`"
		fi
		echo ""

		num1=`cat net_lshw |grep "description: Wireless interface" |wc -l`
		if [ $num1 -ne 0 ];then
			#lshw命令检测无线网卡信息
			echo -e "类型：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep " description:" |awk -F: '{print $2}'`（无线接口）"
			echo -e "产品：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "product:" |awk -F: '{print $2}'`"
			echo -e "供应商：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "vendor:" |awk -F: '{print $2}'`"
			echo -e "逻辑名称：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "logical name:" |awk -F: '{print $2}'`"
			echo -e "版本：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "version:" |awk -F: '{print $2}'`"
			echo -e "串口：\t\t\t `cat net_lshw |grep -A13 "description: Wireless interface" |grep "serial:" |awk '{print $2}'`"
			echo -e "宽度：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "width:" |awk -F: '{print $2}'`"
			echo -e "时钟：\t\t\t`cat net_lshw |grep -A13 "description: Wireless interface" |grep "clock:" |awk -F: '{print $2}'`"
		fi
	else
		echo "未检测到本机网卡硬件信息，请检查USB口是否插入U盘或者其它设备，如果有请拔除" #实训过程中发现系统自带的命令lshw有bug，我的金士顿3.0优盘插着时，这个命令就输不出任何东西
		echo "系统内部错误，系统lshw命令异常，无法检测本机网卡硬件信息"
	fi
	rm -rf net_lshw
fi

