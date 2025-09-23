#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int bt[n], wt[n], tat[n];  
    float avgWT = 0, avgTAT = 0;
    printf("Enter burst times for %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Display table
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    // Averages
    printf("\nAverage Waiting Time = %.2f", avgWT/n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT/n);

    return 0;
}
