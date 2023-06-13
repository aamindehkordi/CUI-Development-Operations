# FatReader
The CSC 430 class' basic implementaion of a FAT File Reader System

# Design Document
Team Lead: Luke Frisbee

Date: February 22, 2021

Team Members:

* Kevin Alonso
* Ali Amin
* Luke Frisbee
* Alex McCune
* Yunhu Xiang

Stage 2 Slides:https://docs.google.com/presentation/d/1Jy8gLT9gnNBVQeR6xrf6DnacX1RCADLgA8syVbqInJo/edit?usp=sharing

# Helper Functions

```c
[x] Luke char*FileAttributes(uint8_t): 

Turns input parameter of "1 byte" into a more human friendly readable string

Example: 

11101011 → "ReadOnly|Hidden|System|X|Directory|X|Device|Reserved|"

```

```c
[x] Yunhu char* AsHumanSize(int bytes):

Turns input parameter "int bytes" into a more human friendly readable string. For example:

1440 → "1.44 KB"

1243652 →"1.32 MB" 

111921029101 → "32.19 GB"

```

```c
[x] Yunhu char* MediaType(uint8_t):

Read input parameter of 1 byte and returns the media type. Examples: HDD, Floppy, Disc, etc.

11101111 → 0xEF → "Floppy"

```

```c
[x] Kevin char* PartitionTypeName(uint8_t):

Reads input parameter of 1 byte and responds with telling us the File System. For example, reading the byte will tell us if the file system is FAT16, FAT32, NTFS, etc.

Example:

00000001 → 0x01 → "FAT12"

00000100 → 0x04 → "FAT16"

00000110 → 0x06 → "FAT16B"

```

```c
[x] Ali void HexDump(void*, int size):

Reads data at memory address (void*) till the end of given size, then dumps the hex values
```

```c
[x] Alex void FixShortFile(void*):

Fixes up the name of data in our Fat Table. Note that this is only designed for short files. Short files can only contain a file name with a max size of 8, and an extension name with a max size of 3.


For Example:

0123456789ABC
File    .txt<jA...Lma)!M>Am1...

Would Need To Become:

012345678 9 A B C
File.txt\0\0\0\0\0jA...Lma)!M>Am1...
```

# Reader Functions (Stage 1)

```c
[x] Kevin- MBR* ReadMsterBootRecord(FILE* fp, long int offset)

This function will read in the MBR. 

The MBR is the information in the first sector of any hard disk. It identifies where an operating system is located so it can be loaded into the computers main storage.
```

```c
[x] Alex- FAT_BOOT* ReadFatBootSector(FILE* fp, long int offset)

This function will read in the Fat Boot Sector.

The Fat Boot Sector is responsible for identifying the location of the file, loading it into memory, and transferring control to it. 
```

```c
[x] Ali- FAT_TABLE* ReadFatTable(FILE* fp, long int offset, int count, int fat_sectors, int sector_size)

This function will read in the FAT Table.

The FAT Table is a table that an operating system maintains on  a hard disk to keep track of the clusters that a file has been stored in
```

```c
[x] Yunhu- ROOT_DIR* ReadFatRootDirectory(FILE* fp, long int offset, int count)

This function will read in the FAT Root Directory 

The purpose of the root directory is to find the main directory of a certain file. 
```

```c
[x] Luke- int ReadDiskImage(char* filename)

This function will read in the disk file. 

```

# Reader Functions (Stage 2)

```c
[x] Kevin- uint32_t GetFileSize(char* filename)

Runs GetFileSizeFromEntry on an entry.
```

```c
[x] Kevin- uint32_t GetFileSizeFromEntry(ROOT_ENTRY* entry)

Gets the size of the entry. Entries can also be directories.
```

```c
[x] Yunhu- int GetDirectorySize(char* directory)

Runs GetDirectorySizeFromEntry on an entry.
```

```c
[x] Yunhu- int GetDirectorySizeFromEntry(ROOT_ENTRY* entry)

Counts all clusters in entry and returns the size of the entry.
```

```c
[x] Alex- char* GetFileData(char* targetFile)

Runs GetRootEntry, then GetFileSize, then ReadFileContents and reads all of that data about the target file into buffer.
```

```c
[x] Ali - char* ReadFileContents(ROOT_ENTRY* entry, char* buffer, int size)

Searches through FAT to find pointers to the file's data and seeks to it to then reads all of the data into a buffer which gets returned.
```

```c
[x] LUKE & Prof. TALLMAN - ROOT_ENTRY* GetRootEntry(char* fullDirectory)

Finds the first cluster of the Root Entry and reads it to find the next cluster until the final cluster is read and the Root Entry gets returned.
```

# FAT Reader Structures

The FAT Reader library requires 6 structures.

```c
///PARTITION

typedef struct _PARTITION
{
	uint8_t bootable;
	uint8_t first_chs[3];
	uint8_t type;
	uint8_t last_chs[3];
	uint32_t lba_offset;
	uint32_t sector_count;

}__attribute__((packed)) PARTITION;
```

```c
///MBR

typedef struct _MBR
{
	uint8_t bootloader[446]; 
	PARTITION list[4]; 
	uint16_t bootsignature; 

}__attribute__((packed)) MBR;
```

```c
//FAT BOOT SECTOR

typedef struct FAT_BOOT
{
	uint8_t jump_instruction[3]; 
	uint8_t OEM_name_in_text[8]; 
	
	//BIOS parameter block
	uint16_t bytes_per_sector;   
	uint8_t sectors_per_cluster;
	uint16_t reserved_logical_sectors;
	uint8_t number_of_file_allocation_table;
	uint16_t fat_root_directory_entries;
	uint16_t logical_sectors;
	uint8_t media_descriptor;
	uint16_t logical_sectors_per_alloc_table;

	//DOS 3.1 BPB
	uint16_t phyiscal_sectors_per_track;
	uint16_t num_of_heads_for_disks;
	uint8_t count_of_hidden_sectors[4];
	uint8_t total_logical_sectors[4];

	//BIOS paramter block extended
	uint8_t physical_drive_num;
	uint8_t reserved;
	uint8_t extended_boot_signature;
	uint8_t volume_id[4];
	uint8_t partition_volume_label[11];
	uint8_t file_system_type[8];



	uint8_t bootstrap_code[448]; 
	uint16_t boot_sector_signature; 

}__attribute__((packed)) FAT_BOOT;
```

```c
//FAT TABLE

typedef uint16_t FAT_TABLE_ENTRY;
typedef struct FAT_TABLE
{
	FAT_TABLE_ENTRY Table[0];

}__attribute__((packed)) FAT_TABLE;

```c

// Root Entry

typedef struct ROOT_ENTRY
{
	uint8_t filename[8];
	uint8_t file_exetension[3];
	uint8_t file_attribute;
	uint8_t reserved[10];
	uint16_t timeOfLastChange;
	uint16_t dateOfLastChange;
	uint8_t first_cluster[2];
	uint32_t file_size;

}__attribute__((packed)) ROOT_ENTRY;
```

```c
//Root Directory

typedef struct ROOT_DIR
{
	ROOT_ENTRY data[0];

} __attribute__((packed)) ROOT_DIR;

```
