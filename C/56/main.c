#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAGIC 5000*4

int comp(const void * a, const void * b){
	return *(uint32_t*)a < *(uint32_t*)b;
}

int main(void){
char inp[] = "input";
//check
int in = open(inp, O_RDONLY);
//check
struct stat s;
int tmp = open("tmp.tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, S_IRUSR | S_IWUSR);
fstat(in, &s);
int bufsize = s.st_size > MAGIC ? MAGIC : s.st_size;
uint32_t* buf = (uint32_t*)malloc(bufsize);
lseek(in, 0, SEEK_SET);
if(read(in, buf, bufsize) > 0){
	qsort(buf,bufsize/4, 4, comp);
}

if(bufsize == MAGIC){
	write(tmp, buf, bufsize);
	int red = read(in, buf, bufsize);
	if (red > 0){
          qsort(buf,bufsize/4, 4, comp);
	}
	int bi = 0;
	fstat(tmp, &s);
	lseek(tmp, 0, SEEK_SET);
	while(bi < red || lseek(tmp, 0, SEEK_CUR) < s.st_size){
		uint32_t toshow;
		uint32_t redfromtmp;
		if (read(tmp, &redfromtmp, 4) <= 0)
			break;

		if(buf[bi] < redfromtmp){
			toshow = buf[bi];
			bi++;
		}else{
			toshow = redfromtmp;
			read(tmp, &redfromtmp, 4);
		}
		printf("%d ", toshow);
	}
}

free(buf);
close(tmp);
close(in);
}
