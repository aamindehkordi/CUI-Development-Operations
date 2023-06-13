#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "helper.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    (byte & 0x80 ? '1' : '0'),     \
        (byte & 0x40 ? '1' : '0'), \
        (byte & 0x20 ? '1' : '0'), \
        (byte & 0x10 ? '1' : '0'), \
        (byte & 0x08 ? '1' : '0'), \
        (byte & 0x04 ? '1' : '0'), \
        (byte & 0x02 ? '1' : '0'), \
        (byte & 0x01 ? '1' : '0')

/******************************************************************************
**                                FileAttributes                             **
******************************************************************************/

char* FileAttributes(uint8_t byte)
{
    char *bitchar = malloc(8 * sizeof(char));
    sprintf(bitchar, BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(byte));
    printf("%s", bitchar);

    char *result = malloc(80);
    strcat(result, "|");

    for (int i = 0; i < strlen(bitchar) - 1; i++)
    {
        if (bitchar[i] == '1')
        {
            switch (i)
            {
            case 0:
                strcat(result, "RO|"); //Read Only
                break;
            case 1:
                strcat(result, "H|"); //Hidden
                break;
            case 2:
                strcat(result, "S|"); //System
                break;
            case 3:
                strcat(result, "V|"); //Volume Label
                break;
            case 4:
                strcat(result, "Dir|"); //Directory
                break;
            case 5:
                strcat(result, "A|"); //Archive
                break;
            case 6:
                strcat(result, "D|"); //Device
                break;
            case 7:
                strcat(result, "R|"); //Reserved
                break;
            }
        }
        else
        {
            strcat(result, "*|");
        }
    }

    return result;
    free(bitchar);
}

/******************************************************************************
**                                 AsHumanSize                               **
******************************************************************************/

char* AsHumanSize(uint64_t bytes)
{
    static char str[20] = "";
    char *readable_string;
    float readable_num = 0;
    readable_num = bytes / 1024;
    if (readable_num <= 1024)
    {
        sprintf(str, "%.2f", readable_num);
        strcat(str, "B");
    }

    else if (readable_num > 1024 && readable_num < 1048576)
    {
        readable_num = readable_num / 1024;
        sprintf(str, "%.2f", readable_num);
        strcat(str, "MB");
    }

    else if (readable_num >= 1048576)
    {
        readable_num = readable_num / 1024;
        readable_num = readable_num / 1024;
        sprintf(str, "%.2f", readable_num);
        strcat(str, "GB");
    }
    readable_string = str;
    return readable_string;
}

/******************************************************************************
**                                  MediaType                                **
******************************************************************************/

char* MediaType(uint8_t byte)
{
    switch (byte)
    {
    case 0xE5:
        return "Floppy";
        break;
    case 0xED:
        return "Floppy";
        break;
    case 0xF0:
        return "Floppy";
        break;
    case 0xF5:
        return "Disk";
        break;
    case 0xF8:
        return "Disk";
        break;
    case 0xF9:
        return "Floppy";
        break;
    case 0xFA:
        return "Floppy";
        break;
    case 0xFB:
        return "Floppy";
        break;
    case 0xFC:
        return "Floppy";
        break;
    case 0xFD:
        return "Floppy";
        break;
    case 0xFE:
        return "Floppy";
        break;
    case 0xFF:
        return "Floppy";
        break;
    }
    return NULL;
}

/******************************************************************************
**                               PartitionTypeName                           **
******************************************************************************/

char* PartitionTypeName(uint8_t PartitionType)
{ //binary to hex?
    //printf("Read in the byte and decide PartitionType");
    switch (PartitionType)
    {
    case 0x01:
        return ("0x01 is FAT12");

    case 0x04:
        return ("0x04 is FAT16");

    case 0x06:
        return ("0x06 is FAT16B");

    case 0x07:
        return ("0x07 is NTFS");

    case 0x0B:
        return ("0x0B is FAT32 With CHS Addressing");

    case 0x0C:
        return ("0x0C is FAT32 With LBA");

    default:
        return ("Partition Type is unknown");
    }
}

/******************************************************************************
**                                    HexDump                                **
******************************************************************************/

void HexDump(void *addr, int size)
{
    int i;
    char temp[17];
    unsigned char *x = (unsigned char *)addr;

    // Process every byte in the data.
    for (i = 0; i < size; i++)
    {

        // Multiple of 8 means new line (with line offset).
        if ((i % 16) == 0)
        {
            // Padding for proper formatting
            if (i != 0)
            {
                printf("  %s\n", temp);
            }

            // Address offset on the left side
            printf("  %08x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", x[i]);

        // If current character is not ASCII then store it as '?'
        //  from  (space) --------->  (~) in ASCII
        if ((x[i] < 0x20) || (x[i] > 0x7e))
        {
            temp[i % 16] = '.';
        }
        else
        {
            temp[i % 16] = x[i];
        }
        // Add a Null terminator to the end of the line so it can be printed
        temp[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0)
    {
        printf("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  %s\n", temp);
}

/******************************************************************************
**                             RemoveTrailingSpaces                          **
******************************************************************************/

void RemoveTrailingSpaces(char* fat_filename_buffer)
{
    assert(fat_filename_buffer != NULL);
    int end = strlen(fat_filename_buffer);

    // Substutute NULLs for an trailing spaces
    int i = end - 1;
    while(i >= 0 && fat_filename_buffer[i] == ' ')
    {
        fat_filename_buffer[i] = '\0';
        i--;
    }
}

/******************************************************************************
**                             EightDotThreeString                           **
******************************************************************************/

const char* EightDotThreeString(const uint8_t name[8], const uint8_t ext[3])
{
    static char full_filename[13] = {0};
    memset(full_filename, 0, sizeof(full_filename));
    strncat(full_filename, (char*)name, 8);
    RemoveTrailingSpaces(full_filename);

    if (ext[0] != ' ')
    {
        strcat(full_filename, ".");
        strncat(full_filename, (char*)ext, 3);
        RemoveTrailingSpaces(full_filename);
    }
    return full_filename;
}

/******************************************************************************
**                                 FixShortFile                              **
******************************************************************************/

char* FixShortFile(void *rawFilename)
{
    //make a char pointer based off void pointer we are given
    char *pRawFileName = rawFilename;
    //make an array to update the string in
    static char fullFileName[12] = {'\0'};
    //copy the first 8 characters of the char pointer (first 8 bytes are always name)
    strncpy(fullFileName, rawFilename, 8);
    //helper function to remove trailing spaces
    RemoveTrailingSpaces(fullFileName);

    //modify string based off if its a directory or file
    //9th character should have text if a file, if empty then a dir.
    if (pRawFileName[8] == ' ') //this is a directory
    {
    }
    else //this is a file
    {
        int end = 0;
        while (fullFileName[end] != '\0')
        {
            //printf(". %c\n",fullFileName[end]);
            end++;
        }
        //update the following 4 characters to have .[extention] + null padding at end
        fullFileName[end + 1] = '.';
        fullFileName[end + 2] = pRawFileName[8];
        fullFileName[end + 3] = pRawFileName[9];
        fullFileName[end + 4] = pRawFileName[10];
        fullFileName[end + 5] = '\0';
    }

    return fullFileName;
}
