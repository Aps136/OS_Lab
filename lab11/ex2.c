#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input_data(int *requests, int *n, int *head) {
    printf("Enter the total number of disk requests: ");
    if (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid number of requests.\n");
        *n = 0;
        return;
    }
    
    printf("Enter the requests (cylinder numbers):\n");
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &requests[i]) != 1 || requests[i] < 0) {
            printf("Invalid cylinder number. Restarting input.\n");
            *n = 0;
            return;
        }
    }
    
    printf("Enter the initial head position (cylinder number): ");
    if (scanf("%d", head) != 1 || *head < 0) {
        printf("Invalid head position. Restarting input.\n");
        *n = 0;
        return;
    }
}

void fcfs(int *requests, int n, int head) {
    if (n == 0) return;
    
    int current_head = head;
    int total_movement = 0;
    
    printf("\nFCFS Scheduling:\n");
    printf("Sequence: %d", current_head);

    for (int i = 0; i < n; i++) {
        total_movement += abs(current_head - requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }
    
    printf("\nTotal Head Movement (FCFS): %d\n", total_movement);
}

void sort_requests(int *requests, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void look(int *requests_orig, int n_orig, int head, int direction) {
    if (n_orig == 0) return;
    
    int n = n_orig + 1; 
    int *requests = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n_orig; i++) requests[i] = requests_orig[i];
    requests[n_orig] = head;

    sort_requests(requests, n);

    int start_index = -1;
    for (int i = 0; i < n; i++) {
        if (requests[i] == head) {
            start_index = i;
            break;
        }
    }

    int total_movement = 0;
    int current_head = head;
    
    printf("\nLOOK Scheduling:\n");
    printf("Sequence: %d", current_head);

    if (direction == 1) { 
        for (int i = start_index + 1; i < n; i++) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }

        for (int i = start_index - 1; i >= 0; i--) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }
    } else { 
        for (int i = start_index - 1; i >= 0; i--) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }

        for (int i = start_index + 1; i < n; i++) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }
    }

    printf("\nTotal Head Movement (LOOK): %d\n", total_movement);
    free(requests);
}

int main() {
    int MAX_REQUESTS = 100;
    int requests[MAX_REQUESTS];
    int n = 0;
    int head = 0;
    int choice;
    int direction; 

    while (1) {
        printf("\n--- Disk Scheduling Algorithms (FCFS, LOOK) ---\n");
        printf("1. Enter Disk Request Data\n");
        printf("2. Simulate FCFS\n");
        printf("3. Simulate LOOK\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice >= 2 && choice <= 3 && n == 0) {
            printf("Please enter disk request data first (Option 1).\n");
            continue;
        }

        switch (choice) {
            case 1:
                input_data(requests, &n, &head);
                break;
            case 2:
                fcfs(requests, n, head);
                break;
            case 3:
                printf("Enter initial direction (1 for towards larger cylinders, 0 for smaller): ");
                if (scanf("%d", &direction) != 1 || (direction != 0 && direction != 1)) {
                    printf("Invalid direction. Use 1 or 0.\n");
                    break;
                }
                look(requests, n, head, direction);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
