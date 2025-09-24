#include <stdio.h>
//round robin
struct P{
	int id,at,bt,wt,tat,rt;
};
int main(){
	int n,tq;
	printf("ENter n: ");
	scanf("%d", &n);
	struct P p[n];
	for(int i=0;i<n;i++){
		p[i].id=i+1;
		printf("ENter at: ");
		scanf("%d", &p[i].at);
		printf("ENter bt: ");
		scanf("%d", &p[i].bt);
		p[i].rt=p[i].bt;
		p[i].wt=0;
		p[i].tat=0;
	}
	printf("ENter tq: ");
	scanf("%d", &tq);
	int time=0, done=0;
	int gnattpid[100], gnatts[100],gnatte[100], gidx=0;
	while(done<n){
		int executed=0;
		for(int i=0;i<n;i++){
			if(p[i].rt>0 && p[i].at<=time){
				executed=1;
				int start=time;
				if(p[i].rt>tq){
					time+=tq;
					p[i].rt-=tq;
				}else{
					time+=p[i].rt;
					p[i].wt=time-p[i].bt-p[i].at;
					p[i].rt=0;
					done++;
				}
				gnattpid[gidx]=p[i].id;
				gnatts[gidx]=start;
				gnatte[gidx]=time;
				gidx++;
			}
		}
		if(!executed) time++;
	}
	for(int i=0;i<n;i++){
		p[i].tat=p[i].bt+p[i].wt;
		printf("P%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt,p[i].wt,p[i].tat);
		
	}
	for(int i=0;i<gidx;i++){
		printf("P%d: %d-%d", gnattpid[i], gnatts[i], gnatte[i]);
		if(i!=gidx-1) printf(", ");
	}printf("\n");
	
	return 0;
	
	
	
}
