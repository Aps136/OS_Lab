#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;  // Number of processes and resources
int Available[MAX_RESOURCES];
int Max[MAX_PROCESSES][MAX_RESOURCES];
int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Need[MAX_PROCESSES][MAX_RESOURCES];

// Function to calculate Need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

// Safety algorithm to check if system is in safe state
bool isSafe() {
    int Work[MAX_RESOURCES];
    bool Finish[MAX_PROCESSES];
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Initialize Work = Available
    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    // Initialize Finish to false for all processes
    for (int i = 0; i < n; i++)
        Finish[i] = false;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int k = 0; k < m; k++)
                        Work[k] += Allocation[i][k];
                    safeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            // No process could be allocated safely
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");

    return true;
}

// Resource-request algorithm
bool requestResources(int processNum, int request[]) {
    printf("Process %d requesting resources: ", processNum);
    for (int i = 0; i < m; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    // Step 1: Check if request <= Need
    for (int i = 0; i < m; i++) {
        if (request[i] > Need[processNum][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Step 2: Check if request <= Available
    for (int i = 0; i < m; i++) {
        if (request[i] > Available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Step 3: Pretend to allocate resources
    for (int i = 0; i < m; i++) {
        Available[i] -= request[i];
        Allocation[processNum][i] += request[i];
        Need[processNum][i] -= request[i];
    }

    // Step 4: Check system safety
    if (isSafe()) {
        printf("Request granted.\n");
        return true;
    } else {
        // Rollback allocation
        for (int i = 0; i < m; i++) {
            Available[i] += request[i];
            Allocation[processNum][i] -= request[i];
            Need[processNum][i] += request[i];
        }
        printf("Request cannot be granted as it leads to unsafe state.\n");
        return false;
    }
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

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d max resources: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d allocated resources: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    calculateNeed();

    if (!isSafe()) {
        printf("System is NOT in a safe state initially.\n");
        return 0;
    }

    while (1) {
        int processNum;
        printf("\nEnter process number to request resources (-1 to exit): ");
        scanf("%d", &processNum);
        if (processNum == -1)
            break;

        int request[MAX_RESOURCES];
        printf("Enter request for each resource:\n");
        for (int i = 0; i < m; i++) {
            scanf("%d", &request[i]);
        }

        requestResources(processNum, request);
    }

    return 0;
}
