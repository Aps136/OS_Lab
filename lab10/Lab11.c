#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the absolute difference (head movement)
int calculateMovement(int a, int b) {
    return abs(a - b);
}

// Function to sort an array (used by SCAN/C-SCAN)
void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// -------------------------------------------------------------------
// 1. FCFS (First-Come, First-Served) Algorithm
// -------------------------------------------------------------------
void fcfs(int *requests, int numRequests, int initialHead) {
    int currentHead = initialHead;
    int totalMovement = 0;

    printf("\n--- FCFS Scheduling ---\n");
    printf("Sequence of Head Movement: %d -> ", initialHead);

    for (int i = 0; i < numRequests; i++) {
        int movement = calculateMovement(currentHead, requests[i]);
        totalMovement += movement;
        currentHead = requests[i];
        printf("%d", currentHead);
        if (i < numRequests - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Total Head Movement (Seek Time): %d\n", totalMovement);
}

// -------------------------------------------------------------------
// 2. SCAN (Elevator) Algorithm
// -------------------------------------------------------------------
void scan(int *requests, int numRequests, int initialHead, int maxCylinder) {
    // 1. Copy and sort the requests
    int *sortedRequests = (int *)malloc(numRequests * sizeof(int));
    if (sortedRequests == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < numRequests; i++) {
        sortedRequests[i] = requests[i];
    }
    sortArray(sortedRequests, numRequests);

    int currentHead = initialHead;
    int totalMovement = 0;
    int direction = 1; // 1 for high (outward), -1 for low (inward). Assume moving HIGH first.
    int i;

    printf("\n--- SCAN Scheduling (Moving HIGH first) ---\n");
    printf("Sequence of Head Movement: %d -> ", initialHead);

    // Find the starting point in the sorted array
    for (i = 0; i < numRequests; i++) {
        if (sortedRequests[i] >= initialHead) {
            break;
        }
    }

    // Process requests in the chosen direction (HIGH)
    for (int j = i; j < numRequests; j++) {
        totalMovement += calculateMovement(currentHead, sortedRequests[j]);
        currentHead = sortedRequests[j];
        printf("%d -> ", currentHead);
    }

    // Move to the end of the disk (MAX CYLINDER)
    if (currentHead != maxCylinder) {
        totalMovement += calculateMovement(currentHead, maxCylinder);
        currentHead = maxCylinder;
        printf("%d -> ", currentHead);
    }

    // Process requests in the opposite direction (LOW)
    for (int j = i - 1; j >= 0; j--) {
        totalMovement += calculateMovement(currentHead, sortedRequests[j]);
        currentHead = sortedRequests[j];
        printf("%d", currentHead);
        if (j > 0) {
            printf(" -> ");
        }
    }

    printf("\n");
    printf("Total Head Movement (Seek Time): %d\n", totalMovement);
    free(sortedRequests);
}

// -------------------------------------------------------------------
// 3. C-SCAN (Circular-SCAN) Algorithm
// -------------------------------------------------------------------
void c_scan(int *requests, int numRequests, int initialHead, int maxCylinder) {
    // 1. Copy and sort the requests
    int *sortedRequests = (int *)malloc(numRequests * sizeof(int));
    if (sortedRequests == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < numRequests; i++) {
        sortedRequests[i] = requests[i];
    }
    sortArray(sortedRequests, numRequests);

    int currentHead = initialHead;
    int totalMovement = 0;
    int i;
    int minCylinder = 0; // Assume minimum cylinder is 0

    printf("\n--- C-SCAN Scheduling (Moving HIGH first) ---\n");
    printf("Sequence of Head Movement: %d -> ", initialHead);

    // Find the starting point in the sorted array
    for (i = 0; i < numRequests; i++) {
        if (sortedRequests[i] >= initialHead) {
            break;
        }
    }

    // Process requests from current head to MAX_CYLINDER
    for (int j = i; j < numRequests; j++) {
        totalMovement += calculateMovement(currentHead, sortedRequests[j]);
        currentHead = sortedRequests[j];
        printf("%d -> ", currentHead);
    }

    // Move from current head to MAX_CYLINDER
    if (currentHead != maxCylinder) {
        totalMovement += calculateMovement(currentHead, maxCylinder);
        currentHead = maxCylinder;
        printf("%d -> ", currentHead);
    }

    // JUMP to MIN_CYLINDER (0) without counting seek time for the jump itself,
    // but the next movement will be from 0
    printf("0 -> ");
    currentHead = minCylinder;
    totalMovement += calculateMovement(maxCylinder, minCylinder); // Standard approach counts this movement

    // Process remaining requests from MIN_CYLINDER to the request just before the starting point
    for (int j = 0; j < i; j++) {
        totalMovement += calculateMovement(currentHead, sortedRequests[j]);
        currentHead = sortedRequests[j];
        printf("%d", currentHead);
        if (j < i - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
    printf("Total Head Movement (Seek Time): %d\n", totalMovement);
    free(sortedRequests);
}

// -------------------------------------------------------------------
// Main Menu Function
// -------------------------------------------------------------------
int main() {
    int choice;
    int numRequests, initialHead, maxCylinder;
    int *requests = NULL;

    printf("--- Disk Scheduling Simulation ---\n");

    // Get common input from the user
    printf("Enter the maximum cylinder number (e.g., 199 for 0-199): ");
    if (scanf("%d", &maxCylinder) != 1 || maxCylinder <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter the initial head position: ");
    if (scanf("%d", &initialHead) != 1 || initialHead < 0 || initialHead > maxCylinder) {
        printf("Invalid input or head position out of range.\n");
        return 1;
    }

    printf("Enter the number of disk requests: ");
    if (scanf("%d", &numRequests) != 1 || numRequests <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Dynamic allocation for requests
    requests = (int *)malloc(numRequests * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the cylinder requests (separated by spaces):\n");
    for (int i = 0; i < numRequests; i++) {
        if (scanf("%d", &requests[i]) != 1 || requests[i] < 0 || requests[i] > maxCylinder) {
            printf("Invalid cylinder request out of range. Exiting.\n");
            free(requests);
            return 1;
        }
    }

    do {
        printf("\nDisk Scheduling Menu:\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input
            choice = 0;
            while (getchar() != '\n'); // Clear buffer
        }

        switch (choice) {
            case 1:
                fcfs(requests, numRequests, initialHead);
                break;
            case 2:
                scan(requests, numRequests, initialHead, maxCylinder);
                break;
            case 3:
                c_scan(requests, numRequests, initialHead, maxCylinder);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    free(requests);
    return 0;
}
