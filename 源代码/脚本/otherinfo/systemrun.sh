#!/bin/bash
		#非root权限显示的信息
		#打印出当前系统已经运行的时间
		cat /proc/uptime| awk -F. '{
		run_days=$1 / 86400;
		run_hour=($1 % 86400)/3600;
		run_minute=($1 % 3600)/60;
		run_second=$1 % 60;printf("系统已运行：\t\t\t%d天%d时%d分%d秒\n",run_days,run_hour,run_minute,run_second)}'
		echo ""
		#进程总数
		process=`ps aux | wc -l`
		echo -e "进程总数：\t\t\t\t$process" 

		#僵尸进程数
		zombie_process=`ps -eal | awk '{ if ($2 == "Z") {print $4}}' | wc -l`
		echo -e "僵尸进程数：\t\t\t$zombie_process"

		#获取帧缓冲的个数
		buf=`cat /proc/fb | awk '{print $1}' | head -1`
		echo -e "帧缓冲个数为：\t\t\t"$buf"个"

		#打开文件数
		open_files=`lsof | wc -l`
		echo -e "打开文件总数：\t\t\t$open_files" 

		#获取系统启动以来发生的中断总的次数
		irq=`cat /proc/stat | grep "intr" | awk '{print $2}'`
		echo -e "系统启动以来发生中断的次数：\t\t"$irq"次"
		#获取系统启动以来cpu上下文交换的次数
		ch=`cat /proc/stat | grep "ctxt" | awk '{print $2}'`
		echo -e "系统启动以来cpu上下文交换次数:\t\t$ch"

		echo ""
		#获取当前队列的任务个数
		que=`cat /proc/stat | grep "procs_running" | awk '{print $2}'`
		echo -e "当前队列任务的个数：\t\t\t"$que"个"
		#获取被阻塞任务的个数
		block=`cat /proc/stat | grep "procs_blocked" | awk '{print $2}'`
		echo -e "当前被阻塞任务的个数：\t\t$block"
		#获取系统启动以来所创建的任务的个数
		task=`cat /proc/stat | grep "processes" | awk '{print $2}'`
		echo -e "系统启动以来创建任务数：\t\t"$task"个"

		echo ""
		#获取虚拟文件系统的个数
		vfs=`cat /proc/filesystems | grep nodev | wc -l`
		echo -e "虚拟文件系统的个数为：\t\t"$vfs"个"

		#获取可供使用的文件系统类型个数
		fs=`cat /proc/filesystems | wc -l`
		echo -e  "系统可供使用的文件系统类型数:\t\t"$fs""
		echo ""




