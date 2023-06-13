/*
 * TEST_PROGRAM.C
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
#include "linked_list.h"

char* str1 = "Data A";
char* str2 = "Data B2";
char* str3 = "Data C3#";
char* str4 = "Data D4#";

int main(int argc, char* argv[])
{
    // literal strings cannot be freed, we must create a copy on the heap
    char* data1 = (char*)malloc(strlen(str1)+1);
    char* data2 = (char*)malloc(strlen(str2)+1);
    char* data3 = (char*)malloc(strlen(str3)+1);
    int* data4 = (int*)malloc(sizeof(int));
    int* data5 = (int*)malloc(sizeof(int));
    int* data6 = (int*)malloc(sizeof(int));    
    strcpy(data1, str1);
    strcpy(data2, str2);
    strcpy(data3, str3);
    *data4 = 21;
    *data5 = 1000000;
    *data6 = 40;

    // create a test Linked List with three nodes
    list* my_list = CreateList();
    AppendValue(my_list, data1, strlen(data1)+1);
    AppendValue(my_list, data2, strlen(data2)+1);
    AppendValue(my_list, data3, strlen(data3)+1);

<<<<<<< HEAD
=======
<<<<<<< HEAD
    //InsertBefore(my_list, data1, str4, sizeof(char*));
    InsertAfter(my_list, data1, str4, sizeof(char*));

=======
>>>>>>> 9e29bdb7eae52bdc207d469a0592cf771f0bcbd7
>>>>>>> deb52310142ff9d73956aae4c994361d19972499
    node* found_target = FindValue(my_list, data2);

     if (found_target == NULL)
     {
         printf("Target not found\n");
     }
    
    // else
    // {
    //     printf("Success, you found your target 0x%08x\n", found_target);
    // }

    //test of InsertAfter()
    //Not sure how to actually use the size parameter....
    //probably using it wrong
<<<<<<< HEAD
    InsertAfter(my_list, data2, data4, sizeof(int));
    InsertAfter(my_list, data4, data5, sizeof(int));
    InsertAfter(my_list, data3, data6, sizeof(int));
=======
<<<<<<< HEAD
    // InsertAfter(my_list, data2, data4, sizeof(int));
    // InsertAfter(my_list, data4, data5, sizeof(int));
    // InsertAfter(my_list, data3, data6, sizeof(int));
=======
    InsertAfter(my_list, data2, data4, sizeof(int));
    InsertAfter(my_list, data4, data5, sizeof(int));
    InsertAfter(my_list, data3, data6, sizeof(int));
>>>>>>> 9e29bdb7eae52bdc207d469a0592cf771f0bcbd7
>>>>>>> deb52310142ff9d73956aae4c994361d19972499

    // Display the list
    printf("\n");
    PrintList(my_list);
    printf("\n");
    
    // Sort then display
    Sort(my_list);
    printf("\n");
    PrintList(my_list);
    printf("\n");

    // no cleanup, this is bad code... memory released on process termination
    return EXIT_SUCCESS;
}
