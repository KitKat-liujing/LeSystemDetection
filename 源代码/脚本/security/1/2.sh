#每个进程都会有一个PID，而每一个PID都会在/proc目录下有一个相应的目录，一般后门程序，在ps等进程查看工具里找不到，因为这些常用工具甚至系统库在系统被入侵之后基本上已经被动过手脚（网上流传着大量的rootkit，假如是内核级的木马，那么该方法就无效了）。因为修改系统内核相对复杂（假如内核被修改过，或者是内核级的木马，就更难发现了），所以在/proc下，基本上还都可以找到木马的痕迹
woodenflag=0
str_pids="`ps -A | awk '{print $1}'`"
for i in /proc/[[:digit:]]*; do
if echo "$str_pids" | grep -qs `basename "$i"`; then
  :
else
	((woodenflag++))
  echo "Rootkit's PID: $(basename "$i")"
fi
done
if [ $woodenflag == 0 ];then
echo "ps下的进程号与pro文件相符合"
echo "未发现有用户态的木马后门程序"
else
echo "共发现 $woodenflag 个后门程序"
fi
