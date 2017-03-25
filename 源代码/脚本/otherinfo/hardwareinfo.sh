#!/bin/bash
#硬件信息

##显卡信息
#集成显卡
echo -e "集成显卡型号：" #sed删除括号里的内容（可优化）
echo -e "`lspci | grep -i 'VGA' | sed '2d' | cut -f3 -d ":" | sed 's/([^>]*)//g'`"

echo -e "集成显卡生产商：" #（可优化）
echo -e "`lspci | grep -i 'VGA'| sed '2d'| awk '{ print $5,$6 }'`"

#lspci | grep -i 'VGA' | sed '2d' |awk '{for(i=5;i<=11;i++)printf $i""FS;print""}'
echo ""
count_dis=`lspci | grep -i 'VGA' | wc -l`

if [ $count_dis -eq 2 ]
then
	#独立显卡
    echo -e "独立显卡型号：" 
	echo -e "`lspci | grep -i 'VGA' | sed '1d' | cut -f3 -d ":" | sed 's/([^>]*)//g'`" #（可优化）

	echo -e "独立显卡生产商：" 
	echo -e "`lspci | grep -i 'VGA'| sed '1d'| awk '{ print $5,$6 }'`" #（可优化）	

else
	echo -e "独立显卡信息："
	echo -e "无"
fi
echo ""
##声卡
count_sound=`lspci | grep Audio | wc -l`

if [ $count_sound -eq 1 ]
then
	echo -e "声卡型号：" 
	echo -e "`lspci |grep Audio | cut -f3 -d ":" | sed 's/([^>]*)//g'`" 

	echo -e "声卡生产商："
	echo -e "`lspci | grep Audio | awk '{ print $4,$5 }'`"
	
	echo ""
else #有的电脑有超过2个声卡
	for((i=1;i<=$count_sound;i++));do
		
		echo -e "声卡$i型号：";
		echo -e "`lspci |grep Audio | awk 'NR=='$i'' | cut -f3 -d ":" | sed 's/([^>]*)//g'`";
	
		echo -e "声卡$i生产商：";
		echo -e "`lspci | grep Audio | awk 'NR=='$i' { print $4,$5 }'`";

		
		echo ""
	done
fi


