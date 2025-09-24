#include <stdio.h>
struct P{
	int bt,wt,tat,rt,pid
};
int main(){
	int n,tq;
	int time=0, done=0;
	printf("Enter number of processes: \n");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].pid=i+1;
		printf("enter burst time: ");
		scanf("%d",&p[i].bt);
		p[i].rt=p[i].bt;
		p[i].wt=p[i].tat=0;
	}
	printf("enter tq: ");
	scanf("%d",&tq);
	while(done<n){
		for(int i=0;i<n;i++){
			if(p[i].rt>0){
				if(p[i].rt>tq){
					time+=tq;
					p[i].rt-=tq;
				}else{
					time+=p[i].rt;
					p[i].wt=time-p[i].bt;
					p[i].rt=0;
					done++;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		p[i].tat=p[i].bt+p[i].wt;
		printf("P%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].wt, p[i].tat);
	}
	float totwt=0, totat=0;
	for(int i=0;i<n;i++){
		totwt+=p[i].wt;
		totat+=p[i].tat;
		
	}
	printf("AVGV TOT WT IS: %f", totwt/n);
	printf("AVGV TOT TAT IS: %f", totat/n);
	
	return 0;
}
