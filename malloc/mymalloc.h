#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdbool.h>
#include<stddef.h>

struct Chunk{
    void *start;
    size_t size;
    bool used;
};

void dump_chunks();
void *MyMalloc(size_t size);
void MyFree(void *ptr);

#endif
