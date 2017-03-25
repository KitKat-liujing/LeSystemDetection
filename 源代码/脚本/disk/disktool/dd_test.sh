#!/bin/bash
#dd命令测试磁盘读写速度
echo $1 |sudo -S echo -n 2> /dev/null
if [ $? == 0 ];then
	#测磁盘写速度
	echo "磁盘写速度测试结果：">info
	sudo dd if=/dev/zero of=test.bin bs=4096 count=1M conv=fdatasync 2>> info
	#测磁盘读速度
	echo "磁盘读速度测试结果：">>info
	sudo dd if=test.bin of=/dev/zero bs=4096 count=1M iflag=direct 2>> info
	rm -rf test.bin
	cat info
	rm -rf info
else
	echo "密码输入错误！"
fi
