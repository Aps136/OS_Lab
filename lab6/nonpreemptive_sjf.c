#include <stdio.h>
struct P{
	int pid, at, bt, wt, tat, ct;
	int completed;
};
int main(){
	//non preemptive sjf
	int n;
	printf("enter number of processes: ");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].pid=i+1;
		printf("enter arrival and burst time\n");
		scanf("%d%d",&p[i].at, &p[i].bt);
		p[i].completed=0;
	}
	int time=0, completed=0;
	float totalTAT=0, totalWT=0;
	while(completed<n){
		int idx =-1;
		int minbt = 10000;
		for(int i=0;i<n;i++){
			if(!p[i].completed && p[i].at<=time){
				if(p[i].bt<minbt){
					minbt=p[i].bt;
					idx=i;
				}
			}
		}
	
	if(idx==-1){
		time++;
	}
	else{
		time+=p[idx].bt;
		p[idx].ct=time;
		p[idx].tat=p[idx].ct-p[idx].at;
		p[idx].wt=p[idx].tat-p[idx].bt;
		totalTAT+=p[idx].tat;
		totalWT+=p[idx].wt;
		p[idx].completed=1;
		completed++;		
	}
	}
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
		}
	printf("\nAverage TAT = %.2f", totalTAT / n);
    	printf("\nAverage WT = %.2f\n", totalWT / n);

    return 0;
}
