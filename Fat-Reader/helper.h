#ifndef HELPER_HEADER
#define HELPER_HEADER
#include <stdint.h>
#include "reader.h"

/* Yunhu - AsHumanSize
 * Turns input parameter "int bytes" into a more human friendly readable string.
 *
 * -=| Params |=-
 *   bytes: amount of bytes
 *
 * -=| Returns |=-
 *   type:    char*
 *   success: returns a readable string
 *   failure: returns NULL
 */
char* AsHumanSize(uint64_t bytes);

/* YUNHU - MediaType
 * Read input parameter of 1 byte and returns the media type. Examples: HDD, Floppy, Disc, etc.
 *
 * -=| Params |=-
 *   byte: One Byte
 *
 * -=| Returns |=-
 *   type:    char*
 *   success: returns "Floppy" or "Disk"
 *   failure: returns NULL
 */
char* MediaType(uint8_t byte);

/* LUKE - FileAttributes
 * Turns input parameter of "1 byte" into a more human friendly readable string
 *
 * -=| Params |=-
 *   byte: One Byte
 *
 * -=| Returns |=-
 *   type:    MBR*
 *   success: returns result
 *   failure: returns NULL
 */
char* FileAttributes(uint8_t byte);

/* KEVIN - PartitionTypeName
 * Reads input parameter of 1 byte and responds with telling us the File System. 
 * For example, reading the byte will tell us if the file system is FAT16, FAT32, NTFS, etc.
 *
 * -=| Params |=-
 *   PartitionType: Type of Partition
 *
 * -=| Returns |=-
 *   type:    char*
 *   success: returns buffer
 *   failure: returns NULL
 */
char* PartitionTypeName(uint8_t PartitionType);

/* Prof. TALLMAN - RemoveTrailingSpaces
 * Removes Trailing Spaces in FAT buffer
 *
 * -=| Params |=-
 *   fat_filename_buffer: FAT buffer
 *
 */
void RemoveTrailingSpaces(char* fat_filename_buffer);

/* ALI - HexDump
 * Reads data at memory address (void*) till the end of given size, then dumps the hex values. 
 *
 * -=| Params |=-
 *   addr: The starting location to dump
 * 	 size: The amount to read from addr
 *
 */
void HexDump(void*, int size);

/* Prof. TALLMAN - EightDotThreeString
 * Cleans up name and filename extensions so everything works fine
 *
 * -=| Params |=-
 *   name: File name
 * 	 ext: File name extention
 *
 * -=| Returns |=-
 *   type:    const char*
 *   success: returns Full File Name
 *   failure: returns NULL
 */
const char* EightDotThreeString(const uint8_t name[8], const uint8_t ext[3]);

/* ALEX - FixShortFile
 * Fixes up the name of data in our Fat Table. Note that this is only designed for short file.
 * Short files can only contain a file name with a max size of 8, 
 * and a extension name with a max size of 3.
 *
 * -=| Params |=-
 *   rawFilename: The raw file name
 *
 * -=| Returns |=-
 *   type:    char*
 *   success: returns Full File Name
 *   failure: returns NULL
 */
char* FixShortFile(void *rawFilename);

#endif
