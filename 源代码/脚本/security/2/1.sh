#!/bin/bash
shopt -s -o nounset
echo "要检查的文件如下:"
Temp=$(mktemp /tmp/check.XXX)
for i in /etc  /tmp  /etc/passwd /etc/shadow /etc/group /etc/security /etc/services /etc/rc*.d
	do
		ls  -ld $i>>$Temp
		echo "$i"
	done
