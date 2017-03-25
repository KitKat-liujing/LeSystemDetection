#include <stdio.h>
#include <string.h>
/*此程序对每个检测项进行打分*/
/*所有评分函数的返回值为int*/

/***********************************CPU性能********************************************/
/*CPU用户占用率评分函数*/
int get_cpu_user(float percent)
{
	if(percent >= 80)
	{
		return 5;
	}
	else if(percent > 70 && percent < 80)
	{
		return 4;
	}
	else if(percent > 65 && percent <= 70)
	{
		return 0;
	}
	else if(percent >= 50 && percent <= 65)
	{
		return 1;
	}
	else if(percent >= 20 && percent < 50)
	{
		return 2;
	}
	else
	{
		return 3;
	}
	
	return 0;
}

/*CPU系统占用率评分函数*/
int get_cpu_sys(float percent)
{
	if(percent > 70)
	{
		return 5;
	}
	else if(percent > 60 && percent <= 70)
	{
		return 4;
	}
	else if(percent > 50 && percent <= 60)
	{
		return 3;
	}
	else if(percent > 40 && percent <= 50)
	{
		return 2;
	}
	else if(percent > 35 && percent <= 40)
	{
		return 1;
	}
	else if(percent >= 30 && percent <= 35)
	{
		return 0;
	}
	else
	{
		return 2;
	}
	
	return 0;
}

/*CPU可运行队列的线程数评分函数*/
int get_cpu_run_threads(float num)
{
	if(num < 1)
	{
		return 1;
	}
	else if(num >= 1 && num <= 3)
	{
		return 0;
	}
	else if(num > 3 && num <=4)
	{
		return 3;
	}
	else if(num > 4 && num <=5)
	{
		return 4;	
	}
	else
	{
		return 5;
	}

	return 0;	
}

/*CPU IO等待评分函数*/
int get_cpu_iowait(float percent)
{	
	if(percent >=0 && percent <= 20)
	{
		return 0;
	}
	else if(percent > 20 && percent <= 30)
	{
		return 2;
	}
	else if(percent > 30 && percent <= 40)
	{
		return 4;
	}
	else
	{
		return 5;
	}
	
	return 0;	
}

/*CPU虚拟化评分函数*/               //已测试
int get_cpu_virtual(float flag)
{
	int tmp = (int)flag;	
	
	switch(tmp)
	{
		case 0:   //不支持虚拟化
			return 2;
			break;
		case 1:  //支持AMD提供的虚拟化
			return 1;
			break;
		case 2:  //支持Intel提供的虚拟化
			return 0;
			break;
		default:
			break;
	}

	return 0;
}

/*CPU超线程评分函数*/         //已测试
int get_cpu_hyper_threads(float flag)
{
	int tmp = (int)flag;	
	
	switch(tmp)
	{
		case 0:   //不支持超线程
			return 2;
			break;
		case 1:  //支持超线程
			return 0;
			break;
		default:
			break;
	}

	return 0;
}
/******************************************************************************************/

/*************************内存性能*****************************/
/*应用程序可用内存占用率评分函数*/
int get_mem_user(float percent)
{
	if(percent > 90 && percent <= 100)
	{
		return 5;
	}
	else if(percent > 80 && percent <= 90)
	{
		return 4;
	}
	else if(percent > 70 && percent <= 80)
	{
		return 2;
	}
	else
	{
		return 0;
	}		

	return 0;
}
/*************************************************************/

/************************************IO性能***************************************/
/*平均IO响应时间评分函数*/
int get_io_response(float time)
{
	if(time < 5)
	{
		return 0;
	}
	else if(time >= 5 && time < 6)
	{
		return 1;
	}
	else if(time >= 6 && time < 7)
	{
		return 2;
	}
	else if(time >= 7 && time < 8)
	{
		return 3;
	}
	else if(time >= 8 && time < 10)
	{
		return 4;
	}
	else
	{
		return 5;
	}
	
	return 0;
}

/*一秒中有百分之多少时间用于IO操作评分函数*/
int get_io_util(float percent)
{
	if(percent > 95 && percent <= 100)
	{
		return 5;
	}
	else if(percent > 90 && percent <= 95)
	{
		return 4;
	}
	else if(percent > 85 && percent <= 90)
	{
		return 3;
	}
	else if(percent > 80 && percent <= 85)
	{
		return 2;
	}
	else if(percent > 70 && percent <= 80)
	{
		return 1;
	} 
	else
	{
		return 0;
	}		
	
	return 0;
}

/*回收站垃圾文件评分函数*/
int get_io_junk_file(float flag)     //已测试
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //回收站垃圾文件不到1G
			return 0;
			break;
		case 1:  //回收站垃圾文件超过1G
			return 2;
			break;
		default:
			break;
	}	
	
	return 0;
}

/*磁盘损坏率评分函数*/
int get_io_checkdisk(float percent)
{
	if(percent == 0)
	{
		return 0;
	}
	else if(percent > 0 && percent <= 10)
	{
		return 1;
	}
	else if(percent > 10 && percent <= 20)
	{
		return 2;
	}
	else if(percent > 20 && percent <= 30)
	{
		return 3;
	}
	else if(percent > 30 && percent <= 40)
	{
		return 4;
	}
	else
	{
		return 5;
	}	

	return 0;
}

/*平均每次设备IO操作的服务时间评分函数*/
int get_io_opt_time(float time)
{
	if(time < 5)
	{
		return 0;
	}
	else if(time >= 5 && time <= 6)
	{
		return 1;
	}
	else if(time > 6 && time <= 7)
	{
		return 2;
	}
	else if(time > 7 && time <= 8)
	{
		return 3;
	}
	else if(time > 8 && time <= 9)
	{
		return 4;
	}
	else 
	{
		return 5;
	}		
	
	return 0;
}

