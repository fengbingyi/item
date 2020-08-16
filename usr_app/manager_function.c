/****************************************
 *Name        : manager_function.c        
 *Data        : 2020.08.12
 *Description : 实现管理员功能页面后台逻辑
 *Author      : 万家庆
 *Modification: None
 *
 ****************************************/
#include<stdio.h>
#include"menu.h"
#include"applib.h"
#include"msg.h"
extern msg_t msg;
/***************************************
 *Name       : manager_function
 *Description: 管理员功能页面后台逻辑
 *args       :
 *             @socketfd:套接字文件描述符
 *return     : 无
 ****************************************/
void manager_function(int socketfd)
{
	int choose     = 0 ;   /*用户选择变量定义*/
	int menu_maxno = 0 ;   /*菜单数量变量定义*/

	/*得到用户选择值*/
	while(1)
	{
		do{
			menu_maxno = menu_manager_function();
			menu_choose();
			scanf("%d",&choose);
			getchar();
		}while(!(choose > 0)&&(choose <= menu_maxno));

		/*执行选择功能*/
		switch(choose)
		{
		case 1:  add_user(socketfd)                ;break;
		case 2:  delect_user(socketfd)             ;break;
		case 3:  modify_information(socketfd)      ;break;
		case 4:  inquire_information(socketfd)     ;break;
		default:                                    break;
		}
		/*退出*/
		if(choose == menu_maxno){break;}
	}
}
