#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TASKS 5
#define MAX_TIME 1000 

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline; 
    
    int remaining_time; 
    int next_release_time; 
    int absolute_deadline;
} Task;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_hyperperiod(Task tasks[], int num_tasks) {
    if (num_tasks == 0) return 0;
    int result = tasks[0].period;
    for (int i = 1; i < num_tasks; i++) {
        result = lcm(result, tasks[i].period);
    }
    return result;
}

void reset_tasks(Task tasks[], int num_tasks, Task initial_tasks[]) {
    for (int i = 0; i < num_tasks; i++) {
        tasks[i] = initial_tasks[i]; 
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_release_time = 0;
        tasks[i].absolute_deadline = tasks[i].deadline;
    }
}

// --------------------------------------------------
// EDF SCHEDULING
// --------------------------------------------------

void simulate_edf(Task initial_tasks[], int num_tasks, int hyperperiod) {
    Task tasks[MAX_TASKS];
    reset_tasks(tasks, num_tasks, initial_tasks);
    int current_time = 0;
    int idle_time = 0;
    
    printf("\n\n--- Earliest Deadline First (EDF) Simulation ---\n");
    printf("Time | Running Task | Remaining Time | Absolute Deadline\n");
    printf("-----|--------------|----------------|------------------\n");

    for (current_time = 0; current_time < hyperperiod; current_time++) {
        
        for (int i = 0; i < num_tasks; i++) {
            if (current_time == tasks[i].next_release_time) {
                if (tasks[i].remaining_time != tasks[i].execution_time) {
                    // This is a simplified simulation. A more robust check 
                    // would track job failures, but here we just reset the job.
                    tasks[i].remaining_time = tasks[i].execution_time;
                }
                tasks[i].absolute_deadline = current_time + tasks[i].deadline;
                tasks[i].next_release_time = current_time + tasks[i].period;
            }
        }

        int selected_task = -1;
        int earliest_deadline = MAX_TIME;

        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && current_time >= tasks[i].next_release_time - tasks[i].period) {
                if (tasks[i].absolute_deadline < earliest_deadline) {
                    earliest_deadline = tasks[i].absolute_deadline;
                    selected_task = i;
                }
            }
        }

        if (selected_task != -1) {
            printf("%4d | P%d           | %14d | %17d\n", 
                   current_time, tasks[selected_task].id, 
                   tasks[selected_task].remaining_time, 
                   tasks[selected_task].absolute_deadline);
            tasks[selected_task].remaining_time--;

            if (tasks[selected_task].remaining_time == 0) {
                // Check for deadline miss (simplified)
                if (current_time + 1 > tasks[selected_task].absolute_deadline) {
                    printf("!! DEADLINE MISS: P%d finished at %d, Deadline was %d !!\n", 
                           tasks[selected_task].id, current_time + 1, 
                           tasks[selected_task].absolute_deadline);
                }
            }
        } else {
            printf("%4d | IDLE         |              |                  \n", current_time);
            idle_time++;
        }
    }
}

// --------------------------------------------------
// RM SCHEDULING
// --------------------------------------------------

void simulate_rm(Task initial_tasks[], int num_tasks, int hyperperiod) {
    Task tasks[MAX_TASKS];
    reset_tasks(tasks, num_tasks, initial_tasks);
    int current_time = 0;
    int idle_time = 0;
    
    // Sort tasks by period (Rate Monotonic = shortest period first)
    // Note: The priority is set once at the beginning based on period.
    // We don't need to re-sort here, but we check priority based on the
    // period field for scheduling.
    
    printf("\n\n--- Rate Monotonic (RM) Simulation ---\n");
    printf("Time | Running Task | Remaining Time | Next Release Time\n");
    printf("-----|--------------|----------------|------------------\n");

    for (current_time = 0; current_time < hyperperiod; current_time++) {
        
        for (int i = 0; i < num_tasks; i++) {
            if (current_time == tasks[i].next_release_time) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_release_time = current_time + tasks[i].period;
                tasks[i].absolute_deadline = current_time + tasks[i].deadline;
            }
        }

        int selected_task = -1;
        int shortest_period = MAX_TIME;

        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && current_time >= tasks[i].next_release_time - tasks[i].period) {
                if (tasks[i].period < shortest_period) {
                    shortest_period = tasks[i].period;
                    selected_task = i;
                }
            }
        }

        if (selected_task != -1) {
            printf("%4d | P%d           | %14d | %17d\n", 
                   current_time, tasks[selected_task].id, 
                   tasks[selected_task].remaining_time, 
                   tasks[selected_task].next_release_time);
            tasks[selected_task].remaining_time--;

            if (tasks[selected_task].remaining_time == 0) {
                // Check for deadline miss
                if (current_time + 1 > tasks[selected_task].absolute_deadline) {
                    printf("!! DEADLINE MISS: P%d finished at %d, Deadline was %d !!\n", 
                           tasks[selected_task].id, current_time + 1, 
                           tasks[selected_task].absolute_deadline);
                }
            }
        } else {
            printf("%4d | IDLE         |              |                  \n", current_time);
            idle_time++;
        }
    }
}

// --------------------------------------------------
// MAIN PROGRAM
// --------------------------------------------------

int main() {
    // Example Task Set: T1(20, 10, 20), T2(5, 4, 5) -> C(Execution), P(Period), D(Deadline)
    Task initial_tasks[2] = {
        {1, 20, 10, 20}, // P1: Period 20, Execution 10, Deadline 20
        {2, 5, 4, 5}     // P2: Period 5, Execution 4, Deadline 5
    };
    int num_tasks = 2;
    int hyperperiod = calculate_hyperperiod(initial_tasks, num_tasks);
    double utilization = 0.0;
    
    printf("Real-Time Scheduling Simulation\n");
    printf("==================================\n");

    for (int i = 0; i < num_tasks; i++) {
        utilization += (double)initial_tasks[i].execution_time / initial_tasks[i].period;
    }

    printf("Task Set:\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("P%d: C=%d, P=%d, D=%d\n", initial_tasks[i].id, 
               initial_tasks[i].execution_time, 
               initial_tasks[i].period, 
               initial_tasks[i].deadline);
    }
    printf("Total CPU Utilization: %.2f (Utilization > 1.0 means no schedule possible)\n", utilization);
    printf("Hyperperiod (LCM of Periods): %d\n", hyperperiod);
    
    if (hyperperiod > MAX_TIME) {
        printf("Warning: Hyperperiod (%d) exceeds simulation limit (%d). Simulation will be truncated.\n", 
               hyperperiod, MAX_TIME);
        hyperperiod = MAX_TIME;
    }

    int choice;
    do {
        printf("\n\n--- Menu ---\n");
        printf("1. Simulate Rate-Monotonic (RM)\n");
        printf("2. Simulate Earliest-Deadline-First (EDF)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                simulate_rm(initial_tasks, num_tasks, hyperperiod);
                break;
            case 2:
                simulate_edf(initial_tasks, num_tasks, hyperperiod);
                break;
            case 3:
                printf("Exiting simulation.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
