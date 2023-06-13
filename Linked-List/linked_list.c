/*
 * LINKED_LIST.C
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

#include <stdio.h>
#include <stdlib.h>

// All structures and function prototypes are defined in here
#include "linked_list.h"

void MergeSort(node** headPointer);
node* Merge(node* l, node* r);
void Split(node* head, node** front, node** back);


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
list *CreateList()
{
    list *my_list = (list *)malloc(sizeof(list));
    if (my_list != NULL)
    {
        my_list->head = NULL;
        my_list->tail = NULL;
        my_list->count = 0;
    }
    return my_list;
}

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
int AppendValue(list *my_list, void *value, int size)
{
    node *curr = (node *)malloc(sizeof(node));
    if (curr == NULL)
    {
        return EXIT_FAILURE;
    }

    curr->data = value;
    curr->size = size;
    curr->next = NULL;
    curr->prev = NULL;

    if (my_list->count == 0)
    {
        my_list->head = curr;
        my_list->tail = curr;
        my_list->count = 1;
    }
    else
    {
        // nodes set the forward and reverse pointers
        my_list->tail->next = curr;
        curr->prev = my_list->tail;

        // list: set the new tail and increment count
        my_list->tail = curr;
        my_list->count++;
    }

    return EXIT_SUCCESS;
}

/*
 * Searches through the Linked List for the first node containing the target data.
 *
 * -=| Params |=-
 *   my_list = linked list to operate on
 *   target  = the data value we are searching for
 *
 * -=| Returns |=-
 *   success = pointer to the target node
 *   fail    = NULL
 */
node *FindValue(list *my_list, void *target)
{
    node *finder = my_list->head;
    while (finder != NULL)
    {
        if (finder->data == target)
        {
            return finder;
        }
        finder = finder->next;
    }
    return NULL;
}

/*
 * Creates a new node and insert's it after desired target value node.
 *
 * -=| Params |=-
 *   my_list = linked list to operate on
 *   target  = enumeartes the list until node posession value of target is found with FindValue()
 *   data    = value to fill new node with
 *   size    = number of bytes required for the data
 *
 * -=| Returns |=-
 *   success = EXIT_SUCCESS
 *   fail    = EXIT_FAIL
 */
int InsertAfter(list *my_list, void *target, void *data, int size)
{
    //node that we are going to insert a new node after.
    node *targetNode = FindValue(my_list, target);   
    if (targetNode == NULL)
    {
        return EXIT_FAILURE;
    }
    
    //make a new node to insert after
<<<<<<< HEAD
    node *insertedNode = (node *)malloc(sizeof(node));
=======
<<<<<<< HEAD
    node *insertedNode = (node*)malloc(sizeof(node));
=======
    node *insertedNode = (node *)malloc(sizeof(node));
>>>>>>> 9e29bdb7eae52bdc207d469a0592cf771f0bcbd7
>>>>>>> deb52310142ff9d73956aae4c994361d19972499
    if (insertedNode == NULL)
    {
        return EXIT_FAILURE;
    }
    insertedNode->data = data;
    insertedNode->size = size;
<<<<<<< HEAD
=======

    insertedNode->data = data;
    insertedNode->size = size;
>>>>>>> deb52310142ff9d73956aae4c994361d19972499

    //make a new node, give it the data of our desired info
    //if the last node in our list is the target...
    if (targetNode == my_list->tail)
    {
        //point the next node for the tail to the appended node
        //also point the new node to the tail 
        //also point tail's next to null, or else infinite print of 
        //the list occurs...
        my_list->tail->next = insertedNode;
        insertedNode->prev = my_list->tail;
        insertedNode->next = NULL;
       
        //appended node is now the tail update the list
        my_list->tail = insertedNode;
    }
    
    //any other node
    else
    {
        //make the new node point to the two other nodes
        //it is now wedged between
        insertedNode->next = targetNode->next;
        insertedNode->prev = targetNode;

        //make the nodes before and after the new node
        //point to it
        if (targetNode->next != NULL)
        {
            targetNode->next->prev = insertedNode;
        }
        targetNode->next = insertedNode;
    }

    //incrase the list count as we have inserted a new node
    my_list->count++;
    return EXIT_SUCCESS;    
}

/*
 * Inserts a node one instance behind the target node.
 *
 * -=| Params |=-
 *   my_list: The Linked List that is to be modified
     target: The node that will have another node inserted before it
     value: The value of the new node
     size: The size of the new node
 *
 * -=| Returns |=-
 *   type:    int
 *   success: EXIT_SUCCESS
 *   failure: EXIT_FAILURE
 */
