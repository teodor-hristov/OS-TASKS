#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int member(char* arr, int sz,char c) {
	if (!arr)
		return -1;
	for(int i = 0; i < sz; i++){
		if (arr[i] == c)
			return i;
	}

	return -1;
}


int main(int argc, char* argv[]){
	char c[2] = {0};
	char prev = 0;
	if (argc <= 2){
		return -1;
	} 
	char* set1 = argv[2];
	if (strcmp(argv[1],"-d") == 0){
		while(read(0,c,1) > 0){
			if (member(set1, strlen(set1), c[0]) < 0)
				printf("%c", c[0]);
		}
	} else if (strcmp(argv[1],"-s") == 0){
		while(read(0, c, 1)>0){
		if (member(set1, strlen(set1), c[0]) < 0)
		{
			printf("%c", c[0]);
                }
		else if (prev != c[0] && member(set1, strlen(set1), c[0]) >= 0)
		{
			printf("%c", c[0]);
		}
		prev = c[0];
		}
	} else{
		//replace
	}	
	
return 0;
}
