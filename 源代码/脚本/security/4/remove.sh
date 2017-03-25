#!/bin/bash
#******************************#
#Author:xuelimin
#Function:删除md5产生的文件
#******************************#
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
cd /usr/share/systemtest/application/systemtest/
`ls -l`
dir=$(ls -l |grep "bin.*")
echo $dir
if [ -f $dir ];then
	rm -rf $dir
	if [ $? == 0 ];then
	echo "$dir 删除成功！"
	fi
fi
fi
