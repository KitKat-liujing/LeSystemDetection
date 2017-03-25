#! /bin/bash
#io等待占用CPU时间的百分比（测评使用）
iowait_rate=`top -b -n 1 | grep Cpu | awk '{print $10}'` #（-b -n 1 表示只需要1次的输出结果）
echo $iowait_rate #百分比 
