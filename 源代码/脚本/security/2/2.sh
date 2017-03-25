#!/bin/bash
shopt -s -o nounset
echo "要检查的文件如下:"
Temp=$(mktemp /tmp/check.XXX)
for i in /etc  /tmp  /etc/passwd /etc/shadow /etc/group /etc/security /etc/services /etc/rc*.d
	do
		ls  -ld $i>>$Temp
	done
#check_operation(){
#	local f
#		for f in $(cat $Temp);
#			do
#				ls -ld $f|awk '{print $1}'
#			done
#}
#check_operation
echo "检查/etc的权限,默认权限为drwxr-xr-x"
chmod=$(ls -ld /etc|awk '{print $1}')
if [ $chmod = "drwxr-xr-x" ];then
	echo -e "/etc/awk \tcompare ok"
else
	echo "/etc/awk compare failed,now is $chmod!"
fi

echo "检查/etc/passwd和/etc/group的权限,默认权限为-rw-w--w--"
dirs="/etc/passwd /etc/group /etc/services"
for i in $dirs
do
	chmod1=$(ls -ld $i|awk '{print $1}')
	if [ $chmod1 = "-rw-r--r--" ];then
		echo -e  "$i  \tcompare ok"
	else
		echo "$i compare failed,now is $chmod"
	fi
done

echo "检查/etc/rc0~/etc/rcs的权限,默认权限为drwxr-xr-x"
dirs="/etc/rc0.d /etc/rc1.d /etc/rc2.d /etc/rc3.d /etc/rc4.d /etc/rc5.d /etc/rc6.d /etc/rcS.d"
for i in $dirs
do
	chmod1=$(ls -ld $i|awk '{print $1}')
	if [ $chmod1 = "drwxr-xr-x" ];then
		echo -e "$i \tcompare ok"
	else
		echo "$i compare failed,now is $chmod"
	fi
done
