#########################################################################
# File Name: hardwareinfomore.sh
# Author: liujing
# mail: 2510034575@qq.com
# Created Time: 2015年01月21日 星期三 21时28分33秒
#########################################################################
#!/bin/bash
echo $1 | sudo -S echo -n 2> /dev/null
if [ $? == 0 ]
then 
	##主板信息
	sudo dmidecode > hardware_tmp
	echo "------------------------------主板信息------------------------------"
	echo -e "主板厂商：\t\t\t`cat hardware_tmp | grep -A 10 "Base Board Information" |grep "Manufacturer" | awk -F ':' '{print $2}'`"
	echo ""
	echo -e "产品名称：\t\t\t`cat hardware_tmp | grep -A 10 "Base Board Information" |grep "Product Name" | awk -F ':' '{print $2}'`"
	echo ""
	echo -e "版本：\t\t\t`cat hardware_tmp | grep -A 10 "Base Board Information" | grep 'Version' | awk -F ':' '{print $2}'`"
	echo ""
	echo -e "序列号：\t\t\t`cat hardware_tmp | grep -A 10 "Base Board Information" | grep 'Serial' | awk -F ':' '{print $2}'`"
	echo ""
	echo ""
	##BIOS信息
	echo "------------------------------BIOS信息------------------------------"
	echo -e "BIOS厂商：\t\t\t`cat hardware_tmp | grep -A 28 "BIOS Information" | grep 'Vendor' | awk -F ':' '{print $2}'`"
	echo ""
	echo -e "BIOS版本：\t\t\t`cat hardware_tmp | grep -A 28 "BIOS Information" | grep 'Version' | awk -F ':' '{print $2}'`"
	echo ""
	echo -e "发行日期：\t\t\t`cat hardware_tmp | grep -A 28 "BIOS Information" | grep 'Release' | awk -F ':' '{print $2}'`"
	
	rm -rf hardware_tmp

fi
