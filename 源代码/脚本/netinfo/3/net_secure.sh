#########################################################################
# File Name: netsecure.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月10日 星期六 20时44分35秒
#########################################################################
#!/bin/bash
	#查看是否开机自动绑定IP和MAC地址
	ap=`cat /etc/init.d/rc.local |grep "arp -f /etc/ip-mac" |wc -l`
	if [ $ap == 0 ];then
		echo "ARP欺骗防护未开机自启动"
		echo " "
	else
		echo "ARP欺骗防护已开机自启动"
		echo " "
	fi

	#正常网卡不该在promisc模式，当然安全server除外，否则可能是有人入侵在sniffer
	a=`ip link | grep PROMISC |wc -l`
	if [ $a -ne 0 ];then
		echo "系统可能有sniffer入侵的危险"
		echo " "
	else
		echo "系统没有sniffer入侵的危险"
		echo " "
	fi 

	#联网后查看IP地址和网关MAC是否已经静态绑定，如果静态绑定则可以防止ARP攻击
	#查看是否存在arp攻击
	a=`arp |grep :|wc -l`
	if [ $a == 0 ];then
		echo "当前主机没有ARP攻击的危险"
		echo " "
		#统计已经静态绑定的ip-mac数目
		ap1=`arp -a |grep "PERM" |wc -l`
		if [ $ap1 == 0 ];then
			echo "当前没有IP与网关MAC静态绑定（有被ARP攻击的风险）"
			echo " "
			#统计未静态绑定的ip数目
			sum=`arp |grep "C" |wc -l`
			#得到未静态绑定的ip地址
			echo "未静态绑定的IP数：$sum 个"
			echo " "
			for((i=1;i<=$sum;i++))
			do
				#找出未静态绑定的ip地址
				un0=`arp |grep "C" |awk NR==$i'{print $3}'`
				un1=`arp -a |grep "$un0" | awk -F"[()]" NR==1'{print $2}'`
				echo "未静态绑定IP$i： $un1"
				echo " "
			done
		elif [ $ap1 -gt 0 ];then
			#统计静态绑定的ip数目
			uap1=`arp -a|grep -v "PERM" |wc -l`
			if [ $uap1 == 0 ];then
				echo "当前所有IP和网关MAC都已经静态绑定(被ARP攻击的风险较小)"
				echo " "
			else

				#得到部分已经静态绑定的ip-mac对
				echo "静态绑定的IP数：$ap1个"
				echo " "
				for((m=1;m<=$ap1;m++))
				do
					#获得每一对ip-mac静态绑定的MAC地址
					ap2=`arp |grep "CM" |awk NR==$m'{print $3}'`
					#获得每一对ip-mac静态绑定的ip地址
					ap3=`arp -a |grep "$ap2" | awk -F"[()]" NR==1'{print $2}'`

					#ap2=`arp -a |grep "PERM" |awk -F"[()]" NR==$m'{print $2}'`
					#ap3=`arp -a |grep "PERM" |awk NR==$m'{print $4}'`
					echo "IP $ap3 和网关MAC $ap2 已经静态绑定(可防御ARP攻击)"
					echo " "
				done

				#得到未静态绑定的ip地址
				echo "未静态绑定的IP数：$uap1 个"
				echo " "
				for((n=1;n<=$uap1;n++))
				do
					#找出未静态绑定的ip地址
					uap2=`arp -a |grep -v "PERM" |awk -F"[()]" NR==$n'{print $2}'`
					echo "IP $uap2 未静态绑定网关MAC(存在ARP攻击的风险)"
					echo " "
				done

			fi
		fi
	else
		echo "当前主机有ARP攻击的危险"
		echo " "
	fi
	################################################
	#用户隐私安全，检测是否有泄露个人隐私的危险

	#检测有没有最近使用文档跟踪记录 
	sec0=`ls -l ~/.local/share/ |grep "recently-used.xbel" |wc -l `
	if [ $sec0 -eq 1 ];then
		sec1=`ls -l ~/.local/share/recently-used.xbel |awk '{print $5}'`
		if [ $sec1 -eq 0 ];then
			echo "检测到不存在最近使用文档跟踪记录"
			echo " "
		else
			echo "检测到存在最近使用文档跟踪记录，个人隐私有泄露危险"
			echo " "
		fi
	else
		echo "检测到不存在最近使用文档跟踪记录"
		echo " "
	fi

	#检查有没有浏览器跟踪cookies和隐私记录
	a=`dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}' |grep "firefox" |wc -l`
	if [ $a -gt 0 ];then
		#echo "firefox已安装"

		fnum=`find ~/.mozilla/firefox -type d -name "*.default" |wc -l`

		if [ $fnum -ne 0 ];then
			path=`find ~/.mozilla/firefox -type d -name "*.default"`
			cd $path

			#检测有没有firefox跟踪cookies
			fc0=`ls -l |grep "cookies.sqlite" |wc -l`
			if [ $fc0 -eq 1 ];then
				fc1=`ls -l cookies.sqlite |awk '{print $5}'`
				if [ $fc1 -gt 0 ];then
					echo "检测到存在firefox跟踪cookies，个人隐私有泄露危险"
					echo " "
				else
					echo "检测到不存在firefox跟踪cookies"
					echo " "
				fi
			else
				echo "检测到不存在firefox跟踪cookies"
				echo " "
			fi

			#检查firefox有没有会话跟踪记录
			num=0

			#寻找非0字节的sessionstore.js文件
			sjnum=`ls -l |grep "sessionstore.js"|wc -l`
			if [ $sjnum -eq 1 ];then  
				sjsize=`ls -l |grep "sessionstore.js"|awk '{print $5}'`
				if [ $sjsize -gt 0 ];then
					((num++))
					#echo "sessionstore.js num: $num"
				fi
			fi

			#寻找非0字节的sessionstore.bak文件
			sbnum=`ls -l |grep "sessionstore.bak"|wc -l`
			if [ $sbnum -eq 1 ];then  
				sbsize=`ls -l |grep "sessionstore.bak"|awk '{print $5}'`
				if [ $sbsize -gt 0 ];then
					((num++))
					#echo "sessionstore.bak num: $num"
				fi
			fi

			#寻找非0字节的previous.js文件
			sbnum=` ls |grep "sessionstore-backups" |wc -l`
			if [ $sbnum -eq 1 ];then
				pjnum=`ls -l sessionstore-backups/ |grep "previous.js" |wc -l`
				if [ $pjnum -eq 1 ];then  
					pjsize=`ls -l sessionstore-backups/previous.js|awk '{print $5}'`
					if [ $pjsize -gt 0 ];then
						((num++))
						#echo "previous.js num: $num"
					fi
				fi


				#寻找非0字节的previous.bak文件
				pbnum=`ls -l sessionstore-backups/ |grep "previous.bak" |wc -l`
				if [ $pbnum -eq 1 ];then  
					pbsize=`ls -l sessionstore-backups/previous.js|awk '{print $5}'`
					if [ $pbsize -gt 0 ];then
						((num++))
						#echo "previous.bak num: $num"
					fi
				fi
				#寻找非0字节的recovery.js文件
				rjnum=`ls -l sessionstore-backups/ |grep "recovery.js" |wc -l`
				if [ $rjnum -eq 1 ];then  
					rjsize=`ls -l sessionstore-backups/previous.js|awk '{print $5}'`
					if [ $rjsize -gt 0 ];then
						((num++))
						#echo "recovery.js num: $num"
					fi
				fi

				#寻找非0字节的recovery.bak文件
				rbnum=`ls -l sessionstore-backups/ |grep "recovery.bak" |wc -l`
				if [ $rbnum -eq 1 ];then  
					rbsize=`ls -l sessionstore-backups/previous.js|awk '{print $5}'`
					if [ $rbsize -gt 0 ];then
						((num++))
						#echo "recovery.bak num: $num"
					fi
				fi
			fi
		fi
		#echo $num
		if [ $num == 0 ];then
			echo "检测到不存在firefox会话跟踪记录"
			echo " "
		else
			echo "检测到存在firefox会话跟踪记录，个人隐私有泄露危险"
			echo " "
		fi

	fi


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
			if [ -f "Cookies" ];then 
				#获取谷歌跟踪Cookies的大小
				gc0=`ls -l Cookies |awk '{print $5}'`
				#如果cookies大小为0,则不存在
				if [ $gc0 -gt 0 ];then
					echo "检测到存在google-chrome跟踪cookies，个人隐私有泄露危险"
					echo " " 
				else
					echo "检测到不存在google-chrome跟踪cookies"
					echo " " 
				fi
			else
				echo "检测到不存在google-chrome跟踪cookies"
				echo " " 
			fi

		else 
			echo "未检测到有google-chrome跟踪cookies" 
			echo " " 
		fi

		#检测有没有google-chrome跟踪URL历史记录
		if [ $g -gt 0 ];then
			#进入google-chrome跟踪cookies所在目录
			cd ~/.config/google-chrome/Default/
			#检测有没有google-chrome跟踪cookies
			if [ -f "History" ];then 
				#获取谷歌跟踪Cookies的大小
				gc0=`ls -l History |awk '{print $5}'`
				#如果cookies大小为0,则不存在
				if [ $gc0 -gt 0 ];then
					echo "检测到存在google-chrome历史跟踪记录，个人隐私有泄露危险"
					echo " " 
				else
					echo "检测到不存在google-chrome历史跟踪记录"
					echo " " 
				fi
			else
				echo "检测到不存在google-chrome历史跟踪记录"
				echo " " 
			fi

		else 
			echo "未检测到有google-chrome历史跟踪记录" 
			echo " " 
		fi
	fi

