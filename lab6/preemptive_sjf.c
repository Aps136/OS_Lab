#include <stdio.h>
#include <unistd.h>
struct P{
	int pid,at,bt,ct,rt,tat,wt;
};
int shortest(struct P p[], int n, int time){
	int shortestidx=-1;
	int minrt=100000;
	for(int i=0;i<n;i++){
		if(p[i].at <=time && p[i].rt>0){
			if(p[i].rt<minrt){
				minrt=p[i].rt;
				shortestidx=i;
			}
		}
	}return shortestidx;
}

int main(){
	int n;
	printf("enter n of p: \n");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].pid=i+1;
		printf("enter at and bt\n");
		scanf("%d %d", &p[i].at, &p[i].bt);
		p[i].rt= p[i].bt;
	}
	int completed=0;
	int current_t=0;
	float tot_tat=0, tot_wt=0;
	while(completed<n){
		int shortestidx = shortest(p, n, current_t);
		if(shortestidx==-1){
			current_t++;
		}else{
			p[shortestidx].rt--;
			current_t++;
			if(p[shortestidx].rt==0){
				completed++;
				p[shortestidx].ct=current_t;
				p[shortestidx].tat=p[shortestidx].ct-p[shortestidx].at;
				p[shortestidx].wt=p[shortestidx].tat-p[shortestidx].bt;
				tot_tat+=p[shortestidx].tat;
				tot_wt+=p[shortestidx].wt;
			}
		}
	}
	 printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	 for (int i = 0; i < n; i++) {
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
	    }

	 printf("\nAverage Turnaround Time = %.2f\n", tot_tat / n);
	 printf("Average Waiting Time = %.2f\n", tot_wt / n);

	 return 0;
	
	

}
