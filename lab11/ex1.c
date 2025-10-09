#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void input_data(int *requests, int *n, int *head, int *disk_size) {
    printf("Enter the total number of disk requests: ");
    scanf("%d", n);
    
    printf("Enter the requests (cylinder numbers):\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position (cylinder number): ");
    scanf("%d", head);
    
    printf("Enter the total disk size (max cylinder + 1, e.g., 200 for 0-199): ");
    scanf("%d", disk_size);
}

int find_min_time(int current_head, int *requests, int n, int *visited) {
    int min_time = INT_MAX;
    int min_index = -1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int time = abs(current_head - requests[i]);
            if (time < min_time) {
                min_time = time;
                min_index = i;
            }
        }
    }
    return min_index;
}

void sstf(int *requests, int n, int head) {
    int current_head = head;
    int total_movement = 0;
    int *visited = (int *)calloc(n, sizeof(int));
    int processed = 0;
    int min_index;
    
    printf("\nSSTF Scheduling:\n");
    printf("Sequence: %d", current_head);

    while (processed < n) {
        min_index = find_min_time(current_head, requests, n, visited);
        if (min_index != -1) {
            total_movement += abs(current_head - requests[min_index]);
            current_head = requests[min_index];
            visited[min_index] = 1;
            processed++;
            printf(" -> %d", current_head);
        }
    }
    
    printf("\nTotal Head Movement (SSTF): %d\n", total_movement);
    free(visited);
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

void scan(int *requests_orig, int n_orig, int head, int disk_size, int direction) {
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
    
    printf("\nSCAN Scheduling:\n");
    printf("Sequence: %d", current_head);

    if (direction == 1) { 
        for (int i = start_index + 1; i < n; i++) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }
        total_movement += abs(current_head - (disk_size - 1));
        current_head = disk_size - 1;
        printf(" -> %d (End)", current_head);

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
        total_movement += abs(current_head - 0);
        current_head = 0;
        printf(" -> %d (End)", current_head);

        for (int i = start_index + 1; i < n; i++) {
            total_movement += abs(current_head - requests[i]);
            current_head = requests[i];
            printf(" -> %d", current_head);
        }
    }

    printf("\nTotal Head Movement (SCAN): %d\n", total_movement);
    free(requests);
}

void c_scan(int *requests_orig, int n_orig, int head, int disk_size) {
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
    
    printf("\nC-SCAN Scheduling:\n");
    printf("Sequence: %d", current_head);

    for (int i = start_index + 1; i < n; i++) {
        total_movement += abs(current_head - requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }
    
    total_movement += abs(current_head - (disk_size - 1));
    current_head = disk_size - 1;
    printf(" -> %d (End)", current_head);

    total_movement += abs(current_head - 0);
    current_head = 0;
    printf(" -> %d (Start)", current_head);

    for (int i = 0; i < start_index; i++) {
        total_movement += abs(current_head - requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (C-SCAN): %d\n", total_movement);
    free(requests);
}

void c_look(int *requests_orig, int n_orig, int head) {
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
    
    printf("\nC-LOOK Scheduling:\n");
    printf("Sequence: %d", current_head);

    for (int i = start_index + 1; i < n; i++) {
        total_movement += abs(current_head - requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }
    
    for (int i = 0; i < start_index; i++) {
        total_movement += abs(current_head - requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (C-LOOK): %d\n", total_movement);
    free(requests);
}

int main() {
    int MAX_REQUESTS = 100;
    int requests[MAX_REQUESTS];
    int n = 0;
    int head = 0;
    int disk_size = 0;
    int choice;
    int direction; 

    while (1) {
        printf("\n--- Disk Scheduling Algorithms ---\n");
        printf("1. Enter Disk Request Data\n");
        printf("2. Simulate SSTF\n");
        printf("3. Simulate SCAN\n");
        printf("4. Simulate C-SCAN\n");
        printf("5. Simulate C-LOOK\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 2 && choice <= 5 && n == 0) {
            printf("Please enter disk request data first (Option 1).\n");
            continue;
        }

        switch (choice) {
            case 1:
                input_data(requests, &n, &head, &disk_size);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                printf("Enter initial direction (1 for towards larger cylinders, 0 for smaller): ");
                scanf("%d", &direction);
                scan(requests, n, head, disk_size, direction);
                break;
            case 4:
                c_scan(requests, n, head, disk_size);
                break;
            case 5:
                c_look(requests, n, head);
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
