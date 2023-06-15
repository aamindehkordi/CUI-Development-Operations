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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// All structures and function prototypes are defined in here
#include "linked_list.h"


/******************************************************************************
**                                CreateList                                 **
******************************************************************************/

list* CreateList()
{
    list* my_list = (list*)malloc(sizeof(list));
    if (my_list != NULL)
    {
        my_list->head = NULL;
        my_list->tail = NULL;
        my_list->count = 0;
    }
    return my_list;
}

/******************************************************************************
**                               DestroyList                                 **
******************************************************************************/

void DestroyList(list** my_list, void (*data_cleanup_function)())
{
    if (*my_list != NULL)
    {
        node* curr = (*my_list)->head;
        while(curr != NULL)
        {           
            // move on to the next node *before* destroying this node,
            // ...otherwise we lose our pointer to the next one
            node* to_destroy = curr;
            curr = curr->next;

            // now it's time to destroy this node
            if (data_cleanup_function != NULL)
            {
                data_cleanup_function(to_destroy->data);
            }            
            to_destroy->prev = NULL;
            to_destroy->next = NULL;
            free(to_destroy);
        }
        
        (*my_list)->head = NULL;
        (*my_list)->tail = NULL;
        (*my_list)->count = 0;
        (*my_list) = NULL;
    }
}

/******************************************************************************
**                               AppendValue                                 **
******************************************************************************/

