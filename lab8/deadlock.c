#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;  // Number of processes and resource types
int Available[MAX_RESOURCES];
int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Request[MAX_PROCESSES][MAX_RESOURCES];

bool detectDeadlock() {
    int Work[MAX_RESOURCES];
    bool Finish[MAX_PROCESSES];
    
    // Initialize Work = Available
    for (int i = 0; i < m; i++)
        Work[i] = Available[i];
    
    // Initialize Finish array
    for (int i = 0; i < n; i++) {
        bool allocated = true;
        // If process has no allocation, it can be considered finished
        for (int j = 0; j < m; j++) {
            if (Allocation[i][j] != 0) {
                allocated = false;
                break;
            }
        }
        Finish[i] = allocated;
    }
    
    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (Request[i][j] > Work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);
    
    // Check if there are processes not finished
    bool deadlock = false;
    printf("Processes in deadlock: ");
    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            printf("%d ", i);
            deadlock = true;
        }
    }
    printf("\n");
    
    return deadlock;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    
    printf("Enter Available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }
    
    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d allocated resources: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }
    
    printf("Enter Request matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d requests: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Request[i][j]);
        }
    }
    
    if (detectDeadlock()) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }
    
    return 0;
}
