#include <stdio.h>
#include "mymalloc.h"


int main() {

    int *root = (int *)MyMalloc(4*5);
    
    for (int i = 0; i < 5; i++) {
        root[i] = i+1;
    }

    // dump_chunks();

    char *root1 = MyMalloc(5);
    
    for (int i = 0; i < 5; i++) {
        root1[i] = i+'A';
    }

    // dump_chunks();

    char *root2 = MyMalloc(10);

    for (int i = 0; i < 10; i++) {
        root2[i] = i+'S';
    }

    // dump_chunks();

    MyFree(root1);

    // dump_chunks();

    char *root3 = (char *)MyMalloc(3);
    for (int i = 0; i < 3; i++) {
        root3[i] = 'O';
    }

    // dump_chunks();

    char *root4 = (char *)MyMalloc(2);
    for (int i = 0; i < 2; i++) {
        root4[i] = 'X';
    }

    // dump_chunks();

    MyFree(root4);
    MyFree(root3);

    // dump_chunks();

    char *root5 = (char *)MyMalloc(5);
    for (int i = 0; i < 2; i++) {
        root4[i] = 'Y';
    }

    // dump_chunks();

    char *root6 = (char *)MyMalloc(24000);

    char *root7 = (char *)MyMalloc(20);

    // dump_chunks();
    
    return 0;
}
