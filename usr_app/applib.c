/****************************************
*Name        : applib.c        
*Data        : 2020.08.12
*Description : 用户和管理员的功能实现库
*Author      : 万家庆
*Modification: 无
*
****************************************/
#include<stdio.h>
#include<string.h>
#include"msg.h"
#include"client.h"
extern msg_t msg;/*从主函数文件中获得变量值*/

/****************************************
*Name       : add_usr
*Description: 完成用户的添加
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void add_user(int socketfd)
{
	msg_t msg_add;
	msg_t rev_msg;
	msg_add = msg;
	msg_add.cmd = ADD_USR;
	
	printf("请输入你想添加的用户名>");
	scanf("%s",msg_add.usr     );
	getchar();
	
	printf("请输入你想添加的姓名>");
	scanf("%s",msg_add.name    );
	getchar();
	
	printf("请输入你想添加的年龄>");
	scanf("%d",&msg_add.age    );
	getchar();
	
	printf("请输入你想添加的性别>");
	scanf("%s",msg_add.sex    );
	getchar();
	
	printf("请输入你想添加的密码>");
	scanf("%s",msg_add.password);
	getchar();
	
	printf("请输入你想添加的薪水>");
	scanf("%d",&msg_add.salary );
	getchar();
	
	printf("请输入你想添加的部门>");
	scanf("%s",msg_add.dept    );
	getchar();
	
	/*ready to add to server*/
	client_send(socketfd,&msg_add,sizeof(msg_add));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		printf("添加成功\n");
	}else{
		printf("添加失败\n");
	}

}

/****************************************
*Name       : delect_user
*Description: 从数据库中删除用户
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void delect_user(int socketfd)
{
	msg_t msg_del;
	msg_t rev_msg;
	msg_del = msg;
	msg_del.cmd = DELECT_USR;
	printf("请输入你想删除的用户>");
	scanf("%s",msg_del.usr);
	client_send(socketfd,&msg_del,sizeof(msg_del));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		printf("删除成功\n");
	}else{
		printf("删除失败\n");
	}
}   

/****************************************
*Name       : inquire_information
*Description: 查询信息
*args       : socketfd:套接字文件描述符
*             msg_inq:要查询的消息结构体
*return     : msg消息结构体
****************************************/
msg_t inquire_information(int socketfd, msg_t msg_inq) 
{
	msg_t rev_msg;
	msg_inq.cmd = INQUIRE_INFO;
	client_send(socketfd,&msg_inq,sizeof(msg_inq));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	printf("1.姓名：%s\n", rev_msg.name    );
	printf("2.年龄：%d\n", rev_msg.age     );
	printf("3.性别：%s\n", rev_msg.sex     );
	printf("4.密码：%s\n", rev_msg.password);
	printf("5.工号：%d\n", rev_msg.number  );
	printf("6.薪水：%d\n", rev_msg.salary  );
	printf("7.部门：%s\n", rev_msg.dept    );
	return rev_msg;
}    

/****************************************
*Name       : modify_information
*Description: 修改信息
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void modify_information(int socketfd)
{
	int choose     = 0 ;   /*the choose of selection     */
	int menu_maxno = 0 ;   /*max number of menu          */
	msg_t msg_mod = msg;
	msg_t rev_msg;
	inquire_information(socketfd,msg);
	/*如果是管理员，需要先得到要修改的用户名*/
	if(strcmp(msg.pri,MANAGER) == 0){
		printf("请输入要修改的用户名>");
		scanf("%s",msg_mod.usr);
		getchar();
	}

	/*获得查询用户的资料信息*/
	msg_mod = inquire_information(socketfd,msg_mod);
	/*进入修改循环*/
	while(1){
		do{
			menu_modify();			
			menu_choose();
			scanf("%d",&choose);
			getchar();
		}while(!(choose>=0 && choose < 8));
		if(choose == 1)
		{
			printf("请输入要修改的姓名>");
			scanf("%s",msg_mod.name);
			getchar();
		}
		if(choose == 2)
		{
			printf("请输入要修改的年龄>");
			scanf("%d",&msg_mod.age);
			getchar();
		}
		if(choose == 3)
		{
			printf("请输入要修改的性别>");
			scanf("%s",msg_mod.sex);      /*暂时没加参数检测*/
			getchar();
		}

		if(choose == 4)
		{
			if(msg.pri == MANAGER){
			printf("请输入要修改的密码>");
			scanf("%s",msg_mod.password); /*暂时没添加参数检测*/
			getchar();
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 5)
		{
			if(msg.pri == MANAGER){
			printf("请输入要修改的工号>");
			scanf("%d",&msg_mod.number);
			getchar();
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 6)
		{
			if(msg.pri == MANAGER){
			printf("请输入要修改的薪水>");
			scanf("%d",&msg_mod.salary);
			getchar();
			}else{
				printf("本项修改权限不足\n");
				break;
			}
		}

		if(choose == 7)
		{
			if(msg.pri == MANAGER){
				printf("请输入要修改的部门>");
				scanf("%s",msg_mod.dept);
				getchar();
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 0)break;
	}
	/*modify infomation finished，begin to send*/
	client_send(socketfd,&msg_mod,sizeof(msg_mod));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		printf("数据库中修改成功\n");
	}else{
		printf("数据库中修改失败\n");
	}
} 

/****************************************
*Name       : renew_password
*Description: 修改密码
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void renew_password(int socketfd)
{
	char pw_buf[10] = {};
	msg_t rev_msg;

	msg.cmd = VERIFY_PASSWORD;
	printf("请输入你要修改的密码>");
	scanf("%s",pw_buf);               /*参数检测待完善*/
	strncpy(msg.password,pw_buf,10);
	client_send(socketfd,&msg,sizeof(msg));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		printf("密码修改成功\n");
	}else{
		printf("密码修改失败\n");
	}
}  

/****************************************
*Name       : inquire_history
*Description: 查询登录历史信息
*args       : @socketfd
*return     : 无
****************************************/
void inquire_history(int socketfd)
{
	printf("待开发\n");
}  

