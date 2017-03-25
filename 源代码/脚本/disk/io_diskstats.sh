#!/bin/bash
#IO性能指标

#/proc/uptime第一列输出的是，系统启动到现在的时间（以秒为单位）
ut=$(cat /proc/uptime |awk '{print $1}')
var=2
ms=1000

#第1个域：读完成次数 ----- 读磁盘的次数，成功完成读的总次数(rio)
rio=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($4)}')


#第5个域：写完成次数 ----写完成的次数，成功写完成的总次数(wio)
wio=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($8)}')


#第2个域：合并读完成次数(rmerge)。为了效率可能会合并相邻的读和写。从而两次4K的读在它最终被处理到磁盘上之前可能会变成一次8K的读，才被计数（和排队），因此只有一次I/O操作。这个域使你知道这样的操作有多频繁
rmerge=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($5)}')


#第6个域：合并写完成次数(wmerge)-----合并写次数。
wmerge=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($9)}')


#第3个域：读扇区的次数(rsect)，成功读过的扇区总次数。
rsect=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($6)}')


#第7个域：写扇区次数(wsect)---- 写扇区的次数，成功写扇区总次数
wsect=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($10)}')


#第4个域：读花费的毫秒数(ruse)，这是所有读操作所花费的毫秒数。
ruse=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($7)}')
#echo "读数据花费的时间（从系统启动时的累积值）：$ruse ms"

#第8个域：写操作花费的毫秒数(wuse)---  写花费的毫秒数，这是所有写操作所花费的毫秒数
wuse=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($11)}')
#echo "写数据花费的时间（从系统启动时的累积值）：$wuse ms"

#第9个域：正在处理的输入/输出请求数(running)--I/O的当前进度，只有这个域应该是0。当请求被交给适当的request_queue_t时增加和请求完成时减小
running=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($12)}')


#第10个域：输入/输出操作花费的毫秒数(use)--花在I/O操作上的毫秒数，这个域会增长只要field 9不为0。
use=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($13)}')

#第11个域：输入/输出操作花费的加权毫秒数(aveq)，加权，花在I/O操作上的毫秒数，在每次I/O开始，I/O结束，I/O合并时这个域都会增加。这可以给I/O完成时间和存储那些可以累积的提供一个便利的测量标准。
aveq=$(cat /proc/diskstats |grep " 0 sda " |awk NR==1'{print int($14)}')

#rsec/s
rsects=$(awk 'BEGIN{printf"%.2f\n",'$rsect' / '$ut'}')
echo -e "每秒读扇区数：\t\t\t    $rsects rsect/s"

#wsec/s
wsects=$(awk 'BEGIN{printf"%.2f\n",'$wsect' / '$ut'}')
echo -e "每秒写扇区数：\t\t\t    $wsects wsect/s"


#rkB/s:每秒读K字节数,是 rsect/s 的一半
rkbs=$(awk 'BEGIN{printf"%.2f\n",'$rsects' / '$var'}')
echo -e "每秒读K字节数：\t\t\t    $rkbs rkB/s"

#wkB/s:每秒写K字节数,是 wsect/s 的一半
wkbs=$(awk 'BEGIN{printf"%.2f\n",'$wsects' / '$var'}')
echo -e "每秒写K字节数：\t\t\t    $wkbs wkB/s"

#rio/s
rios=$(awk 'BEGIN{printf"%.2f\n",'$rio' / '$ut'}')
echo -e "每秒完成的读 I/O 设备次数：\t\t     $rios r/s"

#wio/s
wios=$(awk 'BEGIN{printf"%.2f\n",'$wio' / '$ut'}')
echo -e "每秒完成的写 I/O 设备次数：\t\t     $wios w/s"

#rrqm/s
rmerges=$(awk 'BEGIN{printf"%.2f\n",'$rmerge' / '$ut'}')
echo -e "每秒进行合并的读操作数目：\t\t     $rmerges rmerge/s"

#wrqm/s
wmerges=$(awk 'BEGIN{printf"%.2f\n",'$wmerge' / '$ut'}')
echo -e "每秒进行合并的写操作数目：\t\t     $wmerges wmerge/s"


