##计算cpu利用率（需动态刷新）
#计算公式：
#total_0USER[0]+NICE[0]+SYSTEM[0]+IDLE[0]+IOWAIT[0]+IRQ[0]+SOFTIRQ[0]
#total_1=USER[1]+NICE[1]+SYSTEM[1]+IDLE[1]+IOWAIT[1]+IRQ[1]+SOFTIRQ[1]
#cpu usage=(IDLE[0]-IDLE[1]) / (total_0-total_1) * 100
CPULOG_1=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
SYS_IDLE_1=$(echo $CPULOG_1 | awk '{print $4}')
Total_1=$(echo $CPULOG_1 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

sleep 2

CPULOG_2=$(cat /proc/stat | grep 'cpu ' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')
SYS_IDLE_2=$(echo $CPULOG_2 | awk '{print $4}')
Total_2=$(echo $CPULOG_2 | awk '{print $1+$2+$3+$4+$5+$6+$7}')

SYS_IDLE=`expr $SYS_IDLE_2 - $SYS_IDLE_1`

Total=`expr $Total_2 - $Total_1`
SYS_USAGE=`expr $SYS_IDLE/$Total*100 |bc -l`

SYS_Rate=`expr 100-$SYS_USAGE |bc -l`

Disp_SYS_Rate=`awk 'BEGIN{printf"%.2f\n",'$SYS_Rate' / 1}'`
echo $Disp_SYS_Rate
