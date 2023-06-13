# LinkedList
A project to teach us the C language and practice working together as a team

## Design Document

Lead: Prof. Tallman

Date: Jan 13, 2021

Team: 
* Kevin Alonso
* Ali Amin
* Luke Frisbee
* Alex McCune
* Yunhu Xiang

### Structures

The linked list library requires two structures:
```c
typedef struct _node
{
    typedef struct _node* next;
    typedef struct _node* prev;
    void* data
    int size;
} node;
```
```c
typedef struct _list
{
    node* head;
    node* tail;
    int count;
} list;
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

- [x] [Joshua Tallman](mailto:joshua.tallman@cui.edu) `list* CreateList()`: Allocates a new linked list structure.
- [x] [Joshua Tallman](mailto:joshua.tallman@cui.edu) `int AppendValue(list* my_list, void* value, int size)`: Allocates and appends a new node to the end of the linked list; node has given `value` and `size`.
- [x] [Kevin Alonso](mailto:kevin.alonso@eagles.cui.edu) `node* FindValue(list* my_list, void* target)`: Searches the `my_list` and returns a pointer to the first node containing `target`; returns `NULL` if `target` does not exist in `my_list`.
- [x] [Ali Amin](mailto:ali.amindehkordi@eagles.cui.edu) `int InsertBefore(list* my_list, void* target, void* value, void* size)`: Allocates and inserts a new node into `my_list` immediately before the first node that contains the value `target`; node has given `value` and `size`.
- [x] [Alex McCune](mailto:alexander.mccune@eagles.cui.edu) `int InsertAfter(list* my_list, void* target, void* value, void* size`: Allocates and inserts a new node into `my_list` immediately after the first node contains the value `target`; node has given `value` and `size`.
- [x] [Yunhu Xiang](mailto:yunhu.xiang@eagles.cui.edu) `node* RemoveValue(list* my_list, void* target)`: Finds the first node in `my_list` containing the value `target` and unlinks the node from the list; a pointer to the node is returned and it is up to the caller to deallocate any memory associated with this node; returns `NULL` if `target` does not exist in `my_list`.
- [x] [Luke Frisbee](mailto:luke.frisbee@eagles.cui.edu) `void Sort(list* my_list)`: Sorts all of the nodes in `my_list` in ascending order using the node's value as the sort key.
- [x] [Joshua Tallman](mailto:joshua.tallman@cui.edu) `void PrintList(list* my_list)`: Prints a full linked list (metadata and values)
- [x] [Joshua Tallman](mailto:joshua.tallman@cui.edu) `void PrintNode(node* my_node)`: Prints a single node in a linked list (metadata and values)
