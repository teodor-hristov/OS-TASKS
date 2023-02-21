#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <err.h>
#include <string.h>

struct dataStruct {
	char name[8];
	uint32_t offset;
	uint32_t length;
};

void mkinp(){
	struct dataStruct ds;
	int fd = open("input", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	memcpy(ds.name,"input",5);
	for(int i = 0; i < 10; i++){
		ds.offset = i + 1;
		ds.length=100;
		write(fd,&ds, sizeof(ds));
	}
}

int main(int argc, char* argv[]){
	mkinp();
	if (argc != 2)
		err(1,"args");

	int file = open(argv[1], O_RDONLY);
	if (file < 0)
		err(1, "file open failed");
	
	struct dataStruct ds;
	int fd[2];
	int cnt = 0;
	
	if(pipe(fd) < 0)
		err(1,"pipe");
	
	pid_t pid[8];
	while(read(file, &ds, sizeof(ds)) > 0){
		pid[cnt] = fork();
	       if (pid[cnt] < 0){}

		if (pid[cnt] == 0){
			close(fd[0]);
			int subfile = open(ds.name, O_RDONLY);
			lseek(subfile, ds.offset*sizeof(uint16_t), SEEK_SET);
			uint16_t el;
			read(subfile, &el, sizeof(uint16_t));
			printf("siene: %d %d\n", getpid(), el);
			write(fd[1], &el, sizeof(el));
			close(fd[1]);
			close(subfile);
			return 0;	
		}
	       cnt++;
			       
	}
	uint16_t data;
	close(fd[1]);
	uint16_t res;
	while(read(fd[0], &data, sizeof(data)) > 0){
		if (!res)
			res = data;
		else
			res ^=data;
	}
	close(fd[0]);
	printf("%d %d\n", getpid(), res);

}
