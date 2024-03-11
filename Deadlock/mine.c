#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

int available[MAX_RESOURCES];                            //available resources now
int allocation[MAX_PROCESSES][MAX_RESOURCES];            //Allocated for a process
int need[MAX_PROCESSES][MAX_RESOURCES];                //how many we need to do the process
int num_processes, num_resource;                        

void execute();

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
    execute();
    return 0;
}

void execute(){
    bool processed[num_processes];
    for(int j=0;j<num_processes;j++){
        processed[j]=false;
    }
    int i=0;
    int done_process=0;
    while(done_process<=num_processes){
        while(processed[i]==false){
            bool can_do=true;
            for(int a=0;a<num_resource;a++){
                if(allocation[i][a]>=need[i][a]){
                    available[a]=available[a]+allocation[i][a];
                }
                else if((need[i][a]-allocation[i][a])<=available[a]){
                    available[a]=available[a]+allocation[i][a];
                }
                else{
                    can_do=false;
                }
            }
            if(can_do==true){
                printf("\nP%d process has been executed",i);
                done_process++;
                processed[i]=true;
            }
            i=(i+1)%num_processes;
        }
    }
}

