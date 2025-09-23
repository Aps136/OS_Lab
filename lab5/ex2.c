#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sorts(int count, char *arr[]){
	char *temp;
	for(int i=0;i<count-1;i++){
		for(int j=i+1;j<count;j++){
			if(strcmp(arr[i],arr[j])>0){
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			}
		}
	}
}
int main(int argc, char *argv[]){
	if(argc<2){
		return 1;
	}
	pid_t pid = fork();
	if(pid<0){
		perror("FOrk failed");
		return 1;
	}
	if(pid==0){
		char *strings[argc-1];
		for(int i=1;i<argc;i++){
			strings[i-1]=argv[i];
		}
		sorts(argc-1,strings);
		for(int i=0;i<argc-1;i++){
			printf("%s\n", strings[i]);
		}exit(0);
	}else{
		wait(NULL);
		for(int i=1;i<argc;i++){
			printf("%s\n",argv[i]);
		}
	}return 0;
	
	
}
