#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#define MAXDATASIZE 128 
int main(){
	int sockListen;
	if((sockListen = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		printf("socket fail\n");
		return -1;
	}
	int set = 1;
	setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(int));
	struct sockaddr_in recvAddr;
	memset(&recvAddr, 0, sizeof(struct sockaddr_in));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(4001);
	recvAddr.sin_addr.s_addr = INADDR_ANY;
	// 必须绑定，否则无法监听
	if(bind(sockListen, (struct sockaddr *)&recvAddr, sizeof(struct sockaddr)) == -1){
		printf("bind fail\n");
		return -1;
	}

	int recvbytes;
	char recvbuf[MAXDATASIZE];
	int addrLen = sizeof(struct sockaddr_in);
	printf("receive broadCast messgse now\n");
	while(1){
		recvbytes = recvfrom(sockListen, recvbuf, MAXDATASIZE, 0,(struct sockaddr *)&recvAddr, &addrLen);
		if( recvbytes != -1){
			recvbuf[recvbytes-1] = '\0';
			printf("receive a broadCast messgse:%s from %s \n", recvbuf,inet_ntoa(recvAddr.sin_addr));
		}else{
			printf("recvfrom fail\n");
		}	
	
	}

	close(sockListen);
	return 0;
}
