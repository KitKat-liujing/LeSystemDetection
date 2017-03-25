echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	#hdparm命令测磁盘信息
	#sudo hdparm -I /dev/sda > hdparm_test
	v_judge=`sudo hdparm -I /dev/sda |wc -l` 2> /dev/null
	if [ $v_judge -gt 50 ];then
	echo -e "磁盘产品：\t\t\t\t`sudo hdparm -I /dev/sda |grep "Model Number:" |awk '{print $3}'`" 
	echo -e "磁盘序列号：\t\t\t`sudo hdparm -I /dev/sda |grep "Serial Number:" |awk '{print $3}'`" 	
	fi	
	#rm -rf hdparm_test

	sudo fdisk -l > fdiskinfo 
	dident=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "Disk identifier"|awk '{print $3}'`
	echo -e "磁盘标识符：\t\t\t$dident"	

	a=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "Disk /dev/sda" |awk '{print $3 $4}'`
	b=${a%?}
	echo -e "磁盘物理总量：\t\t\t$b" 
	echo ""
	hdnum=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "heads" |awk '{print $1}'`
	echo -e "硬盘磁头数：\t\t\t$hdnum"

	secnum=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "sectors/track" |awk '{print $1}'`
	echo -e "硬盘扇区/磁道数：\t\t\t$secnum"
	sectotal=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "sectors/track" |awk '{print $8}'`
	echo -e "硬盘总扇区数：\t\t\t$sectotal"
	echo ""
	secsize1=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "Sector size"|awk '{print $4}'`
	secsize2=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "Sector size"|awk '{print $7}'`
	echo -e "逻辑扇区大小：\t\t\t$secsize1 字节"
	echo -e "物理扇区大小：\t\t\t$secsize2 字节"
	echo ""
	iosize1=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "I/O size"|awk '{print $4}'`
	iosize2=`cat fdiskinfo |grep -A6 "Disk /dev/sda"|grep "I/O size"|awk '{print $7}'`
	echo -e "最小I/O大小：\t\t\t$iosize1 字节"
	echo -e "最佳I/O大小：\t\t\t$iosize2 字节"
	
	rm -rf fdiskinfo
	echo ""
	#num0=`cat /proc/partitions |grep "sda" |wc -l `
	#num=$[$num0-1]
	#sudo fdisk -l |grep -A$num "Id"	
	#echo ""

#查看系统日志文件
	logsize=`sudo du -ks /var/log |awk '{print int($1)}'`
	echo -e "系统日志文件大小：\t\t\t`sudo du -hs /var/log |awk '{print $1}'`"
	if [ $logsize -ge 1048576 ];then
		echo "系统日志文件总量超过1G，可清除一些垃圾日志，释放磁盘空间！"


	fi
	#查看系统/tmp临时文件垃圾大小
	tmpsize=`sudo du -ks /tmp |awk '{print int($1)}'`
	echo -e "/tmp临时垃圾文件大小：\t\t`du -hs ~/.cache/thumbnails/ |awk '{print $1}'`"
	if [ $tmpsize -ge 1048576 ];then
		echo "系统/tmp临时垃圾文件总量超过1G，可清除，释放磁盘空间！"
	fi
###################################################
echo ""
	#检查系统根分区磁盘是否正常可用
	device_name=(`df -lh |grep  "^/dev/sd"|awk '{print $1}'`)
	mount_dir=(`df -lh |grep  "^/dev/sd"|awk '{print $6}'`)
	num=${#device_name[@]}

		sudo touch ${mount_dir[0]}/file1 2> /dev/null
		if [ $? -eq 0 ]
		then
			echo -e "系统根分区磁盘${device_name[0]}是正常可用的"
		else
			echo -e "系统根分区磁盘${device_name[0]}是不可用的"
		fi
		sudo rm -rf ${mount_dir[0]}/file1
	
fi





