//
//  client.c
//  udp
//
//  Created by lovekun on 14-11-2.
//  Copyright (c) 2014�� care.jiangnan. All rights reserved.
//

/*client.c*/

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> /* netbd.h is needed for struct hostent =) */

#define PORT 1234 /* Open Port on Remote Host */
#define MAXDATASIZE 100 /* Max number of bytes of data */

/*
 udp�V��ͨӍ�����Еr��Ҫ�ɂ��������£�
 ./client 192.168.1.255
 �@�ӱ����192.168.1�@���W�΃������_��./server�����C�l���Y��
 */
int main(int argc, char *argv[])
{
    
    int fd, numbytes; /* files descriptors */
    char recvbuf[MAXDATASIZE]; /* buf will store received text */
    char sendbuf[MAXDATASIZE];
    struct hostent *he; /* structure that will get information about remote host */
    struct sockaddr_in server,client; /* server's address information */
    int yes;
    
    /* this is used because our program will need two argument (IP address and a message */
    
    if (argc !=2) {
        printf("Usage: %s <IP Address> \n",argv[0]);
        exit(1);
    }
    
    if ((he=gethostbyname(argv[1]))==NULL){ // calls gethostbyname()
        printf("gethostbyname() error\n");
        exit(1);
    }
    
    
    if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1){ // calls socket()
        printf("socket() error\n");
        exit(1);
    }
    
    /* �O��ͨӍ��ʽ���V����������ʽ���͵�һ��ӍϢ���W·���������C�������յ� */
    yes = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
    
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT); /* htons() is needed again */
    server.sin_addr = *((struct in_addr *)he->h_addr); /*he->h_addr passes "*he"'s info to "h_addr" */
    
    socklen_t len;
    len=sizeof(struct sockaddr_in);
    while (1) {
        printf("input message:");
        fgets(sendbuf,40,stdin);
        sendto(fd,sendbuf,strlen(sendbuf),0,(struct sockaddr *)&server,len);
        if ((numbytes=recvfrom(fd,recvbuf,MAXDATASIZE,0,(struct sockaddr *)&server,&len)) == -1){ /* calls recvfrom() */
            printf("recvfrom() error\n");
            exit(1);
        }
        recvbuf[numbytes]='\0';
        
        
    }
    
    close(fd); /* close fd */
}
