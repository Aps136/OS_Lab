#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("FOrk failed\n");
		return 1;
	}
	else if(pid==0){
		printf("IM the child process\n");
		printf("CHILD PROCESS ID: %d\n",getpid());
		printf("PARENT PROCESS ID: %d\n", getppid());
		
	}else{
		printf("IM the parent process\n");
		printf("Parent process ID :%d\n",getpid());
		printf("child process ID : %d\n", pid);
		
	}return 0;
}
