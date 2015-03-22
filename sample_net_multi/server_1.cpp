//头文件和变量的设置
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
  	//删除之前的套接字，为服务器创建一个未命名的套接字   	
	//delete before socket , create new unkown socket
	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	
	//命名套接字
	//name socket
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address, server_len);
	//创建一个链接队列，开始等待客户链接
	//create a linked queue, begin waite custom come
	listen(server_sockfd, 5);
	while(1){
		char ch;
		printf("server waiting\n");
	
		//accept a link
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
					(struct sockaddr *)&client_address,						(socklen_t *)&client_len);
	
		//about client_sockfd run read/wirte operation
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}
}
