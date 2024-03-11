#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resource;
int num_instances[MAX_RESOURCES];

// Function prototypes
int is_safe();
bool request_resources(int process_num, int request[]);

int main() {
    // Initialize variables
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resource types: ");
    scanf("%d", &num_resource);

    // Input available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < num_resource; i++) {
        scanf("%d", &available[i]);
    }

    // Input maximum resources
    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resource; j++) {
            scanf("%d", &need[i][j]);
        }
    }

    // Input allocated resources
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resource; j++) {
            scanf("%d", &allocation[i][j]);
            // Calculate the initial request
            int request = need[i][j] - allocation[i][j];
            if (request < 0) {
                printf("Error: Allocated resources exceed maximum claim for process %d.\n", i);
                return 1; // Exit with error
            }
        }
    }

    // Check for safety and request resources if safe
    if (is_safe()) {
        printf("System is in safe state.\n");
    } else {
        printf("System is in unsafe state.\n");
    }

    return 0;
}

// Function to check if the system is in a safe state
int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    bool can_allocate = true; // Initialize outside the loop

    // Initialize work to available
    for (int i = 0; i < num_resource; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                can_allocate = true; // Reset for each process
                int j;
                for (j = 0; j < num_resource; j++) {
                    int request = need[i][j] - allocation[i][j];
                    if (request < 0 || request > work[j]) {
                        can_allocate = false;
                        break; // Break if request cannot be satisfied
                    }
                }
                if (can_allocate) {
                    // Process can be executed
                    for (int k = 0; k < num_resource; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    count++;
                }
            }
        }
        if (!can_allocate) {
            return 0; // Unsafe state
        }
    }
    return 1; // Safe state
}
