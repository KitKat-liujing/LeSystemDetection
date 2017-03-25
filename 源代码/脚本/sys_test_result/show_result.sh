#! /bin/bash
#测评结果的显示

function show_result()
{
	name=$1
	res=$2
	if [ $name = "cpuuser" ] #CPU用户利用率的测评结果   
	then
		echo $res%
	elif [ $name = "cpusys" ] #CPU系统利用率的测评结果  
	then
		echo $res%
	elif [ $name = "cputhreads" ] #CPU可运行队列的线程数的测评结果  
	then
		echo $res
	elif [ $name = "cpuiowait" ] #CPU：IO等待的测评结果   
	then
		echo $res%
	elif [ $name = "cpuvirtual" ] #CPU是否支持虚拟化的测评结果  
	then
		if [ $res -eq 1 ] 
		then 
			echo "是  (AMD AMD-V)" #AMD提供的虚拟化
		elif [ $res -eq 2 ]
		then
			echo "是  (英特尔 VT-x)" #Intel提供的虚拟化
		else
			echo "否" 
		fi
	elif [ $name = "cpuhyper" ] #CPU是否支持超线程的测评结果    
	then
		if [ $res -eq 1 ]
		then
			echo "是"
		else
			echo "否"
		fi
	elif [ $name = "memuser" ] #应用程序可用内存占用率的测评结果   
	then
		echo $res%
	elif [ $name = "ioresponse" ] #平均IO响应时间的测评结果    
	then
		echo $res"ms"
	elif [ $name = "iorequest" ] #IO队列请求数的测评结果    
	then
		echo $res
	elif [ $name = "ioutil" ] #一秒中有百分之多少时间用于IO操作的测评结果   
	then
		echo $res%
	elif [ $name = "iojunk" ] #垃圾文件的测评结果    
	then
		if [ $res -eq 1 ]
		then
			echo "您的磁盘垃圾已超过1G，最好及时清理！"
		else
			echo "没有过量垃圾"
		fi
	elif [ $name = "iocheck" ] #磁盘损坏率的测评结果  
	then
		echo $res%
	elif [ $name = "ioopt" ] #平均每次设备IO操作的服务时间的评测结果   
	then
		echo $res"ms"
	elif [ $name = "netarp" ] #ARP攻击风险率的评测结果    
	then
		echo $res%
	elif [ $name = "netfirefox" ] #火狐cookies跟踪的评测结果   
	then
		if [ $res -eq 1 ]
		then
			echo "存在cookie跟踪"
		else
			echo "没有cookie跟踪"
		fi
	elif [ $name = "netgoogle" ] #谷歌cookies跟踪的评测结果    
	then
		if [ $res -eq 1 ]
		then
			echo "存在cookie跟踪"
		else
			echo "没有cookie跟踪"
		fi
	elif [ $name = "nethistory" ] #谷歌历史记录的评测结果    
	then
		if [ $res -eq 1 ]
		then
			echo "检测到存在google-chrome历史跟踪记录，个人隐私有泄露危险"
		else
			echo "检测到不存在google-chrome历史跟踪记录"
		fi
	elif [ $name = "recentused" ] #用户最近使用文档跟踪记录的评测结果    
	then
		if [ $res -eq 1 ]
		then
			echo "有"
		else
			echo "无"
		fi
	elif [ $name = "netinitarp" ] #ARP是否开机自启动的评测结果    
	then
		if [ $res -eq 1 ]
		then
			echo "已开启"
		else
			echo "未开启"
		fi
	elif [ $name = "starttime" ] #开机时间的评测结果    
	then
		if [ $res -ge 60 ]
		then
			min=$[$res / 60] 
			sec=$[$res % 60] 
			
			if [ $sec -eq 0 ]
			then
				echo "$min分钟"
			else
				echo "$min分$sec秒" 
			fi
		else
			echo "$res秒"
		fi
	else
		exit 1			
	fi
}

str=$1
param=$2

if [ $# -ne 2 ] #判断传入的参数个数
then
	exit 1
else
	show_result $str $param
fi
