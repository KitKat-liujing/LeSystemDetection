#!/bin/bash
#检测有没有google-chrome跟踪URL历史记录

flag=0
#判断有没有安装google-chrome
b=`dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}' |grep "google-chrome" |wc -l`
if [ $b -gt 0 ];then
	#echo "google-chrome已安装"
	#判断有没有google-chrome配置文件
	g=` ls -l ~/.config |grep "google-chrome" |wc -l `

	if [ $g -gt 0 ];then
		#进入google-chrome跟踪cookies所在目录
		cd ~/.config/google-chrome/Default/
		#检测有没有google-chrome跟踪cookies
		if [ -f "History" ];then 
			#获取谷歌跟踪Cookies的大小
			gc0=`ls -l History |awk '{print $5}'`
			#如果cookies大小为0,则不存在
			if [ $gc0 -gt 0 ];then
				((flag++))
				echo $flag #"检测到存在google-chrome历史跟踪记录，个人隐私有泄露危险"
			else
				echo $flag #"检测到不存在google-chrome历史跟踪记录"
			fi
		else
			echo $flag #"检测到不存在google-chrome历史跟踪记录"
		fi

	else 
		echo $flag #"未检测到有google-chrome历史跟踪记录" 
	fi
fi
