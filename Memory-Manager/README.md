# MemoryManager
The CSC430 class' implementation of a basic memory manager

## Design Document

Lead: Kevin Alonso

Date: Jan 27, 2021

Team: 
* Kevin Alonso
* Ali Amin
* Luke Frisbee
* Alex McCune
* Yunhu Xiang

### Structures
The Memory Manager library requires 2 structures:
```c
Typedef struct _node
{
  struct _node* next;
  void * data;
  int size;
}node;
```

```c
typedef struct _memory_manager
{
    list *free_pointer;
    list * busy_pointer
    int fit_type 
 }Memory_Manager;
```

### Error Codes

* Functions that have no data to return and no reason to fail should return `void`.
* Functions that return pointer will return `NULL` on failure.
* Functions that can succeed or fail but do not return data will return an `int`.
```c
// defined in stdlib.h
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
```

### Functions

- [ ] [Kevin Alonso](mailto:kevin.alonso@eagles.cui.edu): Team Lead

- [x] [Yunhu Xiang](mailto:yunhu.xiang@eagles.cui.edu) `Memory_Manager *init_memory_space(int RAM_size, int type)`: This function will allow us to look at the `size` of the block and decide whether we want to use `first` fit or `best` fit to use our memory sufficiently.

- [x] [Ali Amin](mailto:ali.amindehkordi@eagles.cui.edu) `void *allocate_memory(int memSize, Memory_Manager *manager)`: Will go over the free list and determine if the user is asking for memory and find a block on the free list that is big enough. Ali will complete the Best Fit portion.

- [x] [Alex McCune](mailto:alexander.mccune@eagles.cui.edu) `void *allocate_memory(int memSize, Memory_Manager *manager)`: Will go over the free list and determine if the user is asking for memory and find a block on the free list that is big enough. Alex will complete the First Fit portion.

- [ ] [Luke Frisbee](mailto:luke.frisbee@eagles.cui.edu) `int eliminate_memory(void* memory_block, Memory_Manager* manager)`: When one process finishes, we move it over to the free list. We do not want to keep adding finished processes to the free list, we instead want to combine the processes and make only one entry. I think the goal is to keep the free list with as few entries as possible. We combine processes differently if the block is before us, after us, or there are two free blocks on  both sides. 
When the blocks are on both sides, we need to coalesce it with the block that came before it and the block that came after it. So it can remove entries from the free list and combine them and make it as one block of memory. 

- [ ] [Yunhu Xiang](mailto:yunhu.xiang@eagles.cui.edu) `int free_memory(Memory_Manager)`: Cleans up our program and makes sure there are no memory leaks in the program.
