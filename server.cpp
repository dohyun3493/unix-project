#include stdio.h
#include signal.h
#include systypes.h
#include syssocket.h
#include sysun.h
#define MAX_SIZE 100
#define DEFAULT_PROTOCOL 0

struct locker{
	int password;
	int check;
	char condition[MAX_SIZE];
};

readLine(int fd, char str){
	int n;
	do{
		n = read(fd, str, 1);
 	}while(n  0 && str++ != NULL);
 		return(n  0);
}

int main(){
	int clientfd, lockerx, result, n, password, insert_password;
	struct sockaddr_un serverUNIXaddr;
	struct locker ptr;
	char condition[MAX_SIZE], message[MAX_SIZE], send[MAX_SIZE], send2[MAX_SIZE], insert[MAX_SIZE], last[MAX_SIZE];

	clientfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverUNIXaddr.sun_family = AF_UNIX;
	strcpy(serverUNIXaddr.sun_path, convert);

	do{
		result = connect(clientfd, &serverUNIXaddr, sizeof(serverUNIXaddr));
		if(result == - 1)sleep(1);
	}while(result == - 1);

	readLine(clientfd, message);
	n = atoi(message);

	ptr = (struct locker )malloc(nsizeof(struct locker));

	printf(current locker staten);


	for(int i = 1; i  n; i++){
		strcpy(ptr[i].condition, empty);
		ptr[i].check = 0;
		printf(%d %s , i, ptr[i].condition);
		if(i == n - 1) printf(n);
	}

	while(1){
		printf(set locker );
		scanf(%d, &lockerx);
		sprintf(send, %d, lockerx);
		write(clientfd, send, strlen(send) + 1);
	
		if(ptr[lockerx].check == 0){
			printf(set password );
			scanf(%d, &password);
			sprintf(send2, %d, password);
			write(clientfd, send2, strlen(send2) + 1);
			
			ptr[lockerx].check = 1;
			strcpy(ptr[lockerx].condition, occupied);
			printf(setn);
		}
		else{
			printf(insert password );
			scanf(%d, &insert_password);
			sprintf(insert, %d, insert_password);
			write(clientfd, insert, strlen(insert) + 1);
			
			readLine(clientfd, last);
			printf(%sn, last);
		}

		printf(current locker staten);

		for(int i = 1; i  n; i++){
			printf(%d %s , i, ptr[i].condition);
			if(i == n - 1) printf(n);
		}
	}
}
