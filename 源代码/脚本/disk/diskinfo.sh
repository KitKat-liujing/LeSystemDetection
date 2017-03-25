#########################################################################
# File Name: diskinfo.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月06日 星期二 11时53分42秒
#########################################################################
#!/bin/bash
#获取磁盘缓存大小
echo -e "磁盘缓存大小：\t\t\t`cat /proc/meminfo |grep "Buffers:" |awk '{print $2" "$3}'`"
echo ""
######################计算磁盘占用率#############################
usesum=0
totalsum=0
disknum=`df -hlT |wc -l `
#计算本系统(linux)下的磁盘总量和已使用量
for((n=2;n<=$disknum;n++))
do
	use=$(df -k |awk NR==$n'{print int($3)}')
	pertotal=$(df -k |awk NR==$n'{print int($2)}')
	usesum=$[$usesum+$use]	#计算已使用的总量
	totalsum=$[$totalsum+$pertotal]	#计算本系统总量
done
freesum=$[$totalsum-$usesum]
diskutil=$(awk 'BEGIN{printf"%.2f\n",'$usesum' / '$totalsum'*100}')
freeutil=$(awk 'BEGIN{printf"%.2f\n",100 - '$diskutil'}')
echo -e "本系统磁盘占用率：\t\t\t$diskutil%"

echo -e "本系统磁盘空闲率：\t\t\t$freeutil%"
echo ""

if [ $totalsum -ge 0 -a $totalsum -lt 1024 ];then
echo -e "本系统磁盘总量：\t\t\t$totalsum K"

elif [ $totalsum -gt 1024 -a  $totalsum -lt 1048576 ];then
	totalsum=$(awk 'BEGIN{printf"%.2f\n",'$totalsum' / 1024}')
echo -e "本系统磁盘总量：\t\t\t$totalsum M"

elif [ $totalsum -gt 1048576 ];then
	totalsum=$(awk 'BEGIN{printf"%.2f\n",'$totalsum' / 1048576}')
echo -e "本系统磁盘总量：\t\t\t$totalsum G"

fi

if [ $usesum -ge 0 -a $usesum -lt 1024 ];then
echo -e "本系统磁盘已使用总量：\t\t$usesum K"

elif [ $usesum -gt 1024 -a  $usesum -lt 1048576 ];then
	usesum=$(awk 'BEGIN{printf"%.2f\n",'$usesum' / 1024}')
echo -e "本系统磁盘已使用总量：\t\t$usesum M"

elif [ $usesum -gt 1048576 ];then
	usesum=$(awk 'BEGIN{printf"%.2f\n",'$usesum' / 1048576}')
echo -e "本系统磁盘已使用总量：\t\t$usesum G"

fi


if [ $freesum -ge 0 -a $freesum -lt 1024 ];then
echo -e "本系统磁盘未使用总量：\t\t$freesum K"

elif [ $freesum -gt 1024 -a  $freesum -lt 1048576 ];then
	freesum=$(awk 'BEGIN{printf"%.2f\n",'$freesum' / 1024}')
echo -e "本系统磁盘未使用总量：\t\t$freesum M"

elif [ $freesum -gt 1048576 ];then
	freesum=$(awk 'BEGIN{printf"%.2f\n",'$freesum' / 1048576}')
echo -e "本系统磁盘未使用总量：\t\t$freesum G"
fi

echo ""

######################################################################
#echo "每个磁盘分区的Inode总数和使用情况如下："
#df -i 
#echo ""
#echo "磁盘分区具体信息如下：" 
#df -hlT 

echo "扫描系统磁盘垃圾情况如下："
#查看回收站垃圾大小
a1=`du -ks $HOME/.local/share/Trash/files/ | awk '{print int($1)}'`
echo -e "回收站垃圾大小：\t\t\t`du -hs $HOME/.local/share/Trash/files/ | awk '{print $1}'`"

#查看无用软件包垃圾大小，/var/cache/apt/archives是安装软件时下载包的临时存放目录
a2=`du -ks /var/cache/apt/archives | awk '{print int($1)}'`
echo -e "无用的软件包垃圾：\t\t\t`du -hs /var/cache/apt/archives | awk '{print $1}'`"


#查看是缩略图缓存垃圾大小
a3=`du -ks ~/.cache/thumbnails/ |awk '{print int($1)}'`
echo -e "缩略图缓存垃圾：\t\t\t`du -hs ~/.cache/thumbnails/ |awk '{print $1}'`"


sum=$[$a1+$a2+$a3]

if [ $sum -ge 0 -a $sum -lt 1024 ];then
	echo -e "磁盘垃圾总计：\t\t\t$sum K"
elif [ $sum -ge 1024 -a $sum -lt 1048576 ];then
	msum=`echo "scale=2;$sum/1024"|bc`
	echo -e "磁盘垃圾总计：\t\t\t$msum M"
elif [ $sum -ge 1048576 ];then
	gsum=`echo "scale=2;$sum/1048576"|bc`
	echo -e "磁盘垃圾总计：\t\t\t$gsum G (已超过1G，最好及时清理)"
fi
echo ""
#查看是否有旧内核
a6=`ls /boot |grep "vmlinuz" |wc -l`
if [ $a6 -gt 1 ];then
	echo "系统有旧内核，可删除释放一些磁盘空间！"
fi

echo ""
########################################################################
#检查普通磁盘是否正常可用
	device_name=(`df -lh |grep  "^/dev/sd"|awk '{print $1}'`)
	mount_dir=(`df -lh |grep  "^/dev/sd"|awk '{print $6}'`)
	num=${#device_name[@]}

	for ((i=1;i<=$num-1;i++));
	do
		touch ${mount_dir[$i]}/file1 2> /dev/null
		if [ $? -eq 0 ]
		then
			echo -e "检测到普通磁盘${device_name[$i]}是正常可用的"
		else
			echo -e "检测到普通磁盘${device_name[$i]}是不可用的"
		fi
		rm -rf ${mount_dir[$i]}/file1
	done

