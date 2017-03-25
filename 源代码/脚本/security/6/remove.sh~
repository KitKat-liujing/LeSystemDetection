#!/bin/bash
#******************************#
#Author:xuelimin
#Function:删除md5产生的文件
#******************************#
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
PWD=$(pwd)
dir=$(ls -l $PWD|grep usr.bin.* |awk '{print $NF}')
#echo $dir
cd $PWD
if [ -f $dir ];then
	rm -rf $dir
	if [ $? == 0 ];then
	echo "$dir 删除成功！"
	fi
fi
fi
