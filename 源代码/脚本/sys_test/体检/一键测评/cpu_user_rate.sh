#! /bin/bash
#CPU用户占用率（测评使用）
cpu_user_rate=`top -b -n 1 | grep Cpu | awk '{print $2}'`
echo $cpu_user_rate #百分比