int InsertBefore(list* my_list, void* target, void* value, int size)
{        
    node* curr = FindValue(my_list, target); 
    if(curr == NULL)
    {
        return EXIT_FAILURE;
<<<<<<< HEAD
    }
    
    node* insertedNode = (node*)malloc(sizeof(node));
    if (insertedNode == NULL)
    {
        return EXIT_FAILURE;
    }

    insertedNode->data = value;
    insertedNode->size = size;
    if (insertedNode == my_list->head)
    {
        insertedNode->next = my_list->head;
        insertedNode->prev = NULL;
        my_list->head->prev = insertedNode;
        my_list->head = insertedNode;
    }
    
    // somewhere in the middle
    else
    {
        insertedNode->next = curr;
        insertedNode->prev = curr->prev;
        node* _prev = curr->prev;
        _prev->next = insertedNode;
        node* _next = curr->next;
        _next->prev = insertedNode;
=======
>>>>>>> deb52310142ff9d73956aae4c994361d19972499
    }
    
    node* insertedNode = (node*)malloc(sizeof(node));
    if (insertedNode == NULL)
    {
        return EXIT_FAILURE;
    }

    insertedNode->data = value;
    insertedNode->size = size;
<<<<<<< HEAD

=======
>>>>>>> 9e29bdb7eae52bdc207d469a0592cf771f0bcbd7
    if (insertedNode == my_list->head)
    {
        insertedNode->next = my_list->head;
        insertedNode->prev = NULL;
        my_list->head->prev = insertedNode;
        my_list->head = insertedNode;
    }
<<<<<<< HEAD
=======
    
>>>>>>> 9e29bdb7eae52bdc207d469a0592cf771f0bcbd7
    // somewhere in the middle
    else
    {
        insertedNode->next = curr;
        insertedNode->prev = curr->prev;
        node* _prev = curr->prev;
        _prev->next = insertedNode;
        node* _next = curr->next;
        _next->prev = insertedNode;
    }

    my_list->count++;
    return EXIT_SUCCESS;
}

/*
 * Unlinks a node from the list but does not actually free the memory.
 *
 * -=| Params |=-
 *   my_list = linked list to operate on
 *   target  = enumeartes the list until node posession value of target is found with FindValue()
 *
 * -=| Returns |=-
 *   success = pointer to the unlinked node
 *   fail    = NULL
 */
node *RemoveValue(list *my_list, void *target)
{
    node *targ_node = FindValue(my_list, target);
    //if target is not found
    if (targ_node == NULL)
    {
        return NULL;
    }
    //if there's only one element in the list
    if (my_list->count == 1)
    {
        my_list->head = NULL;
        my_list->tail = NULL;
    }
    else
    {
        //delete head
        if (my_list->head == targ_node)
        {
            my_list->head = my_list->head->next;
            my_list->head->prev = NULL;
        }
        //delete tail
        else if (my_list->tail == targ_node)
        {
            my_list->tail = my_list->tail->prev;
            my_list->tail->next = NULL;
        }
        //delete in the middle
        else
        {
            node *targ_prev = targ_node->prev;
            node *targ_next = targ_node->next;
            targ_prev->next = targ_node->next;
            targ_next->prev = targ_node->prev;
        }
    }
    //unlink target node
    targ_node->next = NULL;
    targ_node->prev = NULL;
    my_list->count--;
    return targ_node;
}

/*
 * Prints the location and value of a single Linked List node
 *
 * -=| Params |=-
 *   my_node: the Linked List node to be printed
 *
 * -=| Returns |=-
 *   None
 */
void PrintNode(node *my_node)
{
    // show the address even if this is a bad pointer
    printf("Addr: 0x%08x\n", (unsigned int)my_node);
    if (my_node != NULL)
    {
        printf("Prev: 0x%08x\n", (unsigned int)my_node->prev);
        printf("Data: 0x%08x\n", (unsigned int)my_node->data);
        printf("Size: %d\n", my_node->size);
        printf("Next: 0x%08x\n", (unsigned int)my_node->next);
    }
}

/*
 * Prints the location and value of a single Linked List node
 *
 * -=| Params |=-
 *   my_list: the Linked List to be printed
 *
 * -=| Returns |=-
 *   None
 */
void PrintList(list *my_list)
{
    // dump the actual Linked List header
    printf("  -=| Linked List |=-\n");
    printf("-----------------------\n");
    printf("| Address: 0x%08x |\n", (unsigned int)my_list);
    if (my_list == NULL || my_list->count == 0)
    {
        printf("-----------------------\n");
    }
    else
    {
        printf("| Count:   %10d |\n", my_list->count);
        printf("| Head:    0x%08x |\n", (unsigned int)my_list->head);
        printf("| Tail:    0x%08x |\n", (unsigned int)my_list->tail);
        printf("-----------------------\n");

        // step through the list and print each node 1-by-1
        node *curr = my_list->head;
        while (curr != NULL)
        {
            PrintNode(curr);
            printf("----------------\n");
            curr = curr->next;
        }
    }
}

/*
 * Sorts List in ascending order using MergeSort algorithm
 *
 * -=| Params |=-
 *   my_list: the Linked List to be sorted
 *
 * -=| Returns |=-
 *   None
 */
void Sort(list* my_list)
{
    MergeSort(&my_list->head);
}

void MergeSort(node** headPointer)
{
    node* head = *headPointer;
    node* l;
    node* r;

    // List must have more than 1 item to sort
    if (head == NULL || head->next == NULL) 
    {
        return;
    }

    // Split left and right sublists
    Split(head, &l, &r);

    // Sort recursively using sublists
    MergeSort(&l);
    MergeSort(&r);

    *headPointer = Merge(l, r);
}

node* Merge(node* l, node* r)
{
    node* result = NULL;

    // If one node pointer is NULL, return the other
    if (l == NULL)
        return (r);
    else if (r == NULL)
        return (l);

    // Pick smaller sublist, then continue recusively
    if (l->data <= r->data) 
    {
        result = l;
        result->next = Merge(l->next, r);
    }
    else 
    {
        result = r;
        result->next = Merge(l, r->next);
    }

    return (result);
}

void Split(node* head, node** front, node** back)
{
    node* quick;
    quick = head->next;

    node* slow;
    slow = head;

    // Split using quick and slow node pointers.
    while (quick != NULL) 
    {
        quick = quick->next;
        if (quick != NULL) 
        {
            slow = slow->next;
            quick = quick->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}