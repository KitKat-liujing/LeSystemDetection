#!/bin/bash
#正在进行的I/O数，I/O队列中请求数(running),一个磁盘队列值为2-3最佳，默认队列为128个长度
#第9个域：正在处理的输入/输出请求数--I/O的当前进度，只有这个域应该是0。当请求被交给适当的request_queue_t时增加和请求完成时减小
running=`cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($12)}'`
echo "$running"
