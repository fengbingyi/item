/****************************************
*Name        : applib.h     
*Data        : 2020.08.12
*Description : 用户和管理员的功能实现库
*Author      : 万家庆
*Modification: 无
*
****************************************/
#ifndef __APPLIB_H__
#define __APPLIB_H__
#include"msg.h"

/****************************************
*Name       : add_usr
*Description: 完成用户的添加
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void idd_user(int socketfd);

/****************************************
*Name       : delect_user
*Description: 从数据库中删除用户
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void delect_user(int socketfd);

/****************************************
*Name       : inquire_information
*Description: 查询信息
*args       : socketfd:套接字文件描述符
*return     : 无
****************************************/
void inquire_information(int socketfd);

/****************************************
*Name       : modify_information
*Description: 修改信息
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void modify_information(int socketfd);

/****************************************
*Name       : renew_password
*Description: 修改密码
*args       : @socketfd:套接字文件描述符
*return     : 无
****************************************/
void renew_password(int socketfd);

#endif
