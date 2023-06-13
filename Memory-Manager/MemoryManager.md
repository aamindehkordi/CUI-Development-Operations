# Memory Manager
A Memory Manager Library that stores arbitrarily sized and typed data. It was designed with a Heap-style Memory Manager in mind to store the heap's busy and free lists.

The purpose of this project was to teach us the C language and practice working together as a team.

## GNU GPL v3 License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (c) 2021 by Concordia CSC430

## Design Team
* Kevin Alonso
* Ali Amin
* Luke Frisbee
* Alex McCune
* Prof. Tallman
* Yunhu Xiang

## Library and Source Files
The source code is available at [https://github.com/prof-tallman/MemoryManager](https://github.com/prof-tallman/MemoryManager)

This project was written in `C` for the GCC compiler.
```
% gcc -c memory_manager.c -o memory_manager.o
```
Add this library to your project by including `memory_manager.h` and linking to `memory_manager.o`

A program has been included for testing.
```
% gcc memory_manager.o test_program.c -o test.EXIT_SUCCESS
```

## Source Documentation
The memory manager library is made from these data types: `list`, `node`, and `Memory_Manager`.

#### The `node` Type
The `node` type stores each individual item in the memory manager. An item is stored as a generic `void*` buffer and size argument.
```c
typedef struct _node
{
    typedef struct _node* next;
    typedef struct _node* prev;
    void* data
    int size;
} node;
```

#### The `Memory_Manager` Type
The `Memory_Manager` type is a structure that defines a memory manager. It contains pointers to a free and busy list. These pointers should not be modified outside of the memory manager library. The type also includes an internal count than can be accessed to determine the method of allocation, `first` Fit or `best` Fit.
```c
typedef struct _memory_manager
{
    list *free_pointer;
    list * busy_pointer
    int fit_type 
 }Memory_Manager;
```

### Creating Memory Managers
Create a memory manager with the `init_memory_space` function. `init_memory_space` will allocate and return a pointer to a `Memory_Manager` structure. This function allow us to look at the size of the desired block of memory and decide whether we want to use `first` fit or `best` fit to use our memory appropriately.
```c
Memory_Manager* init_memory_space(int RAM_size, int type)
```

The memory manager must be cleaned up manually using the `free_memory` function.

### Allocating Memory
There are two different methods in which memory can be allocated on to the busy list of the Memory Manager sturct, and would have to be done when first creating the Memory Manager through the `init_memory_space` function by setting the `fit_type` variable to be equal to `best` or `first` fit. 

#### First Fit
This method simply steps through the free list of the Memory Manager and upon reaching the first suitably sized block, it will allocate the memory.
`(manager->fit_type == FIRST_FIT)`

#### Best Fit
This method finds the smallest suitable location for the memory and allocates there to save time on defragmentation.
`if (manager->fit_type == BEST_FIT)`

```c
void *allocate_memory(int memSize, Memory_Manager *manager);
```
The caller of this function needs to cleanup any loitering allocations through the `eliminate_memory` function.


### Freeing Memory
Once a process finishes and no longer needs its block of memory, this function would be called to move that block of memory to the free list while also coalescing if needed.

```c
int eliminate_memory(void* memory_block, Memory_Manager* manager);
```

### Emptying the the Memory Manager
This function cleans up and all of the memory and destroys it all in a way that leaves no memory leaks.

```c
int free_memory(Memory_Manager);
```

## Performance
A first fit Memory Manager will finish allocating quicker, however may run out of space quicker than a best fit Memory Manager. 