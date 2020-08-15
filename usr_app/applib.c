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

	printf("请输入你想添加的用户名\n>");
	scanf("%s",msg_add.usr     );
	getchar();

	printf("请输入你想添加的姓名\n>");
	scanf("%s",msg_add.name    );
	getchar();

	printf("请输入你想添加的年龄\n>");
	scanf("%d",&msg_add.age    );
	getchar();

	printf("请输入你想添加的性别\n>");
	scanf("%s",msg_add.sex    );
	getchar();

	printf("请输入你想添加的密码\n>");
	scanf("%s",msg_add.password);
	getchar();

	printf("请输入你想添加的薪水\n>");
	scanf("%d",&msg_add.salary );
	getchar();

	printf("请输入你想添加的部门\n>");
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
	printf("请输入你想删除的用户\n>");
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
 *return     : 无
 ****************************************/
void inquire_information(int socketfd) 
{
	msg_t rev_msg;
	msg.cmd = INQUIRE_INFO;
	client_send(socketfd,&msg,sizeof(msg));
	if(strcmp(msg.pri,USER) == 0){
		client_receive(socketfd,&rev_msg,sizeof(rev_msg));
		printf("1.姓名：%s\n", msg.name    );
		printf("2.年龄：%d\n", msg.age     );
		printf("3.性别：%s\n", msg.sex     );
		printf("4.密码：%s\n", msg.password);
		printf("5.工号：%d\n", msg.number  );
		printf("6.薪水：%d\n", msg.salary  );
		printf("7.部门：%s\n", msg.dept    );
	}else{
		msg.inq_cnt = 1;/*标记开始接收信息*/
		while(msg.inq_cnt >= 1){
			client_receive(socketfd,&rev_msg,sizeof(rev_msg));
			printf("姓名:%s\t年龄:%d\t性别:%s\t工号:%d\t薪水:%d\t部门:%s\n",
					msg.name,
					msg.age,
					msg.sex,
					msg.number,
					msg.salary,
					msg.dept);
		}
	}
}      

/****************************************
 *Name       : modify_information
 *Description: 修改信息
 *args       : @socketfd:套接字文件描述符
 *return     : 无
 ****************************************/
void modify_information(int socketfd)
{
	int choose     = 0 ;   /*用户选择值                  */
	int menu_maxno = 0 ;   /*菜单项数目                  */
	char usr_buf[20] = {}; /*管理员名字缓存*/
	char sex_buf[20] = {}; /*性别缓存*/
	int ret = 0 ;
	int manager_flag = 0;  /*本次操作为管理员时需要标记为1，
							 不是则为0*/
	msg_t msg_mod = msg;
	msg_t rev_msg;
	inquire_information(socketfd);
	/*如果是管理员，需要先得到要修改的用户名*/
	if(strcmp(msg.pri,MANAGER) == 0){
		/*需要将当前管理员权限信息备份*/
		manager_flag = 1;   /*标记此次操作为管理员*/
		strncpy(msg.pri,USER,20);
		strncpy(usr_buf,msg.usr,20);
		/*获取要修改的用户名*/
		printf("请输入要修改的用户名\n>");
		scanf("%s",msg.usr);
		getchar();
	}

	/*获得查询用户的资料信息*/
	inquire_information(socketfd);
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
			printf("请输入要修改的姓名\n>");
			do{
				ret = scanf("%s",msg.name);
				getchar();
			}while(ret <= 0);
		}
		if(choose == 2)
		{
			printf("请输入要修改的年龄\n>");
			do{
				ret = scanf("%d",&msg.age);
				getchar();
			}while(ret <= 0);
		}
		if(choose == 3)
		{
			printf("请输入要修改的性别\n>");	
			do{
				ret = scanf("%s",sex_buf);      /*暂时没加参数检测*/
				getchar();
			}while(ret <= 0);
			if((strcmp(sex_buf,MAN) == 0 )||
					(strcmp(sex_buf,WONMAN) == 0)){
				/*参数正确情况下将之修改*/
				strncpy(msg.sex,sex_buf,20);
			}else{
				printf("性别参数输入错误\n");
			}
		}

		if(choose == 4)
		{
			if(strcmp(msg.pri,MANAGER) == 0){
				printf("请输入要修改的密码\n>");
				do{
					ret = scanf("%s",msg.password); /*暂时没添加参数检测*/
					getchar();
				}	while(ret <= 0);
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 5)
		{
			if(strcmp(msg.pri,MANAGER) == 0){
				printf("请输入要修改的工号\n>");
				do{
					ret = scanf("%d",&msg.number);
					getchar();
				}while(ret <= 0);
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 6)
		{
			if(strcmp(msg.pri,MANAGER) == 0){
				printf("请输入要修改的薪水\n>");
				do{
					ret = scanf("%d",&msg.salary);
					getchar();
				}	while(ret <= 0);
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 7)
		{
			if(strcmp(msg.pri,MANAGER) == 0){
				printf("请输入要修改的部门\n>");
				do{
					ret = scanf("%s",msg.dept);
					getchar();
				}while(ret <= 0);
			}else{
				printf("本项修改权限不足\n");
			}
		}

		if(choose == 0)break;
	}
	/*修改信息完成，开始发送到服务器，修改数据库*/
	client_send(socketfd,&msg_mod,sizeof(msg_mod));
	client_receive(socketfd,&rev_msg,sizeof(rev_msg));
	if(OK == rev_msg.status){
		printf("数据库中修改成功\n");
	}else{
		printf("数据库中修改失败\n");
	}
	/*将管理员的名字恢复*/
	if(manager_flag == 1){
		/*把管理员权限拷贝回来*/
		strncpy(msg.pri,MANAGER,20);
		/*把管理员用户名拷贝回来*/
		strncpy(msg.usr,usr_buf,20);
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
	char pw_buf[20] = {};
	char pw_buf2[20] = {};
	msg_t rev_msg;

	msg.cmd = VERIFY_PASSWORD;
	printf("请输入你要修改的密码>");
	scanf("%s",pw_buf);               /*参数检测待完善*/
	getchar();
	printf("请再次输入你要修改的密码>");
	scanf("%s",pw_buf2);               /*参数检测待完善*/
	getchar();
	/*当两次输入密码不一样的时候，修改失败*/
	if(strcmp(pw_buf,pw_buf2)){
		printf("你两次输入的密码不一样，修改密码失败\n");
		return ;
	}
	strncpy(msg.password,pw_buf,20);
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

