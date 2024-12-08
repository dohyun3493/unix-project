#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#define MAX_SIZE 100
#define DEFAULT_PROTOCOL 0

struct locker{
	int password;
	int check;
	char condition[MAX_SIZE];
};

readLine(int fd, char* str){
	int n;
	do{
		n = read(fd, str, 1);
 	}while(n > 0 && *str++ != NULL);
 		return(n > 0);
}

int main(){
	int listenfd, connfd, clientlen, n, insert_password;
	int check = 0;
	struct locker *ptr;
	struct sockaddr_un serverUNIXaddr, clientUNIXaddr;
	char message[MAX_SIZE], send[MAX_SIZE], send2[MAX_SIZE], insert[MAX_SIZE], last[MAX_SIZE];

	srand(time(NULL));
	n =  10;
	ptr = (struct locker *)malloc(n*sizeof(struct locker));

	for(int i = 1; i <= n; i++){
		ptr[i].check = 0;
		strcpy(ptr[i].condition, "empty");
	}


	signal(SIGCHLD, SIG_IGN);
	clientlen = sizeof(clientUNIXaddr);

	listenfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverUNIXaddr.sun_family = AF_UNIX;
	strcpy(serverUNIXaddr.sun_path, "convert");
	unlink("convert");
	bind(listenfd, &serverUNIXaddr, sizeof(serverUNIXaddr));

	listen(listenfd, 5);

	while(1){
		connfd = accept(listenfd, &clientUNIXaddr, &clientlen);

		if(fork() == 0){
			int x, y;
			
			sprintf(message, "%d", n);
			write(connfd, message, strlen(message) + 1);

			while(1){
				readLine(connfd, send);
				x = atoi(send);
				printf("first check : %d\n", x);
				
				if(ptr[x].check == 0){
					readLine(connfd, send2);
					y = atoi(send2);
					ptr[x].password = y;
					strcpy(ptr[x].condition, "occupied");
					ptr[x].check = 1;
					printf("locker: %d password: %d condition: %s\n", x, ptr[x].password, ptr[x].condition);
				}
				else{
					readLine(connfd, insert);
					insert_password = atoi(insert);
					if(ptr[x].password == insert_password){
						printf("Do you want to unlock this locker? (Y/N) \n");
						strcpy(last, "Do you want to unlock this locker? (Y/N) \n");
						printf("%s\n", last);
						write(connfd, last, strlen(last) + 1);
					}
					else{
						printf("Wrong\n");
						strcpy(last, "Wrong\n");
						printf("%s\n" ,last);
						write(connfd, last, strlen(last) + 1);
					}			
				}	
			}
		}
	}
}