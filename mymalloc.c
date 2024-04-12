#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "mymalloc.h"

#define CAPACITY 250
#define METADATA_SIZE sizeof(struct block);

struct block{
    size_t size; //size_ t is a something like a datatype
    int free;
    struct block* next;
};

int ini = 0;

char memory[CAPACITY] = { '\0' }; //Our RAM
struct block* freelist = (void*)memory; //Pointer to bottom.Which is Startting point of the RAM

void initialize()
{
    freelist->size = CAPACITY - METADATA_SIZE;
    freelist->free = 1;
     freelist->next = NULL;
}

void split(struct block* fitting_slot, size_t size)
{
    struct block* new = (void*)((void*)fitting_slot + size + sizeof(struct block));
    
    //Just like link list

    new->size = (fitting_slot->size) - size - METADATA_SIZE;
    new->free = 1;
    new->next = fitting_slot->next;

    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;

}

//first encounting memory block use to store
void* MyMalloc(size_t NoOfBytes)
{
    if(ini == 0)
    {
        initialize();
        ini = 1;
    }
    struct block* curr = freelist;
    
    //Cheking whether the curr pointer in inside the RAM or NOT
    //if not then it not initalized yet therefor we initialize it 
    //Creating memory
    if(!((void*)memory <= (void*)curr && (void*)curr <= (void*)(memory + CAPACITY)))
    {
        initialize();
        curr = freelist;
    }

    //Travers until enconter a proper place 
    while((((curr->size) < NoOfBytes)) || ((curr->free == 0)) && (curr->next != NULL))
    {
        curr = curr->next;
    }

    //exact amout of space is not sufficient(need to store new METADATA)
    if(curr->size == NoOfBytes) 
    {
        curr->free = 0;
        //we need to check storage after this curr. thats why we ++curr
        return (void*)(++curr);
    }
    else if((curr->size) > (NoOfBytes + sizeof(struct block)))
    {
        split(curr, NoOfBytes);
        return (void*)(++curr);
    }

    return NULL;

}

//merging nearby free spaces
void merge(){
    //printf("\nmerge is running");
    struct block* curr = freelist;
    while(curr->next != NULL){
        if((curr->free) && curr->next->free)
        {
            curr->size += curr->next->size + METADATA_SIZE; 
            curr->next = curr->next->next;
        } 
               
        curr = curr->next;

    }
}

void MyFree(void *ptr)
{
    //printf("\nMyFree is running");
    if(((void*)memory <= ptr) && (ptr <= (void*)(memory + CAPACITY)))
    {
        struct block* curr = ptr;
        --curr;
        
        //below block has the infomation about freeing block. thats why we need to --curr
        curr->free = 1;
        
        //printf("\nMerge before in MyFree");
        merge();
        //printf("\ninside if");
    }
    
    //printf("\noutside if bottom before end");
}

void* MyCalloc(size_t NoOfBytes)
{
    struct block* curr = freelist;
    
    //Cheking whether the curr pointer in inside the RAM or NOT
    //if not then it not initalized yet therefor we initialize it 
    //Creating memory
    if(!((void*)memory <= (void*)curr && (void*)curr <= (void*)(memory + CAPACITY)))
    {
        initialize();
        curr = freelist;
    }

    //Travers until enconter a proper place 
    while((((curr->size) < NoOfBytes)) || ((curr->free == 0)) && (curr->next != NULL))
    {
        curr = curr->next;
    }

    //exact amout of space is not sufficient(need to store new METADATA)
    if(curr->size == NoOfBytes) 
    {
        curr->free = 0;
        //we need to check storage after this curr. thats why we ++curr
        return (void*)(++curr);
    }
    else if((curr->size) > (NoOfBytes + sizeof(struct block)))
    {
        split(curr, NoOfBytes);
        return (void*)(++curr);
    }

    return NULL;

}

void printRAM()
{
    for (int i = 0; i < CAPACITY; ++i) {
        printf("%02X ", (unsigned char)memory[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}


