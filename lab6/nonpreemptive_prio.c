#include <stdio.h>
struct P{
	int pid, at, bt, wt,tat, prio;
};
int main(){
	int n;
	printf("ENter n: ");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].pid=i+1;
		printf("ENter at:");
		scanf("%d", &p[i].at);
		printf("ENter bt:");
		scanf("%d", &p[i].bt);
		printf("ENter prio:");
		scanf("%d", &p[i].prio);
		p[i].wt=0;
		p[i].tat=0;	
	}
	int time=0, done=0;
	int iscompleted[n];
	for(int i=0;i<n;i++) iscompleted[i]=0;
	int gi[100], gs[100], ge[100], gidx=0;
	while(done<n){
		int idx=-1;
		int highp=10000;
		for(int i=0;i<n;i++){
			if(!iscompleted[i] && p[i].at<=time && p[i].prio< highp){
				highp=p[i].prio;
				idx=i;
			}
		}
		if(idx!=-1){
			int start=time;
			p[idx].wt= time - p[idx].at;
			time+=p[idx].bt;
			p[idx].tat=p[idx].wt+p[idx].bt;
			iscompleted[idx]=1;
			done++;
			gi[gidx]=p[idx].pid;
			gs[gidx]=start;
			ge[gidx]=time;
			gidx++;
		}else{
			time++;
		}
	}
	printf("\nP\tAT\tBT\tPrio\tWT\tTAT\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].prio, p[i].wt, p[i].tat);
	}
	printf("\nGantt Chart:\n");
	for(int i=0;i<gidx;i++){
		printf("P%d: %d-%d", gi[i], gs[i], ge[i]);
		if(i != gidx-1) printf(", ");
	}
	printf("\n");
	return 0;	
	
}
