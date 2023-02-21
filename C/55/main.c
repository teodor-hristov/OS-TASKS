#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>

struct tuple{
uint32_t x;
uint32_t y;
};

int main(void){
char f1[] = "input";
char f2[] = "out";

int fd1,fd2;
fd1 = open(f1, O_RDONLY);
fd2 = open(f2, O_RDWR);
struct tuple r;
while(read(fd1, &r, sizeof(r)) > 0){
	char c;
	printf("%d, %d", r.x, r.y);
	lseek(fd2, r.x, SEEK_SET);
	while(read(fd2,&c,1) > 0 && lseek(fd2, 0, SEEK_CUR)){
		printf("%c", c);
	}
}
}
