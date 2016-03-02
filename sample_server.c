/* 
 * File:   mainFile.c
 * Author: Karthik Vasisht
 *
 * Created on 26 February 2016, 21:30
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
  //  int numrv;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);  //socket creation, waiting for request

    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET; //socket family
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //udp socket created
    serv_addr.sin_port = htons(5000); //port no assigned

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));  //assign job to socket, 

    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }


    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // child process created, 

        /* Open the file that we wish to transfer */
        //FILE *fp = fopen("sample_text.txt","rb");
	FILE *fp =  fopen("dennis_ritchie.jpeg", "rb");        
	if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   

        /* Read data from file and send it */
        while(1)  //reading from a file requested by client
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread); //writing into into buffer
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }
	//system("service network-manager restart");
        close(connfd);
        sleep(1);
    }


    return 0;
}
