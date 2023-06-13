#ifndef CMD_HEADER
#define CMD_HEADER
#include <stdint.h>

/* Kevin - LS
*
*  Lists all available files and directories in the immediate vicinity of the current working directory.
*/
void ls();

/* Luke - PWD
*
*  Prints the current working directory.
*/
void pwd();

/* Ali - CAT
*
*  Prints out the file given through a HexDump.
*/
void cat(char* path);

/* Alex - CD
*
*  Changes current working directory to the location specified.
*/
void cd(char* path);

/* Yunhu - shellLoop
*
*  Creates the shell in which the user can interact with their FAT filesystem.
*/
void shellLoop();

#endif