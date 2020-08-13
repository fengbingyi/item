/****************************************
 *Name        :usr_app.c
 *Data        :2020.08.11
 *Description :应用程序主程序
 *Author      : JiaqingWan
 *Modification: None
 *
 ****************************************/
#include<stdio.h>
#include<string.h>
#include"menu.h"
#include"msg.h"
#include"client.h"
#include"reg.h"
#include"login.h"

/*定义一个默认的变量供客户端和服务器测试使用*/
msg_t msg = {
	.cmd         = LOG_USR,
	.usr[0]      = 'N',
	.pri         = 'U',
	.name[0]     = 'N',     
	.age         = 18,         
	.sex         = MAN,          
	.password[0] = 'N', 
	.number      = 1,       
	.salary      = 10000,       
	.dept[0]     = 'N',     
	.inq_mode    = ALL_INFO,     
	.inq_cnt     = 10,      
	.status      = 1,
};

int main(int argc, const char *argv[])
{
	int choose     = 0 ;   /*用户输入选择*/
	int menu_maxno = 0 ;   /*菜单选项个数*/
	int socketfd   = -1;   /*套接字文件描述符*/
	int fd = client_init();/*初始化客户端*/
	while(1){
		do{
			/*显示欢迎菜单主界面*/
			menu_maxno = menu_wellcome();
			menu_choose();
			/*获取用户原则值   */
			scanf("%d",&choose);
			getchar();
		}while(!(choose > 0)&&(choose <= menu_maxno));

		/*执行用户原则的功能  */
		switch(choose){
		case 1:reg(fd)  ;break;
		case 2:login(fd);break;
		}
		/*退出*/
		if(menu_maxno == choose)break;
	}
	client_exit(socketfd);
	return 0;
}

