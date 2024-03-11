#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stddef.h>
#include"mymalloc.h"
#define CAPACITY 25000
#define TOP 2500

char Array[CAPACITY] = {0};
size_t heap_size = 0;
const size_t Start = 22000;
struct Chunk *Block = (struct Chunk *)(Array+Start);
size_t End = 0;

void *MyMalloc(size_t size){
    for(size_t i=0;i<End;i++){
        if ((Block+i)->used==false){
            if ((Block+i)->size==size){
                (Block+i)->size=size;
                (Block+i)->used=true;
                printf("Memory allocated in Array\n");
                return ((Block+i)->start);
            } 
            else if((Block+i)->size>size){
                 for(size_t j=End;j>i+1;j--){
                    *(Block+j)=*(Block+j-1);
                }
                size_t new_size=(Block+i)->size-size;
                void *new_loc=(Block+i)->start+size;
                (Block+i)->size=size;
                (Block+i)->used=true;
                struct Chunk chunk={
                    .start=new_loc,
                    .size=new_size,
                    .used=false
                };
                *(Block+i+1)=chunk;
                End=End+1;
                return ((Block+i)->start);
            } 
            else{
                continue;
            }
        }
    }
    if(heap_size+size<=CAPACITY-TOP){
        void *result=Array+heap_size;
        heap_size=heap_size+size;
        struct Chunk chunk={
            .start=result,  
            .size=size,
            .used=true
        };
        *(Block+End)=chunk;
        End=End+1;
        printf("Memory allocated in next available space\n");
        return result;
    }
    else{
        printf("Memory not allocation error\n");
        return NULL;
    }
}

void MyFree(void *ptr){
    for(size_t i=0;i<End;i++) {
        if((Block+i)->start==ptr) {
            (Block+i)->used=false;
            break;
        }
    }
    for(size_t i=0;i<End-1;i++){
        if((Block+i)->used==false){
            struct Chunk *ptr=Block+i;
            if((ptr+1)->used==false){
                (ptr)->size+=(ptr+1)->size;
                for(size_t j=0;j<End-2;j++){
                    *(ptr+1+j)=*(ptr+2+j);
                }
                End=End-1;
            }
        }
    }
}
