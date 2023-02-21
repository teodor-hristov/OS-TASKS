#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
	int fd[2];
	
	if (pipe(fd) < 0)
		return -1;

	pid_t pid1 = fork();
	if (pid1 < 0)
		return -1;

	if (pid1 == 0){
		dup2(fd[1],1);
		close(fd[1]);
		close(fd[0]);

		execlp("cat", "cat", argv[1], 0);
		
	}


	pid_t pid2 = fork();
	if (pid2 < 0)
		return -1;

	if(pid2 == 0){
		dup2(fd[0],0);
		close(fd[0]);
		close(fd[1]);

		execlp("sort", "sort", 0);
	}
	
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}
