#! /bin/bash
##计算CPU的运算速度（浮点运算） （单位：浮点运算/秒）
num=5000
export TIMEFORMAT=$'real:%3R\nuser:%3U\nsys:%3S' #指定time命令的输出格式
(time echo "scale=$num; 4*a(1)" | bc -l -q | grep "real") >&tmp #获取CPU计算圆周率到小数点后5000位所用的时间，并将结果写入到tmp文件
real=`cat tmp | awk -F ':' 'NR==1{print $2}'` #获取CPU实际运算的时间
#echo $real
cpu_cal_speed=$(awk 'BEGIN{printf"%.3f\n",'$num' / '$real'}')
echo "CPU的运算速度:"$cpu_cal_speed"Flops(浮点运算/秒)" 

rm -rf tmp
