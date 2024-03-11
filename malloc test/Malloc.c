//this has a problem when handling if the first block is freed

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <stddef.h>

#define HeapCapacity 25000

char Array[HeapCapacity];
size_t HeapSize=0;

struct Block {
    size_t size;
    struct Block* next;
};


void* MyMalloc(size_t size) {
    struct Block* New;

    if (Array[0] == '\0') {
        // First allocation
        New = (struct Block*)Array;
        New->size = size;
        New->next = NULL;
        HeapSize += (sizeof(struct Block) + size);
    } else {
        struct Block* ptr = (struct Block*)&Array[0];

        while (ptr->next != NULL && (size_t)(ptr->next) - (size_t)ptr == ptr->size) {
            ptr = ptr->next;
        }

        if (ptr->next != NULL && (size_t)(ptr->next) - (size_t)ptr >= size) {
            // Reuse existing space
            size_t offset = (size_t)(ptr->next) - (size_t)&Array[0] + ptr->size + sizeof(struct Block);
            New = (struct Block*)&Array[offset];
            New->next = ptr->next;
            ptr->next = New;
        } else {
            // Allocate new space
            New = (struct Block*)&Array[HeapSize];
            ptr->next = New;
            HeapSize = HeapSize + (sizeof(struct Block) + size);
        }
    }

    if (New == NULL) {
        return NULL;
    }

    New->size = size;
    return (void*)(New + 1);
}


void MyFree(void* ptr){
    if(ptr==NULL){
        return;
    }
    struct Block* current=(struct Block*)((char*)ptr);
    struct Block* temp=(struct Block*)&Array[0];
    if(temp==current){
        Array[0]='\0';
        return;
    }
    while((temp!=NULL)&&((temp->next)!=current)){
        temp=temp->next;
    }
    if((current->next)!=NULL){
        temp->next=current->next;
    }
    if((current->next)==NULL){
        HeapSize=HeapSize-(sizeof(struct Block)+current->size);
        temp->next=NULL;
    }
}

int main(){
    void* fh1=MyMalloc(sizeof(int));
    printf("fh1=%p\n",fh1); 
    void* fh2=MyMalloc(sizeof(int));
    printf("fh2=%p\n",fh2);
    MyFree(fh2);
    MyFree(fh1);
    void* fh3=MyMalloc(sizeof(int));
    printf("fh3=%p\n",fh3);
    void* fh4=MyMalloc(sizeof(int));
    printf("fh4=%p\n",fh4);
    void* fh5=MyMalloc(sizeof(int));
    printf("fh5=%p\n",fh5);
    void* fh6=MyMalloc(sizeof(int));
    printf("fh6=%p\n",fh6);
    void* fh7=MyMalloc(sizeof(int));
    printf("fh7=%p\n",fh7);
    void* fh8=MyMalloc(sizeof(int));
    printf("fh8=%p\n",fh8);
    void* fh9=MyMalloc(sizeof(int));
    printf("fh9=%p\n",fh9);
    void* fh10=MyMalloc(sizeof(int));
    printf("fh10=%p\n",fh10);
    void* fh11=MyMalloc(sizeof(int));
    printf("fh11=%p\n",fh11);
    void* fh12=MyMalloc(sizeof(int));
    printf("fh12=%p\n",fh12);
    void* fh13=MyMalloc(sizeof(int));
    printf("fh13=%p\n",fh13);
    void* fh14=MyMalloc(sizeof(int));
    printf("fh14=%p\n",fh14);
    void* fh15=MyMalloc(sizeof(int));
    printf("fh15=%p\n",fh15);
    void* fh16=MyMalloc(sizeof(int));
    printf("fh16=%p\n",fh16);
    return 0;
}