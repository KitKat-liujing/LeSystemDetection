#! /bin/bash
#################
## CPU软件信息 ##
#################

#（需动态刷新）

##计算cpu利用率
#计算公式：
#total_0USER[0]+NICE[0]+SYSTEM[0]+IDLE[0]+IOWAIT[0]+IRQ[0]+SOFTIRQ[0]
#total_1=USER[1]+NICE[1]+SYSTEM[1]+IDLE[1]+IOWAIT[1]+IRQ[1]+SOFTIRQ[1]
#cpu usage=(IDLE[0]-IDLE[1]) / (total_0-total_1) * 100
CPULOG_1=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
SYS_IDLE_1=$(echo $CPULOG_1 | awk '{print $4}')
Total_1=$(echo $CPULOG_1 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

sleep 1

CPULOG_2=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
SYS_IDLE_2=$(echo $CPULOG_2 | awk '{print $4}')
Total_2=$(echo $CPULOG_2 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

SYS_IDLE=`expr $SYS_IDLE_2 - $SYS_IDLE_1`

Total=`expr $Total_2 - $Total_1`
SYS_USAGE=`expr $SYS_IDLE/$Total*100 |bc -l`

SYS_Rate=`expr 100-$SYS_USAGE |bc -l`

#Disp_SYS_Rate=`expr "scale=2; $SYS_Rate/1" |bc`
Disp_SYS_Rate=$(awk 'BEGIN{printf"%.2f\n",'$SYS_Rate' / 1}')
echo -e "CPU占用：\t\t\t\t $Disp_SYS_Rate%" 
echo ""
##计算可运行队列的线程数
cpu_count=$(grep 'physical id' /proc/cpuinfo | sort -u | wc -l) #cpu个数
loadavg_1min=$( cat /proc/loadavg | awk '{print $1}') #cpu一分钟平均负载
task_per_cpu=$(awk 'BEGIN{printf"%.2f\n",'$loadavg_1min' / '$cpu_count'}')
#每个cpu的当前任务数
echo -e "可运行队列的线程数：\t\t\t" $task_per_cpu 
echo ""
##用户占用率
user_rate=`top -b -n 1 | grep Cpu | awk '{print $2}'`
echo -e "用户占用率：\t\t\t "$user_rate% 
echo ""
##系统占用率
sys_rate=`top -b -n 1 | grep Cpu | awk '{print $4}'`
echo -e "系统占用率：\t\t\t "$sys_rate% 
echo ""
##io等待占用CPU时间的百分比
iowait_rate=`top -b -n 1 | grep Cpu | awk '{print $10}'` #（-b -n 1 表示只需要1次的输出结果）
echo -e "IO等待占用率：\t\t\t "$iowait_rate%  
echo ""
#从磁盘交换到内存的交换页
si=`top -b -n 1 | grep Cpu | awk '{print $14}'`
echo -e "从磁盘交换到内存的页占用率：\t\t "$si% 
echo ""
#从内存交换到磁盘的交换页
so=`top -b -n 1 | grep Cpu | awk '{print $16}'`
echo -e "从内存交换到磁盘的页占用率：\t\t "$so% 
