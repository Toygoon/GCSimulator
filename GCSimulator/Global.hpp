/* The Header for Global Data
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef GLOBAL
#define GLOBAL

 /* Set Flash Storage Configuration */
 // The count of each page size (in Bytes)
#define PAGE_SIZE 1024

// How many pages in a block
#define PAGES_PER_BLOCK 64

// The length of string in single page
#define MAX_LENGTH PAGE_SIZE

// The limit of erasure per cell
#define MAX_ERASURE_LIMIT 1000

typedef unsigned long long int size_l;

#endif