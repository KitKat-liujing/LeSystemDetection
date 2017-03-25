#########################################################################
# File Name: lj.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月06日 星期二 19时40分04秒
#########################################################################
#!/bin/bash
errnum=0
util=100
#检查普通分区（不包括根分区）是否正常可用
device_name=(`df -lh |grep  "^/dev/sd"|awk '{print $1}'`)
mount_dir=(`df -lh |grep  "^/dev/sd"|awk '{print $6}'`)
num=${#device_name[@]}

for ((i=1;i<=$num-1;i++))
do
touch ${mount_dir[$i]}/file1
        if [ $? -ne 0 ];then
	((errnum++))
        fi
rm -rf ${mount_dir[$i]}/file1
done
#计算不能正常使用的普通盘占检查普通盘总数的百分比
errutil0=`awk 'BEGIN{printf"%.2f\n",'$errnum' / '$num' }'`
errutil1=`awk 'BEGIN{printf"%.0f\n",'$errutil0' * '$util' }'`
echo $errutil1