int AppendValue(list* my_list, void* value, int size)
{
    if (my_list == NULL)
    {
        return EXIT_FAILURE;
    }

    node* curr = (node*)malloc(sizeof(node));
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

/******************************************************************************
**                                FindValue                                  **
******************************************************************************/

node* FindValue(list* my_list, void* target)
{
    if (my_list == NULL)
    {
        return NULL;
    }

    node* finder = my_list->head;
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

/******************************************************************************
**                               InsertAfter                                 **
******************************************************************************/

int InsertAfter(list* my_list, void* target, void* data, int size)
{
    if (my_list == NULL)
    {
        return EXIT_FAILURE;
    }

    if (my_list->count == 0)
    {
        return AppendValue(my_list, data, size);
    }

    //node that we are going to insert a new node after.
    node* targetNode = FindValue(my_list, target);
    if (targetNode == NULL)
    {
        return EXIT_FAILURE;
    }

    //make a new node to insert after
    node* insertedNode = (node*)malloc(sizeof(node));
    if (insertedNode == NULL)
    {
        return EXIT_FAILURE;
    }

    insertedNode->data = data;
    insertedNode->size = size;

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
        node* _next = targetNode->next;
        if (targetNode->next != NULL)
        {
            _next->prev = insertedNode;
        }
        targetNode->next = insertedNode;
    }

    //incrase the list count as we have inserted a new node
    my_list->count++;
    return EXIT_SUCCESS;
}

/******************************************************************************
**                              InsertBefore                                 **
******************************************************************************/

int InsertBefore(list* my_list, void* target, void* data, int size)
{
    if (my_list == NULL)
    {
        return EXIT_FAILURE;
    }

    if (my_list->count == 0)
    {
        return AppendValue(my_list, data, size);
    }

    node* targetNode = FindValue(my_list, target);
    if(targetNode == NULL)
    {
        return EXIT_FAILURE;
    }

    node* insertedNode = (node*)malloc(sizeof(node));
    if (insertedNode == NULL)
    {
        return EXIT_FAILURE;
    }

    insertedNode->data = data;
    insertedNode->size = size;

    if (targetNode == my_list->head)
    {
        my_list->head->prev = insertedNode;
        insertedNode->next = my_list->head;
        insertedNode->prev = NULL;

        my_list->head = insertedNode;
    }

    // somewhere in the middle
    else
    {
        insertedNode->next = targetNode;
        insertedNode->prev = targetNode->prev;

        node* _prev = targetNode->prev;
        if (_prev != NULL)
        {
            _prev->next = insertedNode;
        }
        targetNode->prev = insertedNode;
    }

    my_list->count++;
    return EXIT_SUCCESS;
}

/******************************************************************************
**                              RemoveValue                                  **
******************************************************************************/

void* RemoveValue(list* my_list, void* target)
{
    if (my_list == NULL)
    {
        return NULL;
    }

    node* targetNode = FindValue(my_list, target);
    if (targetNode == NULL)
    {
        return NULL;
    }
    void* data = targetNode->data;

    //if there's only one element in the list
    if (my_list->count == 1)
    {
        my_list->head = NULL;
        my_list->tail = NULL;
    }
    else
    {
        //delete head
        if (my_list->head == targetNode)
        {
            my_list->head = my_list->head->next;
            my_list->head->prev = NULL;
        }
        //delete tail
        else if (my_list->tail == targetNode)
        {
            my_list->tail = my_list->tail->prev;
            my_list->tail->next = NULL;
        }
        //delete in the middle
        else
        {
            node* _prev = targetNode->prev;
            node* _next = targetNode->next;
            _prev->next = targetNode->next;
            _next->prev = targetNode->prev;
        }
    }

    //unlink target node
    targetNode->next = NULL;
    targetNode->prev = NULL;
    free(targetNode);
    my_list->count--;
    return data;
}

/******************************************************************************
**                               PrintNode                                   **
******************************************************************************/

void PrintNode(node* my_node)
{
    // show the address even if this is a bad pointer
    printf("Addr: 0x%p\n", my_node);
    if (my_node == NULL)
    {
        return;
    }

    char buffer[61] = { 0 };

    // if the data is a printable string, it's string length should be the
    // same as it's size
    if (strlen(my_node->data)+1 == my_node->size)
    {
        // this node holds a string... print it but hold the line to 80 chars
        if (my_node->size < 60)
        {
            sprintf(buffer, "%s", (char*)my_node->data);
        }
        else
        {
            strncpy(buffer, my_node->data, 45);
            strcat(buffer, "...");
            strcat(buffer, my_node->data + my_node->size - 12);
        }
    }
    else
    {
        // this is not printable data, hex dump the first 20 bytes
        // if we printed any more, it would take more than a single line
        int max_bytes_to_print = sizeof(buffer) / 3;
        int the_bytes_to_print = 0;
        if (my_node->size > max_bytes_to_print)
        {
            the_bytes_to_print = max_bytes_to_print;
        }
        else
        {
            the_bytes_to_print = my_node->size;
        }

        for(int i = 0; i < the_bytes_to_print; i++)
        {
            char byte_string[4];
            unsigned char* byte_ptr = (unsigned char*)my_node->data + i;
            sprintf(byte_string, "%02x ", byte_ptr[0]);
            strcat(buffer, byte_string);
        }
    }

    printf("Data: 0x%p: %s\n", my_node->data, buffer);
    printf("Size: %d\n", my_node->size);
    printf("Next: 0x%p\n", my_node->next);
    printf("Prev: 0x%p\n", my_node->prev);
}

/******************************************************************************
**                               PrintList                                   **
******************************************************************************/

void PrintList(list *my_list)
{
    // dump the actual Linked List header
    printf("  -=| Linked List |=-\n");
    printf("-----------------------\n");
    printf("| Address: 0x%p |\n", my_list);
    if (my_list == NULL)
    {
        printf("-----------------------\n");
    }
    else
    {
        printf("| Count:   %10d |\n", my_list->count);
        printf("| Head:    0x%p |\n", my_list->head);
        printf("| Tail:    0x%p |\n", my_list->tail);
        printf("-----------------------\n");

        // step through the list and print each node 1-by-1
        node* curr = my_list->head;
        while (curr != NULL)
        {
            PrintNode(curr);
            printf("----------------\n");
            curr = curr->next;
        }
    }
}

/******************************************************************************
**                                 Sort                                      **
******************************************************************************/

void MergeSort(node** headPointer);
node* Merge(node* l, node* r);
void Split(node* head, node** front, node** back);

void Sort(list* my_list)
{
    if (my_list == NULL)
    {
        return;
    }

    MergeSort(&my_list->head);
    my_list->head->prev = NULL;
    while(my_list->tail->next != NULL)
    {
        my_list->tail = my_list->tail->next;
    }
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
        result->next->prev = result;
    }
    else
    {
        result = r;
        result->next = Merge(l, r->next);
        result->next->prev = result;
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

/******************************************************************************
**                             END OF FILE                                   **
******************************************************************************/

