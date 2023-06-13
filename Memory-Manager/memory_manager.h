#ifndef MEMORY_MANAGER_HEADER
#define MEMORY_MANAGER_HEADER

#include "linked_list.h"

#define FIRST_FIT 0
#define BEST_FIT 1

typedef struct _memory_manager
{
    list *free_pointer;
    list *busy_pointer;
    void* ram_space;
    int fit_type;
} Memory_Manager;

Memory_Manager *init_memory_space(int size, int type);
void* allocate_memory(int size, Memory_Manager* manager);
int eliminate_memory(void* memory_block, Memory_Manager* manager);
int free_memory(Memory_Manager* usedSpace);

#endif
