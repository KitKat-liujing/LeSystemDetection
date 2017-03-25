#! /bin/bash
#################
## 内存软件信息 ##
#################

#（需动态刷新）

#单位转换函数
function convert_unit()
{
	result=$1
	if [ $result -ge  1048576 ]
	then
		value=1048576 #1024*1024	
		result_gb=$(awk 'BEGIN{printf"%.2f\n",'$result' / '$value'}') #将KB转换成GB，并保留2位小数
		echo $result_gb"GB"
	elif [ $result -ge  1024 ]
	then
		value=1024 	
		result_mb=$(awk 'BEGIN{printf"%.2f\n",'$result' / '$value'}') #将KB转换成MB，并保留2位小数
		echo $result_mb"MB"
	else
		echo $result"KB"
	fi
}

#单位：KB
MemTotal=$(cat /proc/meminfo | awk '/^MemTotal/{print $2}') #内存总量
MemFree=$(cat /proc/meminfo | awk '/^MemFree/{print $2}')   #空闲内存
MemUsed=$(expr $MemTotal - $MemFree)  #已用内存

##计算内存占用率
Mem_Rate=$(awk 'BEGIN{printf"%.2f\n",'$MemUsed' / '$MemTotal' *100}') #保留小数点后2位

MemShared=$(cat /proc/meminfo | awk '/^Shmem/{print $2}') #共享内存
Buffers=$(cat /proc/meminfo | awk '/^Buffers/{print $2}') #文件缓冲区
Cached=$(cat /proc/meminfo | awk '/^Cached/{print $2}') #用于高速缓冲存储器

#活跃使用
Active=$(cat /proc/meminfo | grep "Active" | awk -F ':' 'NR==1 {print $2}' | grep -o '[0-9]\+') 
Active_anon=$(cat /proc/meminfo | grep "Active" | awk -F ':' 'NR==2 {print $2}' | grep -o '[0-9]\+')
Active_file=$(cat /proc/meminfo | grep "Active" | awk -F ':' 'NR==3 {print $2}' | grep -o '[0-9]\+')
Active_all=$[$Active + $Active_anon + $Active_file] #活跃使用总大小

#不经常使用
Inactive=$(cat /proc/meminfo | grep "Inactive" | awk -F ':' 'NR==1 {print $2}' | grep -o '[0-9]\+') 
Inactive_anon=$(cat /proc/meminfo | grep "Inactive" | awk -F ':' 'NR==2 {print $2}' | grep -o '[0-9]\+')
Inactive_file=$(cat /proc/meminfo | grep "Inactive" | awk -F ':' 'NR==3 {print $2}' | grep -o '[0-9]\+')
Inactive_all=$[$Inactive + $Inactive_anon + $Inactive_file] #不经常使用总大小

SwapTotal=$(cat /proc/meminfo | awk '/^SwapTotal/{print $2}') #交换区总量
SwapFree=$(cat /proc/meminfo | awk '/^SwapFree/{print $2}') #空闲交换区
Mapped=$(cat /proc/meminfo | awk '/^Mapped/{print $2}') #已映射

##虚拟内存
VmallocTotal=$(cat /proc/meminfo | awk '/^VmallocTotal/{print $2}') #可分配的虚拟内存总量
VmallocUsed=$(cat /proc/meminfo | awk '/^VmallocUsed/{print $2}') #已使用的虚拟内存
VmallocFree=$(expr $VmallocTotal - $VmallocUsed) #虚拟内存剩余

##将经过单位转换后的结果输出到文件
echo -e "内存总量：\t\t\t"$(convert_unit $MemTotal) 
echo -e "空闲内存：\t\t\t"$(convert_unit $MemFree) 
echo -e "已用内存：\t\t\t"$(convert_unit $MemUsed) 

echo -e "内存占用：\t\t\t"$Mem_Rate% 

echo -e "共享内存：\t\t\t"$(convert_unit $MemShared) 
echo -e "文件缓冲区：\t\t"$(convert_unit $Buffers) 
echo -e "用于高速缓冲存储器：\t\t"$(convert_unit $Cached) 
echo -e "活跃使用总大小：\t\t"$(convert_unit $Active_all) 
echo -e "不经常使用总大小：\t\t"$(convert_unit $Inactive_all) 
echo -e "交换区总大小：\t\t"$(convert_unit $SwapTotal) 
echo -e "空闲交换区：\t\t"$(convert_unit $SwapFree) 
echo -e "已映射：\t\t\t"$(convert_unit $Mapped) 

echo -e "可分配的虚拟内存总大小：\t"$(convert_unit $VmallocTotal) 
echo -e "已使用的虚拟内存：\t\t"$(convert_unit $VmallocUsed) 
echo -e "虚拟内存剩余：\t\t"$(convert_unit $VmallocFree) 
