#include <stdio.h>
#include <stdbool.h>

#define P_MAX 10
#define R_MAX 10

int n, m;
int A[R_MAX], Max[P_MAX][R_MAX], Alloc[P_MAX][R_MAX], Need[P_MAX][R_MAX];

void calc_need() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Alloc[i][j];
}

bool check_safe(int current_A[R_MAX], int temp_Alloc[P_MAX][R_MAX], int temp_Need[P_MAX][R_MAX]) {
    int Work[R_MAX], safeSeq[P_MAX], count = 0;
    bool Finish[P_MAX] = {false};

    for (int i = 0; i < m; i++) Work[i] = current_A[i];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool can_alloc = true;
                for (int j = 0; j < m; j++)
                    if (temp_Need[i][j] > Work[j]) { can_alloc = false; break; }
                
                if (can_alloc) {
                    for (int k = 0; k < m; k++) Work[k] += temp_Alloc[i][k];
                    safeSeq[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

void try_request(int pid, int req[R_MAX]) {
    int temp_A[R_MAX], temp_Alloc[P_MAX][R_MAX], temp_Need[P_MAX][R_MAX];
    
    for (int i = 0; i < m; i++) {
        if (req[i] > Need[pid][i]) { printf("Error: Request exceeds need.\n"); return; }
        if (req[i] > A[i]) { printf("Resources not available. Process must wait.\n"); return; }
    }

    // Pretend allocation
    for (int i = 0; i < m; i++) temp_A[i] = A[i] - req[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            temp_Alloc[i][j] = Alloc[i][j];
            temp_Need[i][j] = Need[i][j];
        }
    for (int i = 0; i < m; i++) {
        temp_Alloc[pid][i] += req[i];
        temp_Need[pid][i] -= req[i];
    }

    if (check_safe(temp_A, temp_Alloc, temp_Need)) {
        printf("Request GRANTED.\n");
        for (int i = 0; i < m; i++) {
            A[i] = temp_A[i];
            Alloc[pid][i] = temp_Alloc[pid][i];
            Need[pid][i] = temp_Need[pid][i];
        }
    } else {
        printf("Request DENIED (Leads to unsafe state).\n");
    }
}

int main() {
    printf("P: "); scanf("%d", &n);
    printf("R: "); scanf("%d", &m);

    printf("Available (R0 R1...):\n");
    for (int i = 0; i < m; i++) scanf("%d", &A[i]);

    printf("Max:\n");
    for (int i = 0; i < n; i++) { printf("P%d: ", i); for (int j = 0; j < m; j++) scanf("%d", &Max[i][j]); }

    printf("Allocation:\n");
    for (int i = 0; i < n; i++) { printf("P%d: ", i); for (int j = 0; j < m; j++) scanf("%d", &Alloc[i][j]); }

    calc_need();

    printf("\nInitial Safety Check:\n");
    if (!check_safe(A, Alloc, Need)) {
        printf("Initial state is UNSAFE. Exiting.\n");
        return 0;
    }

    while (1) {
        int pid, req[R_MAX];
        printf("\nRequest (PID, -1 to exit): ");
        scanf("%d", &pid);
        if (pid == -1) break;

        printf("Request (R0 R1...): ");
        for (int i = 0; i < m; i++) scanf("%d", &req[i]);

        try_request(pid, req);
    }

    return 0;
}
