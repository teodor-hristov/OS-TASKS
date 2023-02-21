#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct __attribute__((packed)) uinfo{
	uint32_t uid;
	uint16_t s1;
	uint16_t s2;
	uint32_t t1;
	uint32_t t2;
};

void mkinp(){
	int fd = open("input", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	//check
	struct uinfo tmp;
	for(int i = 0; i < 20; i++){
		tmp.uid = i % 4;
		tmp.t1 = time(NULL);
		tmp.t2 = tmp.t1 + i*20%6;
		write(fd, &tmp, sizeof(tmp));
	}
	close(fd);
}

int main(void){
mkinp();
int fd = open("input", O_RDONLY);
//check
lseek(fd,0,SEEK_SET);
struct stat s;
fstat(fd, &s);
struct uinfo r;
int fileelements = s.st_size / sizeof(r);
int xsr = 0;
while(read(fd, &r, sizeof(r)) > 0){
	xsr += r.t2 - r.t1;	
}
xsr /=fileelements;

lseek(fd,0,SEEK_SET);
uint32_t disp = 0;
while(read(fd, &r, sizeof(r)) > 0){
	disp += ((r.t2 - r.t1) - xsr) * ((r.t2 - r.t1) - xsr);
}
disp/=fileelements;

lseek(fd, 0, SEEK_SET);
while(read(fd, &r, sizeof(r)) > 0){
        if ((r.t2 - r.t1)*(r.t2 - r.t1) > disp){
		printf("%d %d\n", r.uid, (r.t2 - r.t1));
	}
}
}
