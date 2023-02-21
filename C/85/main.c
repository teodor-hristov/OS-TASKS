#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
	if (argc != 3)
		err(2,"args");

	const int N = atoi(argv[1]);
	const int D = atoi(argv[2]);
	
	int fd[2];
	if (pipe(fd) < 0)
		err(2,"pipe");
	pid_t pid = fork();
	if (pid < 0)
		err(1,"fork");
	if (pid == 0){
		close(fd[1]);
	}else{
		close(fd[0]);
	}
	
	for(int i = 0; i < N; i++){
		if (pid == 0){
			char parent[10];
                        read(fd[0], &parent, 5);
		       	if(strcmp(parent, "DING") == 0){
                                printf("DONG\n");
                        }	
		}else {
			sleep(D);
			write(fd[1], "DING", 5);
			printf("DING\n");
		}	
	}
}
