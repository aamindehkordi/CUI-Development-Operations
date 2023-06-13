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

// Linked list functions
list* CreateList();
int AppendValue(list* my_list, void* value, int size);
int InsertBefore(list* my_list, void* target, void* value, int size);
int InsertAfter(list* my_list, void* target, void* value, int size);
node* FindValue(list* my_list, void* target);
node *RemoveValue(list *my_list, void *target);
void Sort(list* my_list);

// Output and debug functions
void PrintList(list* my_list);
void PrintNode(node* my_node);

#endif
