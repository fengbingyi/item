/****************************************
 *Name        : client.c        
 *Data        : 2020.08.07
 *Description : 实现客户端和服务器通信的接口
 *Author      : 万家庆
 *Modification: None
 *
 ****************************************/

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  SERV_PORT    "6666"
#define  SERV_IP_ADDR "192.168.5.106"
#define  QUIT         "quit"

/****************************************
 *Name       : client_init
 *Description: 客户端初始化函数
 *args       :无
 *return     :套接字文件描述符 
 ****************************************/
int client_init()
{
	//创建用于通讯套接字
	int fd = -1;
	if( (fd = socket(AF_INET,SOCK_STREAM,0)) <0){
		perror("socket");
		exit(1);
	}

	/*链接服务器*/
	//创建结构体
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	//填充结构体
	sin.sin_family   = AF_INET;
	sin.sin_port     = htons(atoi(SERV_PORT));
	if( inet_pton(AF_INET,SERV_IP_ADDR,
				(void*)&sin.sin_addr.s_addr) !=1){
		perror("inet_pton");
		exit(1);
	}

	/*连接服务器*/
	if( connect(fd,(struct sockaddr*)&sin,sizeof(sin)) <0){
		perror("connect");
		exit(1);
	}

	puts("客户端链接成功！");

	return fd;
}

/****************************************
 *Name       : client_exit
 *Description: 关闭客户端
 *args       : @fd：套接字文件描述符
 *return     : 无
 ****************************************/
void client_exit(int fd)
{
	close(fd);
} 

/****************************************
 *Name       : client_send
 *Description: 将信息发送给服务器
 *args       :@socketfd：套接字文件描述符
              @buf: 发送缓存的地址
              @len: 发送长度
 *return     : 发送个数 
 ****************************************/
int client_send(int sockfd, const void *buf, size_t len)
{
	int ret = -1;
	do{//如果被打断则重新发消息
		ret = send(sockfd,buf,len,0);
	}while(EINTR ==errno);
	if(ret<=0){
		perror("TCPsend:");
		exit(1);
	}
	return ret;
}

/****************************************
 *Name       : client_receive
 *Description: 从客户端接收信息
 *args       :@fd：socket fd
              @buf:接收信息缓存的地址
              @len:接收信息的长度
 *return     : 接收信息的个数
 ****************************************/
int client_receive(int sockfd, void *buf, size_t len)
{
	int ret = -1;
	ret = recv(sockfd,buf,len,0);
	if(ret<0){
		perror("TCPrecv:");
		exit(1);
	}

	if(ret == 0){
		perror("server closed:");
	}
	return ret;
}

/*供测试使用*/
#if 0
int main(int argc, char *argv[])
{
	int fd = -1;
	fd = client_init();

	/*读写数据*/
	char buf[BUFSIZ]={};
	int ret = -1;
	while(1){
		bzero(buf,BUFSIZ);
		if( NULL == fgets(buf,BUFSIZ-1,stdin) )
			continue;

		ret = client_send(fd,buf,strlen(buf)); 
		if(0 == ret)break;//对方已经关闭
		//if(!ret)break;//等效上面这一句

		//发送成功
		puts("---------发送成功--------");

		bzero(buf,BUFSIZ);
		ret = client_receive(fd,buf,BUFSIZ); 
		printf("接收到信息:%s",buf);		
		if(0 == ret)break;//对方已经关闭

		//判断是否要退出
		if(0 == strncasecmp(buf,QUIT,strlen(QUIT))){
			puts("++++++你已经退出+++++++");
			break;
		}
	}
	client_exit(fd);
	return 0;
}
#endif
