#! /bin/bash
#计算应用程序可用内存百分比（测评使用）
#计算公式：应用程序可用内存=MemFree + Buffers + Cached
MemFree=$(cat /proc/meminfo | awk '/^MemFree/{print $2}') #系统空闲内存
Buffers=$(cat /proc/meminfo | awk '/^Buffers/{print $2}') #缓冲区内存
Cached=$(cat /proc/meminfo | awk '/^Cached/{print $2}') #高速缓存
MemUser=$[$MemFree + $Buffers +$Cached]

MemTotal=$(cat /proc/meminfo | awk '/^MemTotal/{print $2}') #内存总量
mem_user_rate=$(awk 'BEGIN{printf"%.2f\n",'$MemUser' / '$MemTotal' * 100}')
echo $mem_user_rate #百分比
