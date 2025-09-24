#include <stdio.h>
struct P{
	int id,at,bt,wt,tat
};
int main(){
	int n;
	printf("ENter number of processes\n");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].id=i+1;
		printf("ENter at: ");
		scanf("%d", &p[i].at);
		printf("ENter BT: ");
		scanf("%d", &p[i].bt);
		p[i].wt=0;
		p[i].tat=0;
	}
	int time=0, completed=0;
	int iscompleted[n];
	for(int i=0;i<n;i++) iscompleted[i]=0;
	while(completed<n){
		int idx=-1;
		int minbt=10000;
		for(int i=0;i<n;i++){
			if(!iscompleted[i] && p[i].at<=time && p[i].bt<minbt){
				minbt=p[i].bt;
				idx=i;
			}
		}
		if(idx!=-1){
			p[idx].wt=time -p[idx].at;
			time+=p[idx].bt;
			p[idx].tat=p[idx].bt+p[idx].wt;
			iscompleted[idx]=1;
			completed++;
		}else{
			time++;
		}
	}
	printf("\nP\tAT\tBT\tWT\tTAT\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].wt,p[i].tat);
	}
	return 0;
}
