#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int main(void) {
	char cmd[128] = {};
	pid_t pid1;

	scanf("%s",cmd);
	if (pid1 < 0)
		err(-1,0,"Fork");

	while(strcmp(cmd, "exit") != 0){
		pid1 = fork();
		if (pid1 == 0){
			execlp(cmd,cmd,0);
		}

		waitpid(pid1,0,0);
		scanf("%s",cmd);
	}
}

