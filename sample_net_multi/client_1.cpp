#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'A';

        //create a socket
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0 );

	//server set solution to this socket of name 
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	//this socket connect to server of socket
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(-1 == result){
		perror("oops : client1 ");
		exit(1);
	}

	//end , use sockfd read/write operation
	write(sockfd, &ch, 1);
	read(sockfd, &ch ,1);
	printf("char from server = %c\n",ch);
	close(sockfd);
	exit(0);
}
