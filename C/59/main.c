#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void catfiles(const char* files[], int filec, bool count){
	printf("%d", filec);
	if (!files)
		return;
	int fd, cnt = 0;
	char c;
	for(int i = 0; i < filec; i++){
		if (strcmp(files[i], "-") != 0){
			fd = open(files[i], O_RDONLY);
			//check
			cnt=0;
			while(read(fd,&c,1) > 0){
				printf("%c",c);
				if (c == '\n' && count){
					printf("%d ", cnt);
					cnt++;
				}
			}

			close(fd);
		}else{
                	while(read(0,&c,1)> 0){
                        	printf("%c",c);
                                if (c == '\n' && count){
                                        printf("%d ", cnt);
					cnt++;
				}
			}	
			cnt=0;
		}
	}
}

int main(int argc, const char* argv[]){
	char inp[4096];
	int red = 0;
	if (argc == 1){
		red = read(0,inp,sizeof(inp));
		while(red > 0){
			printf("%s", inp);
			red = read(0,inp,sizeof(inp));
		}
	}else if (strcmp(argv[1], "-n") == 0) {
		catfiles(&argv[2], argc-2, true);		
	}else{
		catfiles(&argv[1], argc-1, false);		
	}
}
