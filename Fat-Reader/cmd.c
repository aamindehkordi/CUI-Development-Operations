#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "reader.h"
#include "helper.h"
#include "cmd.h"
#include <stdio.h>

static char dirListBuffer[256];

/******************************************************************************
**                                 shellLoop                                 **
******************************************************************************/

void shellLoop()
{
    dirListBuffer[0] = '/';

    while (1)
    {
        char cmd[60];
        const char s[2] = " ";
        char* token;

        printf("> ");
        if (fgets(cmd, 60, stdin) != NULL) // read command
        {
            //lowercase the command
            for (int i = 0; cmd[i]; i++)
            {
                cmd[i] = tolower(cmd[i]);
            }

            int index = strcspn(cmd, "\r\n");
            cmd[index] = '\0';
            //The first token is before the first space
            token = strtok(cmd, s);

            if (token == NULL)
            {
                continue;
            }
            RemoveTrailingSpaces(token);
            if (strlen(token) == 0)
            {
                continue;
            }

            //LS Command
            else if (strcmp(token, "ls") == 0)
            {
                ls();
            }
            
            //PWD command
            else if (strcmp(token, "pwd") == 0)
            {
                pwd();
            }

            //CAT Command
            else if (strcmp(token, "cat") == 0)
            {
                token = strtok(NULL, s);
                printf("'%s'\n", token);
                cat(token);
            }

            //CD command
            else if (strcmp(token, "cd") == 0)
            {
                token = strtok(NULL, s);
                cd(token);
            }

            //Close the Shell Loop
            else if (strcmp(token, "exit") == 0)
            {
                return;
            }

            else
            {
                printf("Error: Unrecognized Command");
            }
        }
        else
        {
            printf("fgets failed.");
        }
    }
}

/******************************************************************************
**                                    PWD                                    **
******************************************************************************/

void pwd()
{
    printf("%s\n", dirListBuffer);
}

/******************************************************************************
**                                     LS                                    **
******************************************************************************/

void ls()
{
    //strcpy(dirListBuffer, "/2-DIR-01");

    //make a pointer entryToList and equal it to NULL
    ROOT_DIR* dirToList = NULL;
    uint32_t size = 0;

    //root of the drive
    if(strcmp(dirListBuffer, "/") == 0)
    {
        dirToList = g_rootDir;
        size = g_fatBoot -> fat_root_directory_entries * sizeof(ROOT_ENTRY);
    }
    else
    {
        ROOT_ENTRY* entryToList = NULL;
        entryToList = GetRootEntry(dirListBuffer);
        size = GetFileSizeFromEntry(entryToList);

        dirToList = malloc(size);
        ReadFileContents(entryToList, (char*)dirToList, size);
    }

    //step through root dir one entry at a time
    ROOT_ENTRY* curr = (ROOT_ENTRY*) dirToList;
    while(curr->filename[0] != '\0')
    {
      const char* filename = EightDotThreeString(curr -> filename, curr -> file_exetension);
      uint32_t filesize = curr->file_size;

      if((curr-> file_attribute & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY  )
      {
        //prints out DIR
         printf("%-12s DIR\n", filename);
      }

      else if((curr-> file_attribute & FILE_ATTRIBUTE_LFN ) == FILE_ATTRIBUTE_LFN )
      {
          //printf("longfilename\n");
      }
      else
      {
          //Prints out filename
          printf("%-12s %d\n", filename, filesize);

      }

      //move on to next entry
      curr++;
    }
}

/******************************************************************************
**                                    CAT                                    **
******************************************************************************/

void cat(char* file_path)
{
    char* filename = malloc(256);
    //Local Directory
    if(file_path[0] != '/')
    {   //The last paramater is not the size of the source.

        strncpy(filename, dirListBuffer, 256);
        strncat(filename, "/", 256-strlen(filename)-1);
        strncat(filename, file_path, 256-strlen(filename)-1);
    }
    //Located Elsewhere
    else
    {
        strncpy(filename, file_path, 256);
    }
    int size = GetFileSize(filename);
    if(size == 0)
    {
        return;
    }
    char* buffer = GetFileData(filename);

    //Cat the file
    HexDump(buffer, size);

    //Maintenance
    free(filename);
    free(buffer);

}

/******************************************************************************
**                                     CD                                    **
******************************************************************************/

void cd(char *path)
{
    if (path == NULL)
    {
        dirListBuffer[0] = '/';
        return;
    }

    RemoveTrailingSpaces(path);
    if (strlen(path) == 0)
    {
        dirListBuffer[0] = '/';
        return;
    }

    //Allocate a char* for the path the user might give (at most 256 chars)
    char buffer[256];

    //Go up Directory
    if (strcmp(path, "..") == 0)
    {
        char* last_slash = NULL;
        // get rid of the trailing /
        last_slash = strrchr(dirListBuffer, '/');
        last_slash[0] = '\0';
        // get rid of the child directory
        last_slash = strrchr(dirListBuffer, '/');
        last_slash[1] = '\0';
    }
    //Going down a certian amount of directories
    else
    {
        strncpy(buffer, dirListBuffer, 256);
        strncat(buffer, path, 256-strlen(buffer)-1);

        //Check to make sure the directory path exists before appending to buffer
        if (GetRootEntry(buffer) != NULL)
        {
            strncpy(dirListBuffer, buffer, 256);
            strncat(dirListBuffer, "/", 256-strlen(buffer)-1);
        }
        else
        {
            printf("'%s' is not a valid directory path\n", path);
        }
    }
}