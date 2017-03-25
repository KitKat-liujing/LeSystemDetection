#最近三次登陆时间
echo "最近三次登陆时间如下："
echo "用户名"   "  ""登入时间" 
last -n 3 | awk '{print $1"  	 "$4" "$5" "$6" "$7" "$8$9}' |head -3

#检查passwd文件中有哪些特权用户
echo "passwd文件中的特权用户有："
awk -F: '$3==0 {print $1}' /etc/passwd  

