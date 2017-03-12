#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "databasehandler.h"

using namespace std;

int ls, s;
char buffer[256];
char *ptr = buffer;
int maxlen = sizeof(buffer);
int n = 0;
int waitSize = 16;
int resp,*res=&resp;
string prompt1="1. Buyer 2. Seller\n";
string prompt2="1. Menu 2.Bill 3.Exit\n";
string prompt;

void showMenu(){
	prompt=getCategories();
	ptr=&prompt[0];
	send(s,ptr,sizeof(prompt),0);
	n=recv(s,res,sizeof(int),0);
}

void startBuyerProcess(){
	while(1){
		ptr=&prompt2[0];
		send(s,ptr,prompt2.size(),0);
		n=recv(s,res,sizeof(int),0);
		if(resp==1){
			showMenu();
		}
	}
}


void startUserInteraction(){
	ptr=&prompt1[0];
	send(s,ptr,prompt1.size(),0);
	n=recv(s,res,sizeof(int),0);
	if(resp==1){
		startBuyerProcess();
	}else{
		//startSellerProcess();
	}
}
	
	/*
	while((n = recv(s, ptr, maxlen, 0))>0)
	{
			if(n<0)
			{
				printf("/nError : Null Value Recieved");
			}
			else
			{
				printf("%.*s\n",n,buffer);
				send(s, buffer, n, 0);
			}
		
	}
	*/

int main()
{
	struct sockaddr_in servAddr, clntAddr;
	socklen_t clntAddrLen;
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = 6960;
	
	if((ls = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error : Listen socket failed");
		exit(1);
	}
	
	if((bind(ls,(struct sockaddr*) &servAddr, sizeof(servAddr))) < 0)
	{
		perror("Error : Bind failed");
		exit(1);
	}
	
	if(listen(ls, waitSize) < 0)
	{
		perror("Error : Listening failed");
		exit(1);
	}
	
	clntAddrLen=sizeof clntAddr;
	
	
	while(1)
	{
		if((s = accept(ls, (struct sockaddr*)&clntAddr, &clntAddrLen)) < 0)
		{
			perror("Error : Accepting failed");
			exit(1);
		}	
		
		startUserInteraction();

		close(s);
	}
}
