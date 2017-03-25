#/proc/uptime第一列输出的是，系统启动到现在的时间（以秒为单位）
ut=`cat /proc/uptime |awk '{print $1}'`

#有线网流量信息
num1=`cat /proc/net/dev |grep "eth" |wc -l`
if [ $num1 -gt 0 ];then
for((i=0;i<$num1;i++))
do 
	echo  "当前 eth$i 接口流量信息(自系统启动到当前)"
#bytes 接收的总字节数
rbytes=`cat /proc/net/dev |grep "eth$i"|awk '{print $2}'`
echo -e "接收的总字节数：\t\t$rbytes"
rbavg=`awk 'BEGIN{printf"%.2f\n",'$rbytes' / '$ut'}'`
echo -e "平均每秒接收的字节数：\t$rbavg"

#packets 接收的报文总数
 rpackets=`cat /proc/net/dev |grep "eth$i"|awk '{print $3}'`
echo -e "接收的报文总数：\t\t$rpackets"
rpavg=`awk 'BEGIN{printf"%.2f\n",'$rpackets' / '$ut'}'`
echo -e "平均每秒接收的数据包：\t$rpavg"

#compressed 接收的压缩报数
 rcompressed=`cat /proc/net/dev |grep "eth$i"|awk '{print $8}'`
 echo -e "接收的压缩报数：\t\t$rcompressed"
rcavg=`awk 'BEGIN{printf"%.2f\n",'$rcompressed' / '$ut'}'`
echo -e "平均每秒接收的压缩报数：\t$rcavg"

#multicast 接收到的多播报数
rmulticast=`cat /proc/net/dev |grep "eth$i"|awk '{print $9}'`
echo -e "接收到的多播报数：\t\t$rmulticast"
rmavg=`awk 'BEGIN{printf"%.2f\n",'$rmulticast' / '$ut'}'`
echo -e "平均每秒接收的多播报数：\t$rmavg"

#frame接收时帧错误数
rframe=`cat /proc/net/dev |grep "eth$i"|awk '{print $7}'`
 echo -e "接收时帧错误数：\t\t$rframe"
rfavg=`awk 'BEGIN{printf"%.2f\n",'$rframe' / '$ut'}'`
#echo "平均每秒接收的错误帧数：$rfavg"

#errs 接收时被设备驱动监测到的错误报文总数
 rerrs=`cat /proc/net/dev |grep "eth$i"|awk '{print $4}'`
echo "接收时设备监测到的错误报文总数：$rerrs"
rravg=`awk 'BEGIN{printf"%.2f\n",'$rerrs' / '$ut'}'`
#echo "平均每秒接收的错误报文数：$rravg" 


#drop 由于系统资源限制，接收时被设备驱动丢弃的报文总数
 rdrop=`cat /proc/net/dev |grep "eth$i"|awk '{print $5}'`
echo -e "接收时被设备丢弃的报文总数:\t$rdrop"
rdavg=`awk 'BEGIN{printf"%.2f\n",'$rdrop' / '$ut'}'`
#echo "因系统资源限制，接收时平均每秒被设备驱动丢弃的报文数：$rdavg"

echo ""

#bytes 发送的总字节数
tbytes=`cat /proc/net/dev |grep "eth$i"|awk '{print $10}'`
echo -e "发送的总字节数：\t\t$tbytes"
tbavg=`awk 'BEGIN{printf"%.2f\n",'$tbytes' / '$ut'}'`
echo -e "平均每秒发送的字节数：\t$tbavg"

#packets 发送的报文总数
 tpackets=`cat /proc/net/dev |grep "eth$i"|awk '{print $11}'`
 echo -e "发送的报文数：\t\t$tpackets"
tpavg=`awk 'BEGIN{printf"%.2f\n",'$tpackets' / '$ut'}'`
echo -e "平均每秒发送的报文数：\t$tpavg"

#compressed 发送的压缩报数
 tcompressed=`cat /proc/net/dev |grep "eth$i"|awk '{print $17}'`
 echo -e "发送的压缩报数：\t\t$tcompressed"
tcomavg=`awk 'BEGIN{printf"%.2f\n",'$tcompressed' / '$ut'}'`
echo -e "平均每秒发送的压缩报数：\t$tcomavg"

#errs 发送时被设备驱动监测到的错误报文总数
 terrs=`cat /proc/net/dev |grep "eth$i"|awk '{print $12}'`
 echo -e "发送时设备检测到的错误报文数：\t$terrs"
teavg=`awk 'BEGIN{printf"%.2f\n",'$terrs' / '$ut'}'`
#echo "平均每秒发送的错误报文数：$teavg"

#drop 由于系统资源限制，发送时被设备驱动丢弃的报文总数
 tdrop=`cat /proc/net/dev |grep "eth$i"|awk '{print $13}'`
 echo -e "发送时被设备丢弃的报文总数：\t$tdrop"
tdavg=`awk 'BEGIN{printf"%.2f\n",'$tdrop' / '$ut'}'`
#echo "发送时平均每秒丢弃的报文数：$tdavg"

#colls 接口检测到的冲突数
 tcolls=`cat /proc/net/dev |grep "eth$i"|awk '{print $15}'`
echo -e "接口检测到的冲突数：\t\t$tcolls"
tcavg=`awk 'BEGIN{printf"%.2f\n",'$tcolls' / '$ut'}'`
#echo "平均每秒冲突数：$tcavg"

#carrier 连接介质出现故障次数, 如 : 网线接触不良
 tcarriers=`cat /proc/net/dev |grep "eth$i"|awk '{print $16}'`
 echo -e "连接介质出现故障次数：\t$tcarriers"
tcaravg=`awk 'BEGIN{printf"%.2f\n",'$tcarriers' / '$ut'}'`
#echo "平均每秒出现的连接故障数：$tcarbavg"
done

else 
	echo "未检测到有线网卡的信息，本机可能没有有线网卡或者有线网卡已坏"
fi

