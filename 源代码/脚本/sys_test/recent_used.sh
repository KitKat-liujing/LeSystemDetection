#检测有没有最近使用文档跟踪记录 
flag=0
sec0=`ls -l ~/.local/share/ |grep "recently-used.xbel" |wc -l `
if [ $sec0 -eq 1 ];then
	sec1=`ls -l ~/.local/share/recently-used.xbel |awk '{print $5}'`
	if [ $sec1 -eq 0 ];then
		echo $flag
	else
		((flag++))
		echo $flag
	fi
else
	echo $flag
fi
