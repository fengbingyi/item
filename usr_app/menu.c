/****************************************
 *Name        : menu.c        
 *Data        : 2020.08.07
 *Description : 显示菜单
 *Author      : 万家庆
 *Modification: None
 *
 ****************************************/

/************the includes**************/
#include<stdio.h>

/****************************************
 *Name       : menu_wellcome()
 *Description: 显示欢迎主界面
 *args       : @无
 *return     :菜单选项个数
 ****************************************/
int menu_wellcome()
{
	printf("\n");
	printf("***********欢迎***************\n");
	printf("1.注册\n");
	printf("2.登录\n");
	printf("3.退出\n");
	printf("******************************\n");
	return 3;
}

/****************************************
 *Name       :menu_register
 *Description:display the register menu
 *args       :@无
 *return     :菜单选项个数 
 ****************************************/
int menu_register()
{
	printf("\n");
	printf("***********注册***************\n");
	printf("1.注册用户\n");
	printf("2.注册管理员\n");
	printf("******************************\n");
	return 2;
}

/****************************************
 *Name       : menu_login
 *Description: 显示登录界面
 *args       : 无
 *return     : 菜单选项个数
 ****************************************/
int menu_login()
{
	printf("\n");
	printf("*************登录*************\n");
	printf("1.用户登录\n");
	printf("2.管理员登录\n");
	printf("******************************\n");
	return 2;
}

/****************************************
 *Name       : menu_user_function
 *Description: 显示用户功能菜单
 *args       : 无
 *return     : 菜单选项个数 
 ****************************************/
int menu_user_function()
{
	printf("\n");
	printf("*************用户*************\n");
	printf("1.查询信息\n");
	printf("2.修改密码\n");
	printf("3.修改信息\n");
	printf("4.查询登录历史\n");
	printf("5.退出\n");
	printf("******************************\n");
	return 4;
}

/****************************************
 *Name       : menu_manager_function
 *Description: 显示管理员功能菜单
 *args       : 无
 *return     : 菜单选项个数 
 ****************************************/
int menu_manager_function()
{
	printf("\n");
	printf("**********管理员**************\n");
	printf("1.增加用户\n");
	printf("2.删除用户\n");
	printf("3.修改信息\n");
	printf("4.查询信息\n");
	printf("5.查询登录历史\n");
	printf("6.退出\n");
	printf("******************************\n");
	return 6;
}



/****************************************
 *Name       : menu_modify
 *Description: 修改信息界面
 *args       :无
 *return     : 选项个数
 ****************************************/
int  menu_modify()
{
	printf("\n");
	printf("******************************\n");
	printf("M 需要管理员权限\n");
	printf("1.姓名 2.年龄 3.性别 4.密码(M) \n");
	printf("5.工号(M) 6.薪水(M) 7.部门(M) 0.完成修改\n");
	printf("******************************\n");
	return 8;
}


/****************************************
 *Name       : menu_choose
 *Description: 显示选择命令行
 *args       :空
 *return     :空
 ****************************************/
void  menu_choose()
{
	printf("你的选择>");
}

/*页面显示测试函数，0不测试，1测试*/
#if  0

int main(int argc, const char *argv[])
{
	menu_wellcome();
	menu_register();
	menu_login();
	menu_user_function();
	menu_manager_function();
	menu_modify();
	menu_choose();
	return 0;
}


#endif
