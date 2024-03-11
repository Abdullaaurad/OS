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

int MIN(struct Queue* Q){
    if(IsEmpty(Q)){
        return -1;
    }
    int min_Index=Q->Front;
    for(int i=Q->Front;i<=Q->Rear;i++){
        if(Q->list[min_Index]->RemainingTime>Q->list[i]->RemainingTime){
            min_Index=i;
        }
    }
    return min_Index;
}

void SJF_Dequeue(struct Queue *Q,int index){
    if(IsEmpty(Q)){
        return;
    }
    else{
        if(index==Q->Front){
            Dequeue(Q);
        }
        else{
            for(int i=index;i>Q->Front;i--){
                Q->list[i]=Q->list[i-1];
            }
            Q->Front++;
        }
    }
}

void SJF(struct Queue *Q){
    int k=time;
    while(time<(k+20)){
        int index=MIN(Q);
        if(index>-1){
            int temp=Q->list[index]->RemainingTime;
            if(k+20-time>=temp){
                printf("Process %d executed from time %d to %d\n", Q->list[index]->Id, time, time + temp);
                time=time+temp;
                Q->list[index]->TurnaroundTime=time;
                Q->list[index]->WaiteTime=Q->list[index]->TurnaroundTime-Q->list[index]->BurstTime;
                printf("The waiting time of the process =%d\n",Q->list[index]->WaiteTime);
                printf("The turnaround time of the process =%d\n\n",Q->list[index]->TurnaroundTime);
                SJF_Dequeue(Q,index);
                return;
            }
            else{
                printf("Process %d executed from time %d to %d\n", Q->list[index]->Id,time,k+20);
                Q->list[index]->RemainingTime-=(k+20-time);
                printf("There is a remaining burst time of %d\n",Q->list[index]->RemainingTime);
                time=k+20;
            }
        }
    }
    return;
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

    struct Queue Q1 = {.Rear = -1, .Front = -1,};
    struct Queue Q2 = {.Rear = -1, .Front = -1,};

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
        while(k<1 || k>2){
            printf("Priority is wrong. Enter again: ");
            scanf("%d",&k);
            printf("\n");
        }
        if(k==1){
            Enqueue(&Q1,P);
        }
        if(k==2){
            Enqueue(&Q2,P);
        }
    }
    int Done=0;
    while(!Done){
        if(!IsEmpty(&Q1)){
            printf("\n\t\tQueue 1\n");
            SJF(&Q1);
        }
        if(!IsEmpty(&Q2)){
            printf("\n\t\tQueue 2\n");
            SJF(&Q2);
        }
        if(IsEmpty(&Q1) && IsEmpty(&Q2)) {
            Done = 1;
        }
    }
    
    return 0;
}