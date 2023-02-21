#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <sys/wait.h>

int main(void){
	int fd[2];
	if (pipe(fd) < 0)
		return -1;

	off_t pid1 = fork();
	if (pid1 < 0)
		return -1;

	if (pid1 == 0){
		//child awk
		dup2(fd[1],1);
		close(fd[1]);
		close(fd[0]);

		execlp("awk", "awk", "-F", ":", "{print $7}", "/etc/passwd", NULL);
	}

	int fd2[2];
	pipe(fd2);

	off_t pid2 = fork();
	if (pid2 < 0)
		return -1;
	if (pid2 == 0){
		//child sort
		dup2(fd[0],0);
		dup2(fd2[1],1);
		
		close(fd[0]);
		close(fd[1]);
		close(fd2[1]);
		close(fd2[0]);

		execlp("sort", "sort", 0);
	}
	
	dup2(fd2[0],0);

	close(fd[1]);
	close(fd[0]);
	close(fd2[1]);
	close(fd2[0]);

	waitpid(pid1,0,0);
	waitpid(pid2,0,0);

	if (execlp("uniq", "uniq", "-c", 0) < 0)
		return -1;
}
