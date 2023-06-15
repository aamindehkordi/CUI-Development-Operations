#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"
#include "memory_manager.h"

/*
 * Initializes a new memory manager with a specified amount of RAM
 * and a specified fit type.
 *
 * -=| Params |=-
 *   RAM_size: Int representing how much memory is available for the memory manager
 *   type:     Int representing which fit type to use for the memory manager
*/
Memory_Manager *init_memory_space(int RAM_size, int type)
{
	int freeListCode = EXIT_FAILURE;
	//int busyListCode = EXIT_FAILURE;

	void *RAM_address = malloc(RAM_size);
	if (RAM_address == NULL)
	{
		return NULL;
	}

	Memory_Manager *newMemSpace = (Memory_Manager *)malloc(sizeof(Memory_Manager));
	if (newMemSpace != NULL)
	{
		newMemSpace->ram_space = RAM_address;

		list *free_list = CreateList();
		list *busy_list = CreateList();
		if (free_list == NULL)
		{
			return NULL;
		}

		if (busy_list == NULL)
		{
			return NULL;
		}

		freeListCode = AppendValue(free_list, RAM_address, RAM_size);
		if (freeListCode == EXIT_SUCCESS)
		{
			printf("Free List initialized successfully.\n");
			newMemSpace->free_pointer = free_list;
			newMemSpace->busy_pointer = busy_list;
		}
		else
		{
			printf("Failed to initialize Free List.\n");
		}

		newMemSpace->fit_type = type;
	}

	return newMemSpace;
}

/*
 * Finds a block in the free list that fits the requested memory size from the user
 * then places that block from the free list onto the busy list.
 *
 * -=| Params |=-
 *   memSize:  Int representing how much memory is required for process
 *   manager:  The Memory manger we are using to evaluate which processes are free or not
 */
void *allocate_memory(int memSize, Memory_Manager *manager)
{
	node *curr = manager->free_pointer->head;
	int count = 0;

	//First-Fit
	if (manager->fit_type == FIRST_FIT)
	{
		//step through and find a value
		while (curr != NULL && curr->size < memSize)
		{
			curr = curr->next;
		}
	}
	//Best-Fit
	else if (manager->fit_type == BEST_FIT)
	{
		//Create temporary variable
		node *temp = NULL;
		//step through the whole list
		while (curr != NULL)
		{
			//If the current node is big enough but is still smaller than the temprary node
			if (curr->size >= memSize && (temp == NULL || curr->size < temp->size))
			{
				temp = curr;
				count++;
			}

			curr = curr->next;
		}
		curr = temp;
		temp = NULL;
	}
	//end of list and no available slot is free
	if (curr == NULL)
	{
		printf("Not enough memory for process :(\n");
        return NULL;
	}

    //Pointers for the addresses for the busy list and free list node
    void *pFullBlock = curr->data;
    void *pRemainderBlock = (char *)(curr->data) + memSize;

    //int values to store the memory sizes for the busy lsit and free list node
    int fullBlockMem = memSize;
    int remainderBlockSize = curr->size - memSize;

	//found a compatible slot
	//add it to the busy list after the tail...
	if (curr->size >= memSize)
	{
		//update allocated nodes memory size and attach it to the free list
		AppendValue(manager->busy_pointer, pFullBlock, fullBlockMem);

		RemoveValue(manager->free_pointer, curr->data);

		//as long as there is leftover memory, insert freenode right before where curr's location is.
		if (remainderBlockSize > 0)
		{
			AppendValue(manager->free_pointer, pRemainderBlock, remainderBlockSize);
		}
	}

    return pFullBlock;
}

void combine_memory(list* free_pointer);
// node* combine_memory_sorted(node* memory, list* free_pointer);

/*
 * Removes specified memory block in the busy list
 * then places that block from the busy list onto the busy list.
 * Afterwards combines memory blocks of the free list if their
 * adresses are located next to one another.
 *
 * -=| Params |=-
 *   memory_block: Data pointer of memory node to be deleted.
 *   manager: The Memory manger we wish to delete a memory block from.
 */
int eliminate_memory(void* memory_block, Memory_Manager *manager)
{
	// Get Memo
	node* memory = FindValue(manager->busy_pointer, memory_block);
	RemoveValue(manager->busy_pointer, memory_block);

	AppendValue(manager->free_pointer, memory->data, memory->size);
	Sort(manager->free_pointer);
	combine_memory(manager->free_pointer);

	// OLD code for faster alogirthm, although doesn't work without properly sorting free list
	//memory = FindValue(manager->free_pointer, memory_block);
	//node* freeMemory = combine_memory(memory, manager->free_pointer);
	//AppendValue(manager->free_pointer, freeMemory->data, freeMemory->size);
	//free(freeMemory);

	return EXIT_SUCCESS;
}

void combine_memory(list* free_pointer)
{
	node* result = NULL;
	node* slow = free_pointer->head;
	node* fast = free_pointer->head->next;

	// Unfortunately this is O(^x) for each node we're combining
	// This works, but we can make a MUCH quicker algorithm
	while(slow != NULL)
	{
		while(fast != NULL)
		{
			if(slow->data + slow->size == fast->data || slow->data == fast->data + fast->size)
			{
				if (slow->data < fast->data)
				{
					result = slow;
					result->size += fast->size;
				}
				else
				{
					result = fast;
					result->size += slow->size;
				}
				RemoveValue(free_pointer, slow->data);
				RemoveValue(free_pointer, fast->data);
				AppendValue(free_pointer, result->data, result->size);
				combine_memory(free_pointer);
				return;
			}
			fast = fast->next;
		}
		slow = slow->next;
	}
	return;
}

// FASTER ALGORITHM, REQUIRES FREE LIST TO BE SORTED
// node* combine_memory_sorted(node* memory, list* free_pointer)
// {
// 	while(memory->prev != NULL)
// 	{
// 		if(memory->data == memory->prev->data + memory->prev->size)
// 			memory = memory->prev;
// 		else
// 			break;
// 	}

// 	node* result = malloc(sizeof(node));
// 	result->data = memory->data;
// 	result->size = memory->size;

// 	while(memory->next != NULL)
// 	{
// 		if(memory->data + memory->size == memory->next->data)
// 		{
// 			result->size += memory->next->size;
// 			node* temp = memory->next;
// 			//RemoveValue(free_pointer, memory->data);
// 			memory = temp;
// 		}
// 		else
// 		{
// 			break;
// 		}
// 	}

// 	return result;
// }

/*
 * Frees the memory in ram_space buffer, busy list and free list.
 *
 * -=| Params |=-
 *   usedSpace: The memory manager we want to clean up.
 */

int free_memory(Memory_Manager* usedSpace)
{
	list* freeList = usedSpace->free_pointer;
	list* busyList = usedSpace->busy_pointer;

    //destory free list and busy list
	DestroyList(&freeList, NULL);
	DestroyList(&busyList, NULL);

    //free the memory in ram_space
	free(usedSpace->ram_space);
    free(usedSpace);

    //there is no way for the function to fail
    return EXIT_SUCCESS;
}
