#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "memory_manager.h"

int main(int argc, char *argv[])
{
	// Memory_Manager* FF_Space = init_memory_space(500, FIRST_FIT);
	//Allocate
	// void* memory1 = allocate_memory(40, FF_Space);
	// void* memory2 = allocate_memory(60, FF_Space);
	// void* memory3 = allocate_memory(100, FF_Space);
	// void* memory4 = allocate_memory(200, FF_Space);
	// void* memory5 = allocate_memory(95, FF_Space);

	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->busy_pointer);

	//free
	// eliminate_memory(memory1, FF_Space);
	// printf("\n~~~~~~~~~~~~~~~~~~first free~~~~~~~~~~~~~~~~~~~~~\n");
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->busy_pointer);

	// eliminate_memory(memory5, FF_Space);
	// printf("\n~~~~~~~~~~~~~~~~~~second free~~~~~~~~~~~~~~~~~~~~~\n");
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->busy_pointer);

	// eliminate_memory(memory2, FF_Space);
	// printf("\n~~~~~~~~~~~~~~~~~~third free~~~~~~~~~~~~~~~~~~~~~\n");
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->busy_pointer);

	// eliminate_memory(memory3, FF_Space);
	// eliminate_memory(memory4, FF_Space);    
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(FF_Space->busy_pointer);







	Memory_Manager* BF_Space = init_memory_space(500, BEST_FIT);

	//Allocate
	void* memory1 = allocate_memory(200, BF_Space);
	void* memory2 = allocate_memory(60, BF_Space);
	void* memory3 = allocate_memory(150, BF_Space);
	void* memory4 = allocate_memory(50, BF_Space);
	void* memory5 = allocate_memory(40, BF_Space);

	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->busy_pointer);

	//Free
	eliminate_memory(memory1, BF_Space);
	eliminate_memory(memory3, BF_Space);
	eliminate_memory(memory5, BF_Space);

	printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->free_pointer);
	printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->busy_pointer);

	//Allocate again
	void* memory6 = allocate_memory(30, BF_Space);
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->busy_pointer);

	void* memory7 = allocate_memory(100, BF_Space);
	// printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->free_pointer);
	// printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	// PrintList(BF_Space->busy_pointer);

	void* memory8 = allocate_memory(210, BF_Space);
	printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->free_pointer);
	printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->busy_pointer);

	eliminate_memory(memory2, BF_Space);
	eliminate_memory(memory4, BF_Space); 
	eliminate_memory(memory6, BF_Space);
	eliminate_memory(memory7, BF_Space); 

	printf("\n~~~~~~~~~~~~~~~~~~free~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->free_pointer);
	printf("\n~~~~~~~~~~~~~~~~~~busy~~~~~~~~~~~~~~~~~~~~~\n");
	PrintList(BF_Space->busy_pointer);

	free_memory(BF_Space);

	printf("\nTest Success\n");
}