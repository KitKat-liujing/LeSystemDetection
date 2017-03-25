#!/bin/bash
#获取启动时长
function run_time (){

  a=`cat /var/log/dmesg | grep "setting system" | awk '{print $2}'`
  run=${a%?}
  run=${run:0:1}
  start_hour=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' | awk   -F: '{print int($1)}'`*3600]
  start_min=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($2)}'`*60]
  start_sec=$[`cat /var/log/dmesg | grep "setting system" | awk '{print $10}' |  awk -F: '{print int($3)}'`]
  start_time=$[$start_hour+$start_min+$start_sec-$run]

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
  cur_runtime=$[$end_time-$start_time]
  return $cur_runtime
}

run_time
timelength=$?
echo $timelength
