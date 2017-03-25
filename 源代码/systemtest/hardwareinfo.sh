#########################################################################
# File Name: hardwareinfo.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月07日 星期三 19时23分25秒
#########################################################################
#!/bin/bash
echo "33333333333"
echo $1 |sudo -S echo "" 2> /dev/null
if [ $? == 0 ];then
echo  主板：lspci |grep Host | head -1 | awk '{for(i=4;i<=NF;i++) printf $i " "}'
echo  主板厂商：`echo $1 | sudo -S dmidecode | grep -A 10 "Base Board Information" |grep Manufacturer | awk '{print $2,$3,$4}'`
echo  版本：` echo $1 |sudo -S dmidecode | grep -A 10 "Base Board Information" | grep 'Version' | awk '{print $2 " " $3 " "  $4}'`
echo  序列号：`echo $1 | sudo -S dmidecode | grep -A 10 "Base Board Information" | grep 'Serial' | awk '{print $3}'`
echo  BIOS版本：`echo $1 | sudo -S dmidecode | grep -A 28 "BIOS Information" | grep 'Version' | awk '{print $2}'`
echo  BIOS日期：` echo $1 |sudo -S dmidecode | grep -A 28 "BIOS Information" | grep 'Release' | awk '{print $3}'`
echo 集显生产厂商：`lspci | grep -i 'VGA'| sed '2d'| awk '{ print $5,$6 } '`
echo 集显显卡型号：`lspci | grep -i 'VGA' | sed '2d' |awk '{for(i=5;i<=14;i++)printf $i""FS;print""}'`
echo 独显型号`lspci | grep -i 'VGA' | sed '1d' | awk '{for(i=5;i<=9;i++)printf $i""FS;print""}'`
echo  "显卡：`lspci | grep VGA | cut -f2 -d "." |cut -f2 -d "0"`"
echo "声卡：`lspci |grep Audio | cut -f3 -d ":"`"
echo 声卡版本号：   `alsactl -v | awk ' { print $3} '`
echo 声卡音频设备： `lspci  | grep -i audio | grep Intel | cut  -f3 -d ":"`
echo "网卡：`lspci | grep Ethernet | cut -f3 -d ":"`"

cat /proc/cpuinfo | grep name  | uniq | awk '$1="处理器",$2=null'
echo "`cat /proc/cpuinfo | grep MHz |  sort | uniq  |awk '$1="运行速度 ",$2=null'| grep 运行速度` MHz"

echo "USB：`lspci |grep USB | cut -f3 -d ":" | head -1`"
echo "usb生产厂商：` lsusb | sort -k4r |head -1 | awk '{ print $7.$8,$9 }'`"
echo "共有usb设备：` lsusb | sort -k2r | head -1 |awk '{ print $2 }'|cut -f3 -d "0"` 个"
else
	echo "密码输入错误！"
fi


