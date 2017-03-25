#!/bin/bash
#系统信息

echo -e "当前操作系统位数：\t\t`getconf LONG_BIT `位"
echo -e "操作系统内核：\t\t`cat /proc/version | awk '{OFS="  ";print $1, $2, $3}'`"
echo -e "查看操作系统版本：\t\t`head -n 1 /etc/issue | awk '{print $1,$2}'`"

usernum=`cut -d: -f1 /etc/passwd |wc -l`
echo -e "系统用户总数：\t\t$usernum"

#登陆用户数
login_user=`who | wc -l`
echo -e "登陆的用户数：\t\t$login_user"  

groupnum=`cut -d: -f1 /etc/group |wc -l`
echo -e "系统组总数：\t\t$groupnum"

modnum=`lsmod |wc -l`
echo -e "已加载的内核模块总数：\t$modnum"

#软件总信息
softnum=`dpkg -l | awk '{if(NR!=1&&NR!=2&&NR!=3&&NR!=4&&NR!=5) {print $2}}' |wc -l `
echo -e "本机已安装软件总数：\t\t$softnum"
echo -e #空行
#apt-cache stats

#获取加密算法的个数和名字
num=`cat /proc/crypto |grep "name" | sort | uniq | awk '{print $3}' | wc -l`
namesum=`cat /proc/crypto |grep "name" | sort | uniq | awk '{print $3}'`
echo "当前系统有"$num"种加密算法，分别为:"
i=0
for name in $namesum;
do
	((i++)); 
	if [ $[$i % 6] -eq 0 ] 
	then

		echo -n $name" 、";		
		echo -e;
	else 
		if [ $i -eq $num ]
		then
			echo $name" 。 ";
		else
			echo -n $name" 、";
		fi
	fi	
done
