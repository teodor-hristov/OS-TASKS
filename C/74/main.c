#include <error.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct dataHeader{
	uint32_t magic;
	uint32_t count;
};

struct comparatorHeader{
	uint32_t magic1;
	uint16_t magic2;
	uint16_t reserved;
	uint64_t count;
};

struct comparatorItem{
	uint16_t type;
	uint16_t reserved[3];
	uint32_t offset1;
	uint32_t offset2;
};

void mkcomparator(){
int fd = open("comparator", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
struct comparatorHeader ch;
ch.magic1 = 0xAFBC7A37;
ch.magic2 = 0x1C27;
ch.count = 2;
write(fd, &ch, sizeof(ch));
struct comparatorItem ci;
ci.type = 0;
ci.offset1 = 1;
ci.offset2 = 2;
write(fd, &ci, sizeof(ci));

ci.type = 1;
ci.offset1 = 1;
ci.offset2 = 1;
write(fd, &ci, sizeof(ci));

close(fd);
}

void mkdata(){
int fd = open("data", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
struct dataHeader dh;
dh.magic = 0x21796F4A;
dh.count = 2;
write(fd, &dh, sizeof(dh));
uint64_t d = 234;
write(fd,&d,sizeof(d));
d = 499;
write(fd,&d,sizeof(d));
close(fd);
}

void swapContents(int fd, struct comparatorItem ci, uint64_t rhs, uint64_t lhs){
	struct comparatorHeader ch;
	lseek(fd, ci.offset1*sizeof(rhs), SEEK_SET);
	write(fd, &rhs, sizeof(rhs));

	lseek(fd, ci.offset2*sizeof(lhs), SEEK_SET);
        write(fd, &lhs, sizeof(lhs));
}

int main(int argc, char* argv[]){
mkcomparator();
mkdata();
if (argc != 3)
	error(-1,1,"Invalid args");

char* data = argv[1];
char* comparator = argv[2];
int datafd, compfd;

datafd = open(data, O_RDWR);
if (datafd < 0)
	error(-1, 1, "File open failed!");

compfd = open(comparator, O_RDWR);
if (compfd < 0)
	error(-1, 1, "File open failed!");

struct dataHeader dh;
struct comparatorHeader ch;
struct comparatorItem ci;

if (read(datafd, &dh, sizeof(dh)) <= 0)
	error(-1, 1, "Read datafd failed!");

if (dh.magic != 0x21796F4A)
	error(-1, 1, "Invalid2 file!");

if (read(compfd, &ch, sizeof(ch)) <= 0)
        error(-1, 1, "Read ch failed!");

if (ch.magic1 != 0xAFBC7A37 || ch.magic2 != 0x1C27)
        error(-1, 1, "Invalid1 file!");

while(read(compfd, &ci, sizeof(ci)) > 0){
	uint64_t lhs, rhs;
	if (ci.offset1 > dh.count || lseek(datafd, ci.offset1*sizeof(lhs), SEEK_SET) < 0)
		error(-1, 1, "lseek failed");
	if (read(datafd, &lhs, sizeof(lhs)) <= 0)
		error(-1, 1, "Read lhs failed!");

	if (ci.offset2 > dh.count || lseek(datafd, ci.offset2*sizeof(rhs), SEEK_SET) < 0)
                error(-1, 1, "lseek failed");
        if (read(datafd, &rhs, sizeof(rhs)) <= 0)
                error(-1, 1, "Read rhs failed!");

	switch(ci.type){
	case 0:
		if (lhs < rhs)
			//printf("%d %d %d\n", lhs,rhs,ci.type);
			swapContents(datafd, ci, rhs,lhs);
	break;
	case 1:
		if (lhs > rhs)
			printf("%d %d %d\n", lhs,rhs, ci.type);
			//	swapContents(datafd, ci, rhs,lhs);
	break;
	default:
	 error(-1, 1, "Read failed!");
	}

}
}
