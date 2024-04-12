#include <stdio.h>
#include "mymalloc.h"

int main(){
    printf("Running Main.C ...\n");
    // Allocate memory
    int* ptr1 = (int *)MyMalloc(10 *sizeof (int));
    
    if(ptr1==NULL){
        printf("Memory Allocation Failed");
    }
    else{
        printf("Memory Allocated Successfully\n");
    }
    
    void* ptr2 = MyMalloc(20);
    for (int i = 0; i < 10; ++i) {
        // Accessing elements and assigning values for the array of allocated memory
        (ptr1)[i] = i;
    }

  printf("\n");
    // Print the contents of the array
    printf("Contents of the Allocated array: ");
    for (int i = 0; i < 10; ++i) {
        printf("%d", (*(ptr1)+i));
    }
    
    MyFree(ptr1);
    printf("Memory Freed\n");
    return 0;
}