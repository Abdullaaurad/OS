#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100

struct Process{
    int Id;                               // ID of the process  
    int BurstTime;                        // Time the process takes to execute
    int RemainingTime;                    //for non preemptive version of the scheduling
    int WaiteTime;                        //Total waiting time of the process
    int TurnaroundTime;                   //the time the process ended executing
};

struct Queue{                             //Enter the process to the Queue
    int Rear;                             //Rear index of the queue
    int Front;                            //Front index of the queue
    struct Process* list[MAX_SIZE];       //the initial Queue
};

int time=0;                               //the clock in the processor 

bool IsEmpty(struct Queue* Q) {                                 //To check if the queue is empty or not
  return ((Q->Front==-1)||(Q->Rear==-1));
}

bool IsFull(struct Queue* Q) {                                  //To check if the queue is full or not
  return (Q->Rear+1)%MAX_SIZE==Q->Front;
}

void Enqueue(struct Queue* Q,struct Process* p){                 //Function to add the process to the Back of the Queue
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

void Dequeue(struct Queue* Q){                                   //Function to remove the process in the first index of the queue
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

void FIFO(struct Queue* Q){ 
    int k=time;
    while (time<(k+20) && !IsEmpty(Q)) {
        int temp = Q->list[Q->Front]->RemainingTime;
        if (temp <= 20) {
            printf("Process %d executed from time %d to %d\n", Q->list[Q->Front]->Id, time, time + temp);
            time += temp;
            Q->list[Q->Front]->TurnaroundTime = time;
            Q->list[Q->Front]->WaiteTime = Q->list[Q->Front]->TurnaroundTime - Q->list[Q->Front]->BurstTime;
            printf("The waiting time of the process = %d\n", Q->list[Q->Front]->WaiteTime);
            printf("The turnaround time of the process = %d\n\n", Q->list[Q->Front]->TurnaroundTime);
            Dequeue(Q);
        } else {
            printf("Process %d executed from time %d to %d\n", Q->list[Q->Front]->Id, time, time + 20);
            Q->list[Q->Front]->RemainingTime -= 20;
            printf("There is a remaining burst time of %d\n\n", Q->list[Q->Front]->RemainingTime);
            time += 20;
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
                Index_Dequeue(Q,index);
                if(IsEmpty(Q) || time==k+20){
                    return;
                }
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

//In Round Robin Process cant use time to process which are less than 1s
//for physical computers it might change for my implementation its 1s
//if the Queue has more than 20 process the remaining process may not get executed work properly for count less than 20
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
                Index_Dequeue(Q,i);
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
        printf("timeQuantum =%d\n",timeQuantum);
        for(int i=Q->Front;i<=Q->Rear;i++){
            if(Q->list[i]->RemainingTime<=timeQuantum){
                int t=time;
                time=time+Q->list[i]->RemainingTime;
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,t,time);
                Q->list[i]->TurnaroundTime=time;
                Q->list[i]->WaiteTime=Q->list[i]->TurnaroundTime-Q->list[i]->BurstTime;
                printf("The waiting time of the process =%d\n",Q->list[i]->WaiteTime);
                printf("The turnaround time of the process =%d\n\n",Q->list[i]->TurnaroundTime);
                Index_Dequeue(Q,i);
            } 
            else{
                int t=time;
                time=time+timeQuantum;
                printf("Process %d executed from time %d to %d\n", Q->list[i]->Id,t,time);
                Q->list[i]->RemainingTime=Q->list[i]->RemainingTime-timeQuantum;
                printf("There is a remaining burst time of %d\n\n",Q->list[i]->RemainingTime);
            }
        }
    }
}

//To check whether process has been added to the Queue properly

/*
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
*/

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
        while(k<0 || k>4){                                                               //To check the priority of the process
            printf("Priority is wrong. Enter again: ");
            scanf("%d",&k);
            printf("\n");
        }
        if(k==0){
            Enqueue(&Q0,P);
        }
        else if(k==1){
            Enqueue(&Q1,P);
        }
        else if(k==2){
            Enqueue(&Q2,P);
        }
        else if(k==3){
            Enqueue(&Q3,P);
        }
    }

    int Done=0;
    while(!Done){
        if(!IsEmpty(&Q0)){
            printf("\n\t\tQueue 0\n");
            RR(&Q0);
        }
        if(!IsEmpty(&Q1)){
            printf("\n\t\tQueue 1\n");
            SJF(&Q1);
        }
        if(!IsEmpty(&Q2)){
            printf("\n\t\tQueue 2\n");
            SJF(&Q2);
        }
        if(!IsEmpty(&Q3)){
            printf("\n\t\tQueue 3\n");
            FIFO(&Q3);
        }
        if(IsEmpty(&Q0) && IsEmpty(&Q1) && IsEmpty(&Q2) && IsEmpty(&Q3)) {
            Done = 1;
        }
    }
    return 0;
}