#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define portnum 3333

int main()
{
	int sockfd;
	int new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	char buffer[128];
	int nByte;
	int sin_size;
	
	//1.创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("create socket error!\n");
		exit(1);
	}
	
	//2.1设置要绑定的地址
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnum); //字节序(大小端)
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		
	//2.绑定地址
	bind(sockfd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr));
	
	//3.监听端口
	listen(sockfd,5);
		
	while(1)
	{
		//4.等待连接
		sin_size = sizeof(struct sockaddr);
		new_fd = accept(sockfd,(struct sockaddr*)(&client_addr),&sin_size);//注意:第3个参数为socklen_t*（整形的指针）
		printf("server get connection from %s\n",inet_ntoa(client_addr.sin_addr)); //将整数型的IP地址转化为字符型(192.168.1.1)
		
		//5.接收数据
		nByte = recv(new_fd, buffer, 128, 0);
		buffer[nByte] = '\0';
		printf("server reciivd : %s\n", buffer);
		
		//6.结束连接
		close(new_fd);
	}	
	
	close(sockfd);
	
	return 0;
	
}	