/*IO队列请求数评分函数*/
int get_io_request(float num)
{
	if(num >= 0 && num <= 3)
	{
		return 0;
	}
	else if(num > 3 && num <= 4)
	{
		return 1;
	}
	else if(num > 4 && num <= 5)
	{
		return 2;
	}
	else if(num > 5 && num <= 6)
	{
		return 3;
	}
	else if(num > 6 && num <= 7)
	{
		return 4;
	}
	else
	{
		return 5;
	}			

	return 0;
}
/*********************************************************************************/

/************************网络性能******************************/
/*ARP攻击评分函数*/     //已测试
int get_net_arp(float res)
{
	int tmp = (int)res;

	return tmp;
}

/*火狐cookies跟踪评分函数*/      //已测试
int get_net_firefox_cookies(float flag)
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //无cookie
			return 0;
			break;
		case 1:  //有cookie
			return 1;
			break;
		default:
			break;
	}		

	return 0;
}

/*谷歌cookies跟踪评分函数*/     //已测试
int get_net_google_cookies(float flag)
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //无cookie
			return 0;
			break;
		case 1:  //有cookie
			return 1;
			break;
		default:
			break;
	}		

	return 0;
}

/*谷歌历史记录评分函数*/    //已测试
int get_net_google_history(float flag)
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //无cookie
			return 0;
			break;
		case 1:  //有cookie
			return 1;
			break;
		default:
			break;
	}		

	return 0;
}

/*用户最近使用文档跟踪记录评分函数*/
int get_recent_used(float flag)
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //无记录
			return 0;
			break;
		case 1:  //有记录
			return 2;
			break;
		default:
			break;
	}		

	return 0;
}

/*ARP是否开机自启动*/     //已测试
int get_net_init_arp(float flag)
{
	int tmp = (int)flag;

	switch(tmp)
	{
		case 0:   //ARP防护没有开机自启动
			return 3;
			break;
		case 1:  //ARP防护开机自启动
			return 0;
			break;
		default:
			break;
	}			

	return 0;
}
/**************************************************************/

/******************开机时间*********************/
/*开机时间评分函数*/
int get_start_time(float second)
{
	if(second <= 30)
	{
		return 0;
	}
	else if(second > 30 && second <= 40)
	{
		return 1;
	}
	else if(second > 40 && second <= 50)
	{
		return 2;
	}
	else if(second > 50 && second <= 60)
	{
		return 3;
	}
	else if(second > 60 && second <=90)
	{
		return 4;
	}
	else
	{
		return 5;
	}	

	return 0;
}
/***********************************************/

/*对指定项评分函数*/
int get_point(char *str,void *val)
{
	/*CPU*/	
	if(!strncmp("cpuuser",str,7))
	{
		float num = *((float*)val);
		return get_cpu_user(num);
	}

	if(!strncmp("cpusys",str,6))
	{
		float num1 = *((float*)val);
		return get_cpu_sys(num1);
	}

	if(!strncmp("cputhreads",str,10))
	{
		float num2 = *((float*)val);
		return get_cpu_run_threads(num2);
	}

	if(!strncmp("cpuiowait",str,9))
	{
		float num3 = *((float*)val);
		return get_cpu_iowait(num3);
	}
	
	if(!strncmp("cpuvirtual",str,10))
	{
		float num4 = *((float*)val);
		return get_cpu_virtual(num4);
	}

	if(!strncmp("cpuhyper",str,8))
	{
		float num5 = *((float*)val);
		return get_cpu_hyper_threads(num5);
	}
	
	/*内存*/
	if(!strncmp("memuser",str,8))
	{
		float num6 = *((float*)val);
		return get_mem_user(num6);
	}

	/*IO*/
	if(!strncmp("ioresponse",str,10))
	{
		float num7 = *((float*)val);		
		return get_io_response(num7);
	}
	
	if(!strncmp("ioutil",str,6))
	{
		float num8 = *((float*)val);		
		return get_io_util(num8);
	}

	if(!strncmp("iojunk",str,6))
	{
		float num9 = *((float*)val);		
		return get_io_junk_file(num9);
	}

	if(!strncmp("iocheck",str,7))
	{
		float num10 = *((float*)val);		
		return get_io_checkdisk(num10);
	}
	
	if(!strncmp("ioopt",str,5))
	{
		float num11 = *((float*)val);		
		return get_io_opt_time(num11);
	}

	if(!strncmp("iorequest",str,9))
	{
		float num12 = *((float*)val);		
		return get_io_request(num12);
	}

	/*网络*/
	if(!strncmp("netarp",str,6))
	{
		float num13 = *((float*)val);		
		return get_net_arp(num13);
	}

	if(!strncmp("netfirefox",str,10))
	{
		float num14 = *((float*)val);		
		return get_net_firefox_cookies(num14);
	}

	if(!strncmp("netgoogle",str,9))
	{
		float num15 = *((float*)val);		
		return get_net_google_cookies(num15);
	}

	if(!strncmp("nethistory",str,10))
	{
		float num16 = *((float*)val);		
		return get_net_google_history(num16);
	}

	if(!strncmp("netinitarp",str,10))
	{
		float num17 = *((float*)val);		
		return get_net_init_arp(num17);
	}

	/*开机时间*/
	if(!strncmp("starttime",str,9))
	{
		float num18 = *((float*)val);		
		return get_start_time(num18);
	}

	/*其它*/
	if(!strncmp("recentused",str,10))
	{
		float num19 = *((float*)val);		
		return get_recent_used(num19);
	}

	return 0;
}
