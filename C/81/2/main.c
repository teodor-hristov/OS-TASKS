#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	
	mkfifo("/tmp/kiunec", 0666);
	int fd = open(argv[1], O_RDONLY);
	int fifo = open("/tmp/kiunec", O_RDWR);
	char c;
	while(read(fd,&c,1) > 0)
		write(fifo, &c, 1);	
	close(fifo);	
	close(fd);
}
