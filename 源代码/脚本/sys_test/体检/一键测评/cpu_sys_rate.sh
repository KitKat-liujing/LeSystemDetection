#! /bin/bash
#CPU系统占用率（测评使用）
sys_rate=`top -b -n 1 | grep Cpu | awk '{print $4}'`
echo $sys_rate #百分比
