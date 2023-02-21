#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC 2000
void mkinp(){
	int fd = open("input", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	for (uint32_t i = 4000; i > 0; i--){
		write(fd, &i, sizeof(i));
	}
	close(fd);
}

void merge(int fd, uint32_t* buf, int outfd){
	uint32_t n,idx = 0;
	int written,red;
	lseek(fd, 0, SEEK_SET);
	red =  read(fd,&n,sizeof(n));
	while(idx < MAGIC || red > 0){
		if (idx < MAGIC && (buf[idx] < n || red <= 0)){
			written = write(outfd, &buf[idx], sizeof(uint32_t));
			//check
			idx++;
		}else {
			written = write(outfd, &n, sizeof(uint32_t));
			red =  read(fd,&n,sizeof(n));
		}
	}	
}

int comp(const void* a, const void* b){
	if( *(uint32_t*)a < *(uint32_t*)b){
		return -1;
	}else if( *(uint32_t*)a > *(uint32_t*)b){
		return 1;
	}else return 0;
}

int main(void){
mkinp();
char inp[] = "input";
char outf[] = "output";
char tmpf[] = "tmp.tmp";
int in,out,tmp;
in = open(inp, O_RDONLY);
out = open(outf, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
tmp = open(tmpf, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
//check
uint32_t* buf = (uint32_t*)malloc(MAGIC*sizeof(uint32_t));
//check
int red = read(in, buf, MAGIC*sizeof(uint32_t));
if (red <= 0)
	return -1;

qsort(buf, MAGIC, sizeof(uint32_t), comp);
int written = write(tmp, buf, MAGIC*sizeof(uint32_t));
if (written <= 0)
	return -1;

memset(buf, 0, MAGIC*sizeof(uint32_t));
red = read(in, buf, MAGIC*sizeof(uint32_t));
qsort(buf, MAGIC, sizeof(uint32_t), comp);
if (red <= 0)
        return -1;

merge(tmp, buf, out);

}
