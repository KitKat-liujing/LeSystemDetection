#! /bin/bash
#################
## CPU硬件信息 ##
#################

#--------------------CPU硬件信息--------------------#
##厂商
manufacturer=$(lscpu | grep "厂商" | awk -F '：  ' '{print $2}') #11个空格
echo -e "生产商：\t\t\t"$manufacturer 

##处理器名称
model_name=`cat /proc/cpuinfo | grep "model name" | awk -F ':' '{print $2}' | sort | uniq`
echo -e "名称：\t\t\t"$model_name 

##型号
model=$(lscpu | grep "型号" | awk -F '：  ' '{print $2}')
echo -e "型号：\t\t\t"$model 

##CPU个数
cpu_count=$(grep 'physical id' /proc/cpuinfo | sort -u | wc -l) #cpu个数
echo -e "CPU个数：\t\t\t "$cpu_count 

##逻辑CPU数
cpu_logic=$(cat /proc/cpuinfo | grep 'processor' | wc -l)
echo -e "逻辑CPU数：\t\t "$cpu_logic 
##主频
cpu_main_freq=$(cat /proc/cpuinfo | grep "model name" | awk -F '@' 'NR==1 {print $2}')
echo -e "主频：\t\t\t"$cpu_main_freq 

##外频
cpu_out_freq=$(cat /proc/cpuinfo | grep "cpu MHz" | awk -F ':' 'NR==1{print $2}') 
echo -e "外频：\t\t\t"$cpu_out_freq"MHz" 
##核心数量
cpu_cores=$(cat /proc/cpuinfo | grep "cpu cores" | awk -F ':' 'NR==1 {print $2}')
echo -e "核心数：\t\t\t"$cpu_cores 

##架构
architecture=$(lscpu | grep "Architecture" | awk -F ':         ' '{print $2}')
echo -e "架构：\t\t\t"$architecture 

##运行模式
run_model=$(lscpu | grep "运行模式" | awk -F '：  ' '{print $2}')
echo -e "运行模式：\t\t\t"$run_model

##处理速度（单位：百万条指令/秒）
cpu_cal_rate=$(cat /proc/cpuinfo | grep "bogomips" | awk -F ':' 'NR==1 {print $2}')
echo -e "处理速度：\t\t\t"$cpu_cal_rate"Mips" 

##缓存
cache_val=`lscpu | grep "L[0-9]" | awk -F '          ' '{print $2}' | grep -oP '\d+'` #获取缓存的值（awk以10个空格为分隔符）
sort_val=`lscpu | grep "L[0-9]" | awk '{print $1}' | grep -o '[0-9]\+' | sort -r` 
MAX_level_ch=`echo $sort_val | cut  -c 1`  #获取最大缓存的级数
MAX_level_int=`expr $MAX_level_ch + 0`   #将最大缓存级数转换成整数
L1d_cache_ch=`echo $cache_val | awk '{print $1}'` #获取L1数据缓存的大小
L1d_cache_int=`expr $L1d_cache_ch + 0`
echo -e "（1） 1级数据缓存容量：\t $L1d_cache_int"'K' 
L1i_cache_ch=`echo $cache_val | awk '{print $2}'` #获取L1指令缓存的大小
L1i_cache_int=`expr $L1i_cache_ch + 0`
echo -e "（2） 1级指令缓存容量：\t $L1i_cache_int"'K' 
plus=0
for((i=2;i<=$MAX_level_int;i++));do
	pos=$(($i + 1));
	cache_ch=`echo $cache_val | awk '{print $'$pos'}'`;
	cache_int=`expr $cache_ch + 0`;
	plus=$[$plus+$cache_int];
	echo -e "（$pos） $i级缓存容量：\t\t $cache_int"'K'  
done

total=$[$L1d_cache_int+$L1i_cache_int+$plus] #计算所有缓存总大小
echo -e "缓存总容量：\t\t $total"'K' 
echo -e "\t\t\t 共有$MAX_level_int级缓存" 

##每个核的线程数
threads_per_core=$(lscpu | grep "线程数" | grep -Eo '[0-9]+' )
((threads_total=$cpu_cores * $threads_per_core))  #计算CPU的总线程数
echo -e "CPU每个核的线程数：\t\t "$threads_per_core 
echo -e "CPU的总线程数：\t\t "$threads_total 

##对虚拟化的支持
cpu_virtual=`egrep -o '(vmx | svm)' /proc/cpuinfo | awk 'NR==1'`

if [ $cpu_virtual = "vmx" -o $cpu_virtual = "svm" ]  #判断CPU是否支持虚拟化
then
{
	if [ $cpu_virtual = "vmx" ]  #Intel提供的虚拟化
	then
		echo -e "支持虚拟化：\t\t 是  (英特尔 VT-x)"
	fi
	if [ $cpu_virtual = "svm" ] #AMD提供的虚拟化
	then
		echo -e "支持虚拟化：\t\t 是  (AMD AMD-V)" 
	fi
}
else
	echo -e "支持虚拟化：\t\t 否" 
fi

##对超线程的支持
siblings=$( cat /proc/cpuinfo | grep "siblings" | awk -F ':' 'NR==1 {print $2}')
val=`expr $siblings / $cpu_cores`

if [ $siblings -eq $cpu_cores ]
then
	echo -e "支持超线程：\t\t 否" 
fi

if [ $val -eq 2 ]
then
	echo -e "支持超线程：\t\t 是" 
fi
