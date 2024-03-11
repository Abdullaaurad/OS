#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100

struct Process{
    int Id;
    int BurstTime;
    int RemainingTime;
    int WaiteTime;
    int TurnaroundTime;
};

struct Queue{
    int Rear;
    int Front;
    struct Process* list[MAX_SIZE];
};

int time=0;

bool IsEmpty(struct Queue* Q) {
  return ((Q->Front==-1)||(Q->Rear==-1));
}

bool IsFull(struct Queue* Q) {
  return (Q->Rear+1)%MAX_SIZE==Q->Front;
}

void Enqueue(struct Queue* Q,struct Process* p){
    if(IsFull(Q)){
        printf("No space in the Queue\n");
    }
    else{
        if(IsEmpty(Q)){
            Q->Front=0;
        }
        Q->Rear=(Q->Rear+1)%MAX_SIZE;
        Q->list[Q->Rear]=p;
    }
}

void Dequeue(struct Queue* Q){
    if(IsEmpty(Q)){
        printf("The Queue is empty\n");
    }
    else{
        if(Q->Rear==Q->Front){
            Q->Rear=-1;
            Q->Front=-1;
        }
        else{
            Q->Front=(Q->Front+1)%MAX_SIZE;
        }
    }
}

void Robin_Dequeue(struct Queue* Q,int index){
    if(Q->Front==index){
        Q->Front++;
    }
    else{
        for(int i=index;i>Q->Front;i--){
            Q->list[i]=Q->list[i-1];
        }
        Q->Front++;
    }
}

void RR(struct Queue* Q){ 
    int size=1+(Q->Rear-Q->Front);
    if(size>20){
        int timeQuantum=1;
        for(int i=Q->Front;i<=Q->Front+20;i++){
            if(Q->list[i]->RemainingTime==1){
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,time,time++);
                Q->list[i]->TurnaroundTime=time;
                Q->list[i]->WaiteTime=Q->list[i]->TurnaroundTime-Q->list[i]->BurstTime;
                printf("The waiting time of the process =%d\n",Q->list[i]->WaiteTime);
                printf("The turnaround time of the process =%d\n\n",Q->list[i]->TurnaroundTime);
                Robin_Dequeue(Q,i);
            }
            else{
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,time,time++);
                printf("There is a remaining burst time of %d\n\n",Q->list[i]->RemainingTime);
                Q->list[i]->RemainingTime-=1;
            }
        }
    }
    else{
        int timeQuantum=20/size;
        printf("timeQuantum =%d",timeQuantum);
        for(int i=Q->Front;i<=Q->Rear;i++){
            if(Q->list[i]->RemainingTime<=timeQuantum){
                int t=time;
                time=time+Q->list[i]->BurstTime;
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,t,time);
                Q->list[i]->TurnaroundTime=time;
                Q->list[i]->WaiteTime=Q->list[i]->TurnaroundTime-Q->list[i]->BurstTime;
                printf("The waiting time of the process =%d\n",Q->list[i]->WaiteTime);
                printf("The turnaround time of the process =%d\n\n",Q->list[i]->TurnaroundTime);
                Robin_Dequeue(Q,i);
            } 
            else{
                int t=time;
                time=time+timeQuantum;
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,t,time);
                Q->list[i]->RemainingTime-=timeQuantum;
                printf("There is a remaining burst time of %d\n",Q->list[i]->RemainingTime);
            }
        }
    }
}

void PrintQueue(struct Queue* Q) {
    if(IsEmpty(Q)) {
        printf("The Queue is empty\n");
    } else {
        int i = Q->Front;
        printf("Processes in the Queue:\n");
        while(i != Q->Rear) {
            printf("Process ID: %d, Burst Time: %d\n",Q->list[i]->Id, Q->list[i]->BurstTime);
            i = (i + 1) % MAX_SIZE;
        }
        printf("Process ID: %d, Burst Time: %d\n", Q->list[i]->Id, Q->list[i]->BurstTime);
    }
}

int main(){
    int n;
    printf("Enter the number of process to enter =");
    scanf("%d",&n);
    printf("\n");

    struct Queue Q0 = {.Rear = -1, .Front = -1};
    struct Queue Q1 = {.Rear = -1, .Front = -1};
    struct Queue Q2 = {.Rear = -1, .Front = -1};
    struct Queue Q3 = {.Rear = -1, .Front = -1};

    for(int i=0;i<n;i++){
        int k;
        struct Process* P=(struct Process*) malloc (sizeof(struct Process));
        printf("Enter the process Id =");
        scanf("%d",&P->Id);
        printf("Enter the burst time of the process =");
        scanf("%d",&P->BurstTime);
        P->RemainingTime=P->BurstTime;
        printf("Enter the priority of the process=");
        scanf("%d",&k);
        printf("\n");
        while(k<0 || k>3){
            printf("Priority is wrong. Enter again: ");
            scanf("%d",&k);
            printf("\n");
        }
        if(k==0){
            Enqueue(&Q0,P);
        }
    }
    PrintQueue(&Q0);
    RR(&Q0);
    return 0;
}