#%util: 一秒中有百分之多少的时间用于 I/O 操作，或者说一秒中有多少时间 I/O 队列是非空的，即 delta(use)/s/1000 (因为use的单位为毫秒)
util=$(awk 'BEGIN{printf"%.2f\n",'$use' / '$ut' / 1000 * 100}')
util1=$(awk 'BEGIN{printf"%.0f\n",'$use' / '$ut' / 1000 * 100}')
if [ $util1 -ge 70 -a $util1 -lt 95 ];then
		echo -e "一秒中有百分之多少的时间用于 I/O 操作\t     ：$util%（I/O压力比较大）"
	elif [ $util1 -ge 95 -a $util1 -lt 100 ];then
		echo -e "一秒中有百分之多少的时间用于 I/O 操作：\t     $util%（I/O请求太多，磁盘可能存在瓶颈）"
	fi
echo -e "一秒中有百分之多少的时间用于I/O操作：\t     $util%"

#avgrq-sz:平均每次设备I/O操作的数据大小 (扇区)(IO Chunk Size)，即 (rsect+wsect)/(rio+wio)，平均每次设备I/O操作的数据大小(扇区)
rwsect=$[$rsect+$wsect]
rwio=$[$rio+$wio]
avgrq=$(awk 'BEGIN{printf"%.2f\n",'$rwsect' / '$rwio'}')
echo -e "平均单次IO大小：\t\t\t     $avgrq"

#await:平均每次设备I/O操作的等待时间 (毫秒)(IO Response Time),包括在请求队列中的时间和响应消耗时间，即 (ruse+wuse)/(rio+wio)
rwuse=$[$ruse+$wuse]
await=$(awk 'BEGIN{printf"%.2f\n",'$rwuse' / '$rwio'}')
echo -e "平均IO响应时间：\t\t\t     $await ms"

#avgqu-sz:平均I/O队列长度，对磁盘请求的平均队列长度,即 aveq/1000 (因为aveq的单位为毫秒)avgqu-sz=await*(r/s+w/s)/1000 (队列长度)  
rwios=$(echo "scale=2;$rios + $wios"|bc)
avgqu=$(awk 'BEGIN{printf"%.2f\n",'$await' * '$rwios' / '$ms'}')
echo -e "平均I/O队列长度(扇区)：\t\t     $avgqu"

#svctm:平均每次设备I/O操作的服务时间 (毫秒)，即 use/(rio+wio)
svctm=$(awk 'BEGIN{printf"%.2f\n",'$use' / '$rwio'}')
echo -e "平均每次设备I/O操作的服务时间：\t\t     $svctm ms"

#计算IOPS(IO per Second)，IO系统每秒所执行IO操作的次数，是一个重要的用来衡量系统IO能力的一个参数
iops=$(awk 'BEGIN{printf"%.2f\n",'$rios' + '$wios'}')
echo -e "IO系统每秒所执行IO操作的次数：\t\t     $iops"
#计算IO吞吐率(Throughtput) 
tp=$(awk 'BEGIN{printf"%.2f\n",'$rkbs' + '$wkbs'}')
echo -e "IO吞吐率（Throughtput）：\t\t     $tp kB/s"


#echo -e "读请求总数(从系统启动时的累积值)：\t     $rio"
#echo -e "写请求总数(从系统启动时的累积值)：\t     $wio"
#echo -e "合并的读请求总数(从系统启动时的累积值)：\t     $rmerge"
#echo -e "合并的写请求总数(从系统启动时的累积值)：\t     $wmerge"
#echo -e "读扇区总数(从系统启动时的累积值)：\t     $rsect"
#echo -e "写扇区总数(从系统启动时的累积值)：\t     $wsect"

echo -e "正在进行的I/O数，I/O队列中请求数：\t     $running"
echo -e "系统在I/O上花费的时间加权毫秒数:\t\t    $aveq ms"
echo -e "系统真正花费在I/O上的时间，除去重复等待时间：$use ms"

