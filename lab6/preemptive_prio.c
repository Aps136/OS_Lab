#include <stdio.h>

struct Process {
    int id, at, bt, rt, priority, wt, tat;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for(int i=0;i<n;i++){
        p[i].id = i+1;
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for P%d (lower number = higher priority): ", i+1);
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt; // remaining time
        p[i].wt = 0;
        p[i].tat = 0;
    }

    int time = 0, completed = 0;

    while(completed < n){
        int idx = -1;
        int highestPriority = 1e9;

        // Find process with highest priority that has arrived and not completed
        for(int i=0;i<n;i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].priority < highestPriority){
                highestPriority = p[i].priority;
                idx = i;
            }
        }

        if(idx != -1){
            // Execute process for 1 unit (preemptive)
            p[idx].rt--;
            time++;

            // If process finishes
            if(p[idx].rt == 0){
                completed++;
                p[idx].tat = time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            time++; // idle time
        }
    }

    // Print results
    printf("\nP\tAT\tBT\tPriority\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    return 0;
}
