/****************************************
*Name        : login.h      
*Data        : 2020.08.12
*Description : 实现登录功能
*Author      : JiaqingWan
*Modification: None
*
****************************************/
#ifndef __LOGIN_H__
#define __LOGIN_H__

/****************************************
*Name       : login_manager
*Description: 管理员登录功能实现
*args       :
              @socketfd:套接字文件描述符
*return     : 登录成功返回OK
              失败返回NO
****************************************/
int login_manager(int socketfd);

/****************************************
*Name       : login_user
*Description: 用户登录功能实现
*args       :  
               @socketfd:套接字文件描述符    
*return     :  登录成功返回OK
               失败返回NO
****************************************/
int login_user(int socketfd);

/****************************************
*Name       : login
*Description:登录主界面执行逻辑
*args       :
              @socketfd:套接字文件描述符
*return     : 无
****************************************/
void login(int socketfd);

#endif