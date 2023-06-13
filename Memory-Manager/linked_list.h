/*
 * LINKED_LIST.H
 *
 * This file is part of the CSC430 Test Project.
 *   https://github.com/prof-tallman/test)
 *   Copyright (c) 2021
 *   Concordia CSC430
 *    Kevin Alonso
 *    Ali Amin
 *    Luke Frisbee
 *    Alex McCune
 *    Joshua Tallman
 *    Yunhu Xiang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

// Linked list node structure
typedef struct _node {
    struct _node* next;
    struct _node* prev;
    void* data;
    int size;
} node;

// Linked list structure
typedef struct {
    node* head;
    node* tail;
    int count;
} list;

/*
 * Returns a pointer to a new Linked List structure allocated on the heap
 *
 * -=| Params |=-
 *   None
 *
 * -=| Returns |=-
 *   type:    list*
 *   success: pointer to the newly created list
 *   failure: NULL
 */
list* CreateList();

/*
 * Returns a pointer to a new Linked List structure allocated on the heap
 *
 * -=| Params |=-
 *   my_list:               pointer to the linked-list to be destroyed
 *   data_cleanup_function: deallocation function to cleanup each node's buffer
 *                          pass NULL if the buffer should not be deallocated
 *
 * -=| Returns |=-
 *   None
 */
void DestroyList(list** my_list, void (*data_cleanup_function)());

/*
 * Appends a new node to the tail of a Linked List
 *
 * -=| Params |=-
 *   my_list: the linked-list that the new node will be appended to
 *   value:   data that the new node will hold
 *   size:    number of bytes that data consumes
 *
 * -=| Returns |=-
 *   type:    int
 *   success: EXIT_SUCCESS
 *   failure: EXIT_FAILURE
 */
int AppendValue(list* my_list, void* value, int size);

/*
 * Inserts a node one instance behind the target node. If the list is empty,
 * a new node is added as the head of the list.
 *
 * -=| Params |=-
 *   my_list: Linked List that is to be modified
 *   target:  Value of node that will have this new value inserted before it
 *   value:   The value of the new node
 *   size:    The size of the new node
 *
 * -=| Returns |=-
 *   type:    int
 *   success: EXIT_SUCCESS
 *   failure: EXIT_FAILURE
 */
int InsertBefore(list* my_list, void* target, void* value, int size);

/*
 * Inserts a node one instance after the target node. If the list is empty,
 * a new node is added as the head of the list.
 *
 * -=| Params |=-
 *   my_list: Linked List that is to be modified
 *   target:  Value of node that will have this new value inserted after it
 *   value:   The value of the new node
 *   size:    The size of the new node
 *
 * -=| Returns |=-
 *   type:    int
 *   success: EXIT_SUCCESS
 *   failure: EXIT_FAILURE
 */
int InsertAfter(list* my_list, void* target, void* value, int size);

/*
 * Searches through the list for the first node containing the target data.
 *
 * -=| Params |=-
 *   my_list: Linked List to operate on
 *   target:  The data value we are searching for
 *
 * -=| Returns |=-
 *   success: Pointer to the target node
 *   failure: NULL
 */
node* FindValue(list* my_list, void* target);

/*
 * Unlinks a node from the list and returns a pointer to the node's data. The
 * node is freed but the node's data is unchanged.
 *
 * -=| Params |=-
 *   my_list = linked list to operate on
 *   target  = Data address of the node to be removed
 *
 * -=| Returns |=-
 *   success = pointer to the unlinked node's data
 *   fail    = NULL
 */
void* RemoveValue(list* my_list, void* target);

/*
 * Sorts List in ascending order using MergeSort algorithm
 *
 * -=| Params |=-
 *   my_list: the Linked List to be sorted
 *
 * -=| Returns |=-
 *   None
 */

void Sort(list* my_list);

/*
 * Prints the location and value of a single Linked List node
 *
 * -=| Params |=-
 *   my_list: the Linked List to be printed
 *
 * -=| Returns |=-
 *   None
 */
void PrintList(list* my_list);

/*
 * Prints the location and value of a single Linked List node
 *
 * -=| Params |=-
 *   my_node: the Linked List node to be printed
 *
 * -=| Returns |=-
 *   None
 */
void PrintNode(node* my_node);

#endif
