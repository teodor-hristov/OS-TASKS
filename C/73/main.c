#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

struct __attribute__((packed)) header{
uint16_t magic;  //0x5A4D
uint16_t filetype;
uint32_t count;
};

void mkinplst(){
	struct header h{0x5a4d, 1,2};
	int fd = open("list.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	uint16_t d;
	d = 2;
	write(fd, &d, sizeof(d));
	d = 10;
	write(fd, &d, sizeof(d));
	close(fd);
}


void mkinpdata(){
        struct header h{0x5a4d, 2, 3};
        int fd = open("data.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        uint32_t d;
        d = 13;
        write(fd, &d, sizeof(d));
        d = 23;
        write(fd, &d, sizeof(d));
        d = 123;
        write(fd, &d, sizeof(d));

	close(fd);
}

int main(int argc, char* argv[]){
	if (argc != 4)
		return -1;
char* list = argv[1];
char* data = argv[2];
char* out = argv[3];

int fdlist,fddata,fdout;
fdlist = open(list, O_RDONLY);
fddata = open(data, O_RDONLY);
fdout = open(out, O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
//check

struct header h;
int red = read(fdlist, &h, sizeof(h));
//check header for all files
uint16_t value;
off_t offs;
uint32_t d;
uint64_t o;

struct header outh;
write(fdout, &outh, sizeof(outh));//check

red = read(fdlist, &value, sizeof(value));
while(red > 0)
{
	offs = lseek(fdlist, 0, SEEK_CUR);
	lseek(fddata, offs, SEEK_SET);//check
	if (read(fddata, &d, sizeof(d)) <= 0)
		break;

	off_t allelements = lseek(fdout, 0, SEEK_END);
	if (allelements < value){
		write(fdout, 0, (sizeof(uint64_t))*(allelements - value));//check
	}
	lseek(fdout, value, SEEK_SET);
	
	o = d;
	if (write(fdout, &o, sizeof(o)) <= 0)
		break;

	red = read(fdlist, &value, sizeof(value));
}	
}
