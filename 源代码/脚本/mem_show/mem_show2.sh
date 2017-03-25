#! /bin/bash
#################
## 内存硬件信息 ##
#################
#（需要root权限）

###已插入内存条的硬件信息###
#需要密码，验证密码是否正确  （问题：生产商、Type未获取、实际的内存插槽数未获取）
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ]
then 
	###已插入内存条的硬件信息###	
	max_capacity=`echo $1 | sudo -S dmidecode -t memory | grep "Maximum Capacity" | awk -F ':' '{print $2}' | grep -o '[0-9]\+'`
	#获取支持的最大内存
	echo -e "最大内存支持：\t\t $max_capacity""GB" 
	#echo -e #换行
	#MAX=`echo $1 | sudo -S dmidecode -t memory | grep "Number Of Devices" | awk -F ':' '{print $2}'`
	#echo $MAX
	MAX=4
	i=0
	mem_count=0 
	total=0
	value=1024

	while(($i < $MAX))
	do
		((i++))	
		status=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Size" | awk -F ': ' 'NR=='$i'{print $2}' | grep -io '[a-z]\+'`	
		
		if test "$status" = "MB" #检测内存条的插入状态
		then
			((mem_count++)) #计算实际插入的内存条个数
			line=$i #记录已插入的内存条信息所在行数，便于信息映射

			echo -e "\t  内存条$mem_count信息" 
			
			###已插入内存条信息###
			#规格
			form_factor=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Form Factor" | awk -F ':' 'NR=='$line'{print $2}'` 
			echo -e "规格：\t\t\t$form_factor" 
			
			#类型
			type=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Type Detail" | awk -F ':' 'NR=='$line'{print $2}'` 
			echo -e "类型：\t\t\t$type" 
			
			#内存插槽号
			locator=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Locator" | grep -v "Bank Locator" | awk -F ':' 'NR=='$line'{print $2}'` 
			echo -e "内存插槽号：\t\t$locator" 

			#序列号
			serial_number=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Serial Number" | awk -F ':' 'NR=='$line'{print $2}'` 
			echo -e "序列号：\t\t\t$serial_number" 			
			
			#内存总线位数（数值）	  		
			total_width=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Total Width" | awk -F ':' 'NR=='$line'{print $2}' | grep -o '[0-9]\+'`
			echo -e "内存总线位数：\t\t "$total_width"bits" 


			#获取插入的内存条大小（数值）
			size=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Size" | awk -F ':' 'NR=='$line'{print $2}' | grep -o '[0-9]\+'`
			total=$[$size + $total] #计算插入内存条的总大小
			if [ $size -ge 1024 ]
			then
				size_gb=$(awk 'BEGIN{printf"%.2f\n",'$size' / '$value'}') #将MB转换成GB，并保留2位小数
				echo -e "大小：\t\t\t "$size_gb"GB" 
			else		
				echo -e "大小：\t\t\t "$size"MB" 
			fi 

			#获取插入的内存核心频率（数值）
			speed=`echo $1 | sudo -S dmidecode -t memory | grep -A17 "Memory Device$" | grep "Speed" | awk -F ':' 'NR=='$line'{print $2}' | grep -o '[0-9]\+'`

			if [ "$speed" != "" ] #判断是否在虚拟机中，不是才可以进行计算
			then			
				echo -e "核心频率：\t\t\t "$speed"MHz" 

				#计算内存带宽
				#计算公式（简化）：内存核心频率 * 内存总线位数
				bandwidth_Mbit=$[$speed * $total_width]
				bandwidth_MB=`expr $bandwidth_Mbit / 8`

				if [ $bandwidth_MB -ge $value ]
				then
					bandwidth_GB=$(awk 'BEGIN{printf"%.2f\n",'$bandwidth_MB' / '$value'}') #将MB转换成GB，并保留2位小数
					echo -e "内存带宽：\t\t\t "$bandwidth_GB"GB/s"    
				else		
					echo -e "内存带宽：\t\t\t "$bandwidth_MB"MB/s" 
				fi 
			else
				echo -e "当前在虚拟机中，无法获取核心频率！"
				echo -e "无法计算内存带宽！"
			fi
							
			#echo -e  #换行
		fi
	done

	if [ $mem_count -eq 0 ]
	then
		echo "warning:未插入内存条！"  #有的主板会集成内存，可能会有未插入内存的情况
	else
		echo -e "已插入的内存条数：\t\t $mem_count" 
		#计算物理内存总大小
		if [ $total -ge 1024 ]
		then
			total_gb=$(awk 'BEGIN{printf"%.2f\n",'$total' / '$value'}') #将MB转换成GB，并保留2位小数
			echo -e "物理内存总大小：\t\t "$total_gb"GB" 
		else		
			echo -e "物理内存总大小：\t\t "$total"MB" 
		fi
		echo "（警告：软件检测结果以实际运行环境为主！）" 
	fi
fi
