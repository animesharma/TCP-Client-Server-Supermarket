#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
	int s,n;
	char servName[100]="127.0.0.1";
	int servPort;
	//char string[100];
	int maxlen = 256;
	char buffer[256+1];
	char* ptr = buffer;
	struct sockaddr_in servAddr;
	servPort=6960;
	int resp,*res=&resp;
	
	
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, servName, &servAddr.sin_addr);
	servAddr.sin_port = servPort;
	
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error : Socket creation failed");
		exit(1);
	}
	
	if((connect(s, (struct sockaddr*) &servAddr, sizeof(servAddr))) < 0)
	{
		perror("Error : Connection failed");
		exit(1);
	}
	while(1)
	{
		n = recv(s,ptr,maxlen,0);
		buffer[n]='\0';
		printf("%s",buffer);
		scanf("%d",res);
		send(s, res,sizeof(int), 0);
	}
	close(s);
	exit(0);
}
