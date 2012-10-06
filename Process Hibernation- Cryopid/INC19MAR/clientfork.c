#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 50
#define PORT 3450

int main() 
{
  	int s,r,a=65;
  	int rtn;
  	struct sockaddr_in addr;
	ssize_t len;
	char buff[BUF_SIZE];
	 
	puts("Entering program");

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == -1) 
	{
	    perror("Failed to get socket");
	    exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY;
	addr.sin_port = htons(PORT);
	
	rtn = connect(s, (struct sockaddr * )&addr, sizeof(addr) );

	if (rtn == -1) 
	{
	    perror("Failed to connect to server");
	    exit(EXIT_FAILURE);
	}

	printf("connected to the server\n");
	
	//execve("./a.out",NULL,NULL);
		
	while(1)
	{
		/*fprintf(stderr,"\nEnter Data: ");		
		fflush(stdout);
		fflush(stdin);		
		gets(buff);*/
		fprintf(stderr,"%c",a);
		buff[0]=a++;
		buff[1]='\0';
		len=send(s,buff,BUF_SIZE,MSG_OOB);
		sleep(5);
		//printf("Descriptor:%d",s);		
		/*printf("Hi	%d",getpid());
		fflush(stdout);
		fflush(stdin);
    
		if (fgets(buff, BUF_SIZE, stdin) == NULL)
		{
    			  //fprintf(stderr, "Failed to read input\n");
   			  //exit(EXIT_FAILURE);
   		}
    
		len = write(s, buff, strlen(buff));*/
	}
}

