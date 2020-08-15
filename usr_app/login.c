/****************************************
 *Name        : login.c        
 *Data        : 2020.08.12
 *Description : 实现登录功能
 *Author      : JiaqingWan
 *Modification: None
 *
 ****************************************/
#include<stdio.h>
#include<string.h>
#include"menu.h"
#include"usr_function.h"
#include"manager_function.h"
#include"msg.h"

extern msg_t msg;/*从主函数文件中获得变量值*/

/****************************************
 *Name       : login_manager
 *Description: 管理员登录功能实现
 *args       : @socketfd:套接字文件描述符
 *return     : 登录成功返回OK
 *             失败返回NO
 ****************************************/
int login_manager(int socketfd)
{
	char usr_buf[20] = {}; 
	char pw_buf[20] = {};
	msg_t rev_msg;
	int ret = -1;	
	/*fill login manager command */
	msg.cmd = LOG_MANAGER ;
	/*输入管理员名字 */
	printf("请输入管理员名字：");
	scanf("%s",usr_buf);
	getchar();

	/*输入管理员密码*/
	printf("请输入密码：");
	scanf("%s",pw_buf);
	getchar();

	/*将得到信息填充到信息结构体中*/
	bzero(msg.usr,20);
	bzero(msg.password,20);
	strncpy(msg.usr,usr_buf,20);
	strncpy(msg.password,pw_buf,20);

	/*与服务器通信*/
	client_send(socketfd,&msg,sizeof(msg));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));

	if(OK == rev_msg.status){
		/*将管理员权限写入*/
		strcpy(msg.pri,MANAGER);
		return OK;
	}
	return NO;
}

/****************************************
 *Name       : login_user
 *Description: 用户登录功能实现
 *args       : @socketfd:套接字文件描述符    
 *return     : 登录成功返回OK
 *             失败返回NO
 ****************************************/
int login_user(int socketfd)
{
	char usr_buf[20] = {}; /*用户名缓存*/
	char pw_buf[20] = {};  /*密码缓存*/
	msg_t rev_msg;         /*从服务器收到的信息*/
	int ret = -1;	
	msg.cmd = LOG_USR ;
	printf("请输入用户名字：");
	scanf("%s",usr_buf);
	getchar();
	printf("请输入用户密码：");
	scanf("%s",pw_buf);
	getchar();
	bzero(msg.usr,20);
	bzero(msg.password,20);
	strncpy(msg.usr,usr_buf,20);
	strncpy(msg.password,pw_buf,20);
	client_send(socketfd,&msg,sizeof(msg));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));

	if(OK == rev_msg.status){
		strcpy(msg.pri, USER);
		return OK;
	}
	return NO;
}

/****************************************
 *Name       : login
 *Description:登录主界面执行逻辑
 *args       : @socketfd:套接字文件描述符
 *return     : 无
 ****************************************/
void login(int socketfd)
{
	char usr_buf[20] = {};
	char pw_buf[20] = {};
	msg_t rev_msg;
	int ret = -1;
	int choose     = 0 ;   /*用户输入选择*/
	int menu_maxno = 0 ;   /*菜单选项个数*/
	do{
		menu_maxno = menu_login();
		menu_choose();
		scanf("%d",&choose);
		getchar();
	}while(!(choose > 0)&&(choose <= menu_maxno));

	/*用户登录，登录成功跳到用户功能选择界面*/

	if(1 == choose)
	{
		ret = login_user(socketfd);
		if(OK == ret ){
			user_function(socketfd);
		}else{
			printf("登录失败\n");
		}
	}

	/*管理员登录，登录成功跳转到管理员功能界面*/
	if(2 == choose)
	{
		ret = login_manager(socketfd);
		if(OK == ret ){
			manager_function(socketfd);
		}else{
			printf("登录失败\n");
		}
	}

}
