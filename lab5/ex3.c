#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void bubblesort(char arr[][15], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char temp[15];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}
void selectionsort(char arr[][15], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[minIndex]) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            char temp[15];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[minIndex]);
            strcpy(arr[minIndex], temp);
        }
    }
}
int main(){
	int n;
	printf("Enter n val: ");
	scanf("%d", &n);
	getchar();
	char strr[n][15];
	printf("ENter strings: \n");
	for(int i=0;i<n;i++){
		fgets(strr[i],sizeof(strr[i]),stdin);
		strr[i][strcspn(strr[i],"\n")]='\0';
	}
	pid_t pid = fork();
	if(pid==0){
		bubblesort(strr, n);
		printf("Bubble sort: \n");
		for(int i=0;i<n;i++){
			printf("%s\n", strr[i]);
		}
		exit(0);
	}
	pid_t pid1 =fork();
	if(pid1==0){
		selectionsort(strr,n);
		for(int i=0;i<n;i++){
			printf("%s\n",strr[i]);
		}
		exit(0);
	}
	int status;
	pid_t finished = wait(&status);
	printf("\nParent: child process with PID : %d has finished\n",finished);
	return 0;
	
	
}
