#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <err.h>
#include <pwd.h>

int main(void){
	char commandLine[256];
	scanf("%s", commandLine);
	
	char* username = getpwuid(getuid())->pw_name; 	
	char time[] = "nekarechem che she go napraim";

	printf("%s %s %s\n", username, commandLine, time);

	pid_t pid = fork();
	if (pid < 0)
		err(1,"fork");
	if (pid == 0){
		execlp("echo", "echo", "-e", "block usr");
	}

	int fd[2];
        if (pipe(fd) < 0)
                err(1,"pipe");

	pid_t pid1 = fork();
	if (pid1 < 0)
		err(2,"fork1");

	if (pid1 == 0){
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		
		execlp("awk", "awk", "-F", ":", "{print $7}", "/etc/passwd", 0);
	}

	close(fd[1]);
	dup2(fd[0],0);
	close(fd[0]);
	
	waitpid(pid,0,0);
	waitpid(pid1,0,0);
	execlp("xargs", "xargs", "echo", 0);
}
