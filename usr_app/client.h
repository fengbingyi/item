#ifndef __CLIENT_H__
#define __CLIENT_H__

/****************************************
*Name       : client_init
*Description: 客户端初始化函数
*args       :无
*return     :套接字文件描述符 
****************************************/
int client_init();

/****************************************
*Name       : client_exit
*Description: 关闭客户端
*args       :
              @fd：套接字文件描述符
*return     : 无
****************************************/
void client_exit(int fd);

/****************************************
*Name       : client_send
*Description: 将信息发送给服务器
*args       :
              @socketfd：套接字文件描述符
			  @buf: 发送缓存的地址
			  @len: 发送长度
*return     : 发送个数 
****************************************/
int client_send(int sockfd, const void *buf, size_t len);

/****************************************
*Name       : client_receive
*Description: 从客户端接收信息
*args       :
              @fd：socket fd
			  @buf:接收信息缓存的地址
			  @len:接收信息的长度
*return     : 接收信息的个数
****************************************/
int client_receive(int sockfd, void *buf, size_t len);



#endif