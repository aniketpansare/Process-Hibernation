#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 50

struct sockaddr_in addr;
int incoming_s;
socklen_t incoming_len;
static int PORT=3450;

int main(int argc,char * argv[]) 
{
	  int s,i,a;
	  int rtn;
	  ssize_t len; 	
	  
	  
	  char buff[BUF_SIZE];
	  

	  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	  if (s == -1) 
	  {
	    	perror("Failed to get socket in serverfork1");
	    	exit(EXIT_FAILURE);
	  }

	  addr.sin_family = AF_INET;
	  addr.sin_addr.s_addr = INADDR_ANY;
	  addr.sin_port = htons(PORT);

	  rtn = bind(s, (struct sockaddr*)&addr, sizeof(addr));

	  if (rtn == -1) 
	  {
	    	perror("Failed to get socket in serverfork");
	    	exit(EXIT_FAILURE);
	  }

	  printf("\ni am listening in serverfork");
	  rtn = listen(s, 10);

	  if (rtn == -1) 
	  {
	    	perror("Failed to listen on socket in serverfork");
	    	exit(EXIT_FAILURE);
	  }

	  
	  while(1)
	  {
	  	incoming_len = sizeof(addr);
	  	memset(&addr, 0, sizeof(addr));

	  	incoming_s = accept(s, (struct sockaddr *)&addr, &incoming_len);

	  	if (incoming_s == -1) 
		{
	    		perror("Failed to accept incoming connection in serverfork");
	    		exit(EXIT_FAILURE);
	  	}

	  	printf("\nAccepted incoming connection in serverfork\n");
	
		if (!fork())
		{
			fprintf(stderr,"%d\n",getpid());			
			while(1)
			{
				//printf("Descriptor:%d",incoming_s);				
				len=recvfrom(incoming_s,buff,BUF_SIZE,MSG_WAITALL,(struct sockaddr *)&addr, &incoming_len);				
				/*len = read(incoming_s, buff, BUF_SIZE);*/
				/*if (len < 0) 
				{
	      				fprintf(stderr, "Failed to read network data\n");
					sleep(10);
					break;
	    			}	
	    			else if (len == 0) 
				{
	      				fprintf(stderr, "No response data read\n");
					break;
				}*/
	    	   		if(len>0)
				{
					buff[len] = '\0';					
					a=buff[0];
					//fprintf(stderr,"%d",a);
					a=a+32;
					//fprintf(stderr,"%d",a);
					buff[0]=a;	     				
					buff[len] = '\0';
	     				printf("client says : %s\n", buff);
				}
				len=0;
			}
		}
		else
		{

		}
	}
}



