#/bin/bash

#echo "当前登入的用户：`whoami` "

#此函数计算系统开机所用时间单位是秒数
function run_time (){
  #计算出dmesg中系统启动记录的时间相对文件开头的时间
  a=`cat /var/log/dmesg | grep "setting system" | awk '{print $2}'`
  run=${a%?}
  run=${run:0:1}
  #获取dmesg中系统启动时记录的时间
  start_hour=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' | awk   -F: '{print int($1)}'`*3600]
  start_min=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($2)}'`*60]
  start_sec=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($3)}'`]
  #做减法获取真正系统启动的时间
  start_time=$[$start_hour+$start_min+$start_sec-$run]
  #获取图形登入界面启动的时间，这里有两个要去掉父进程为1的进程，取最近时间的进程
  end_time=0
  for pid in $(pgrep lightdm); 
  do 
  t2=`ps -p ${pid} -o lstart=`
  end_hour=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($1)}'`*3600]
  end_min=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($2)}'`*60]
  end_sec=$[`echo $t2 | awk '{print $4}' | awk -F: '{print int($3)}'`]
  t1=$[$end_hour+$end_min+$end_sec]
  if [ $t1 -gt $end_time ]
  then
    end_time=$t1
  fi
  done
  #获取系统启动的时长
  cur_runtime=$[$end_time-$start_time]
  #为了判断cmos有问题，还是格林尼治时间的处理，要把结果减去28800
  if [ $cur_runtime -ge 28800 ]
  then 
     cur_runtime=$[$cur_runtime - 28800]     
  fi     
  #返回系统启动时长
  echo $cur_runtime
}

#此函数将开机所用的的秒数格式化转换成时分秒
function date_time()
{
  min=0
  hour=0
  #一般情况下针对个人PC开机时长是不会超过一个小时的
  min=$[$[ $1 / 60 ] %60]
  second=$[$1 % 60]
  if [ $1 -gt 60 ]
  then
    echo "本次开机用时$min分$second秒"
  else
    echo "本次开机用时$second秒" 
  fi
}
  timelength=$(run_time)
  date_time $timelength

echo "本次开机时刻：`date -d "$(awk -F. '{print $1}' /proc/uptime) second ago" +"%Y-%m-%d %H:%M:%S"`"

 
 







