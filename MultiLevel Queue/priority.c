#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100

struct Priority_Process{
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

void Index_Dequeue(struct Queue *Q,int index){
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
    struct Queue Q4 = {.Rear = -1, .Front = -1};

    for(int i=0;i<n;i++){
        int k,l;
        struct Priority_Process* P=(struct Priority_Process*) malloc (sizeof(struct Priority_Process));
        printf("Enter the process Id =");
        scanf("%d",&P->Id);
        printf("Enter the burst time of the process =");
        scanf("%d",&P->BurstTime);
        P->RemainingTime=P->BurstTime;
        printf("Enter the priority of the process=");
        scanf("%d",&k);
        if(k==4){
            printf("Enter the priority inside the Queue: ");
            scanf("%d",&l);
            while(l<0 || l>4){
                printf("Priority is of the process inside the Queue is wrong. Enter again: ");
                scanf("%d",&l);
                printf("\n");
            }
            p->Priority=l;
        }
        printf("\n");
        while(k<0 || k>4){
            printf("Priority is wrong. Enter again: ");
            scanf("%d",&k);
            printf("\n");
        }
        if(k==0){
            Enqueue(&Q4,P);
        }
    }
    PrintQueue(&Q0);
    do{
        FIFO(&Q0);
    }while(!IsEmpty(&Q0));
    return 0;
}