#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 4 || argc > 4)
		return -1;

	int rst = atoi(argv[1]);
	char* prog = argv[2];
	char* params = argv[3];
	
	time_t start = 0, end = 0;

	pid_t pid; 
	int stat = 0;
	int fd[2];
	
	if (pipe(fd) < 0)
		return -1;

	while(stat == 0 && end - start <= rst){
		pid = fork();
		if (pid < 0)
			return -1;

		if (pid == 0){
			//child Q
			close(fd[0]);
			start = time(NULL);
			if(write(fd[1], &start, sizeof(time_t)) < 0)
				return -1;
			close(fd[1]);
			execlp(prog, prog, params);
		}

		close(fd[1]);
		if (waitpid(pid, &stat, 0) < 0)
			return -1;
		if (read(fd[0], &start, sizeof(end)) < 0)
			break;

		end = time(NULL);
		printf("%ld %ld %d\n", start,end,stat);
	}

	close(fd[0]);
}
