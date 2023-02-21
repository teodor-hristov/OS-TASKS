#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>

int comp(const void* a, const void * b){
        return *(uint8_t*)a < *(uint8_t*)b;
}

int main(void){
        char fn[] = "testfile";
        int fd = open(fn, O_RDONLY);

        struct stat file;
        fstat(fd, &file);
        uint8_t* buf = (uint8_t*)malloc(file.st_size);


        while(read(fd, buf, sizeof(buf)) > 0)
                qsort(buf, sizeof(buf), sizeof(uint8_t), comp);

        close(fd);

        printf("%s", buf);
}
