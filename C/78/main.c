#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
bool getmax2args(char args[2][5]);
bool getmax2args(char args[2][5]){
        char c;
	memset(args, 0, 10);
        int cnt = 0, idx = 0;
        while (cnt < 2 && read(0, &c, 1) > 0){
		if (c == '\n' || c == ' '){
			cnt++;
			idx=0;
		}else{
			args[cnt][idx] = c;
			idx++;
		}
        }

	return cnt + idx != 0;
}

int main(int argc, char* argv[]){
	char command[5] = "echo";
	if (argc == 2){
		memset(command,0,sizeof(command));
		memcpy(command, argv[1], 4);
	}

	char arguments[2][5];
	while(getmax2args(arguments)){	
		pid_t pid = fork();
        	if (pid < 0)
                	return -1;

		if (pid == 0){
			//child
			execlp(command, command, arguments[0], arguments[1]);

		}
		waitpid(pid,0,0);
	}
	
}
