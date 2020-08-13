/****************************************
 *Name        : reg.c       
 *Data        : 2020.8.12
 *Description : 注册功能实现
 *Author      : 万家庆
 *Modification: 无
 *
 ****************************************/
#include<stdio.h>
#include<string.h>
#include"client.h"
#include"reg.h"
#include"msg.h"

extern msg_t msg;

/****************************************
 *Name       : reg_manager
 *Description: 注册管理员实现逻辑
 *args       : @socketfd:套接字文件描述符
 *return     : 成功返回OK
 *             失败返回NO
 ****************************************/
int reg_manager(int sockfd)
{
	char usr_buf[10] = {};	
	char pw_buf[10]  = {};
	char root[10]    = {};
	msg_t rev_msg;
	int ret = -1;

	printf("请输入超级用户权限\n");
	scanf("%s",root);
	getchar();
	if(strcmp(root,"666666")){
		return NO;
	}
	msg.cmd = REGISTER_MANAGER ;
	printf("请输入管理员名字:");
	scanf("%s",usr_buf);
	getchar();
	printf("请输入密码:");
	scanf("%s",pw_buf);
	getchar();

	bzero(msg.usr,10);
	bzero(msg.password,10);
	strncpy(msg.usr,usr_buf,10);
	strncpy(msg.password,pw_buf,10);

	client_send(sockfd,&msg,sizeof(msg));
	client_receive(sockfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		return OK;
	}else{
		return NO;
	}

}

/****************************************
 *Name       : reg_usr
 *Description: 注册用户实现逻辑
 *args       : @sockfd:套接字文件描述符
 *return     : 成功返回OK
 *             失败返回NO
 ****************************************/
int reg_usr(int sockfd)
{
	char usr_buf[10] = {};
	char pw_buf[10] = {};
	msg_t rev_msg;
	int ret = -1;
	msg.cmd = REGISTER_USR ;
	printf("请输入注册的用户名：");
	scanf("%s",usr_buf);
	getchar();
	printf("请输入注册的用户密码：");
	scanf("%s",pw_buf);
	getchar();
	bzero(msg.usr,10);
	bzero(msg.password,10);
	strncpy(msg.usr,usr_buf,10);
	strncpy(msg.password,pw_buf,10);
	client_send(sockfd,&msg,sizeof(msg));
	client_receive(sockfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		return OK;
	}else{
		return NO;
	}
}

/****************************************
 *Name       : reg
 *Description: 注册页面后台逻辑
 *args       : @socketfd:套接字文件描述符
 *return     : 无
 ****************************************/
void reg(int socketfd)
{
	int ret        = 0;
	int choose     = 0 ;   /*用户选择变量定义*/
	int menu_maxno = 0 ;   /*菜单数量变量定义*/
	/*得到用户输入值*/
	do{
		menu_maxno = menu_register();
		menu_choose();
		scanf("%d",&choose);
		getchar();
	}while(!(choose > 0)&&(choose <= menu_maxno));

	/*用户注册*/
	if(1 == choose)
	{
		ret = reg_usr(socketfd);
		if(OK == ret)
			printf("注册用户成功\n");
		else
			printf("注册用户失败\n");
	}

	/*管理员注册*/
	if(2 == choose)
	{
		ret = reg_manager(socketfd);
		if(OK == ret)
			printf("注册管理员成功\n");
		else
			printf("注册管理员失败\n");
	}	
}
