# LinkedList
A Linked List Library that stores arbitrarily sized and typed data. It was designed with a Heap-style Memory Manager in mind to store the heap's busy and free lists.

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
The source code is available at [https://github.com/prof-tallman/LinkedList](https://github.com/prof-tallman/LinkedList)

This project was written in `C` for the GCC compiler.
```
% gcc -c linked_list.c -o linked_list.o
```
Add this library to your project by including `linked_list.h` and linking to `linked_list.o`

A program has been included for testing.
```
% gcc linked_list.o test_program.c -o test.EXIT_SUCCESS
```

## Source Documentation
The linked list library is made from two data types: `list` and `node`.

### Creating Linked Lists
Create a linked list with the `CreateList` function. CreateList will allocate and return a pointer to a `list` structure.
```c
list* CreateList();
```

The linked list structure must be cleaned up manually using the `free` function.

#### The `list` Type
The `list` type is a structure that defines a linked list. It contains pointers to the front and back of the list. These pointers should not be modified outside of the linked list library. The type also includes an internal count than can be accessed to determine the number of items in the list.
```c
typedef struct _list
{
    node* head;
    node* tail;
    int count;
} list;
```

### Adding Nodes
Nodes can be allocated and added to the linked list by three functions `AppendValue`, `InsertBefore`, and `InsertAfter`. Nodes should not be created manually. Each of these functions takes a pointer to a `list` structure in addition to a data buffer that holds the data being added to the list. The *'Before* and *'After* functions also take a pointer to a target buffer. This target is the address of the buffer to be found in the node that comes before or after the new node.
```c
int AppendValue(list* my_list, void* value, int size);
int InsertBefore(list* my_list, void* target, void* value, int size);
int InsertAfter(list* my_list, void* target, void* value, int size);
```

Each of these functions will return `EXIT_SUCCESS` if the new node was added successfully and `EXIT_FAILURE` if the new node could not be added. On failure, there is no change to the linked list or to the data buffer. The caller **does not** need to cleanup any loitering list allocations but it **is** responsible for the original data buffer.

#### The `node` Type
The `node` type stores each individual item in the linked list. An item is stored as a generic `void*` buffer and size argument.
```c
typedef struct _node
{
    typedef struct _node* next;
    typedef struct _node* prev;
    void* data
    int size;
} node;
```

### Selecting Nodes
Nodes should be be accessed using the `FindValue` function. This search function takes the address of the buffer being searched for. It is optimized for memory managers that must maintain busy and free lists (memory manager operations are based on the address of the start of each block).
```c
node* FindValue(list* my_list, void* target)
```

### Removing Nodes
Nodes ***must*** be manually deallocated as the caller is responsible for cleaning up the memory that is stored within each node. The `RemoveValue` function will unlink the node from the linked list. After a node has been unlinked, the caller can free the generic `void*` buffer and must also free the node itself.
```c
node* RemoveValue(list* my_list, void* target)
```

### Sorting the Lists
Linked lists will be created with nodes arranged in the order that they were  added to the list. Not chronological ordering, but operational ordering based on the particular use of `AppendNode` and `InsertBefore` and `InsertAfter` operations.
The nodes can be sorted in ascending order using the `Sort` function. Sort will use the address of each node's buffer as its sorting key, so a node whose buffer is at address `0x12345678` will be placed before a node whose buffer is at address `0x90abcdef`.
```c
void Sort(list* my_list)
```

## Performance
Creating the list and appending nodes are both constant time O(1) operations. Inserting nodes, searching for values, and removing nodes take linear time O(n) time.

The library includes a linked list sorting function that will reorder the nodes in ascending order based on the *address* of the node's data buffer. The sort function was implemented with Merge Sort, which operates in linearithmic O(n log n) time.
