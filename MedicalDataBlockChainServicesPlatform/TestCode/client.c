#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnum 3333

int main()
{
	struct sockaddr_in server_addr;
	char buffer[128];
	
	//1.�����׽���
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("create socket error!\n");
		exit(1);
	}
	
	//2.1����Ҫ���ӵķ������ĵ�ַ
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnum);
	server_addr.sin_addr.s_addr = inet_addr("192.168.103.100");
	
	//2.���ӷ�����
	if(connect(sockfd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr)) == -1)
	{
		printf("connect error\n");
		exit(1);
	}
	
	//3.�������ݵ�������
	printf("please input char:\n");
	fgets(buffer,128,stdin);
	send(sockfd, buffer, strlen(buffer), 0);
	
	//4.�ر�����
	close(sockfd);
	
	return 0;
	
}