#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if (argc != 2)
		err(1,"Args");
	
	//if (mkfifo("/tmp/kiunec", 0666) < 0)
	//	err(1,"Fifo");

	int fifo = open("/tmp/kiunec", O_RDONLY);
	if (fifo < 0)
		err(1,"open fifo");

	int fd[2];
	if(pipe(fd) < 0)
		return -1;
	pid_t pid = fork();

	if (pid < 0)
		return -1;
	if(pid == 0)
	{
		dup2(fd[0], 0);
		
		close(fd[0]);
		close(fd[1]);

		execl(argv[1], argv[1], 0);
	}
	char c;
	while(read(fifo,&c,1) > 0)
		write(fd[1],&c,1);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid,0,0);	
}
