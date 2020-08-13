/****************************************
 *Name        : usr_function.c        
 *Data        : 2020.08.12
 *Description : 用户界面功能实现
 *Author      : JiaqingWan
 *Modification: None
 *
 ****************************************/
#include<stdio.h>
#include"msg.h"

extern msg_t msg;/*从主函数文件中获得变量值*/


/****************************************
 *Name       : user_function
 *Description: 用户功能页后台逻辑
 *args       :
 *             @socketfd:套接字文件描述符
 *return     : 无
 ****************************************/
void user_function(int socketfd)
{
	int choose     = 0 ;   /*用户选择变量定义*/
	int menu_maxno = 0 ;   /*菜单数量变量定义*/

	/*得到用户选择值*/
	while(1){
		do{
			menu_maxno = menu_user_function();
			menu_choose();
			scanf("%d",&choose);
		}while(!(choose > 0)&&(choose <= menu_maxno));
		switch(choose){
		case 1:  inquire_information(socketfd);break;
		case 2:  renew_password(socketfd)     ;break;
		case 3:  modify_information(socketfd) ;break;
		case 4:  inquire_history(socketfd)    ;break;
		default:                               break;
		}

		if(choose == 5)break;
	}
}




