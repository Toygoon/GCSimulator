/* The Header for Global Data
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef GLOBAL
#define GLOBAL

/* PAGE_SIZE, and PAGES_PER_BLOCK will be deprecated
* Because it'll be converted for dynamic modifiable values */
// The count of page in one storage
#define PAGE_SIZE 4096

// The count of page per block
#define PAGES_PER_BLOCK 64

/* Set Flash Storage Configuration */
// The count of each page size (in Bytes)
#define PAGE_SIZE 4096

// How many pages in a block
#define PAGES_PER_BLOCK 64

// The length of string in single page
#define MAX_LENGTH 10

// The limit of erasure per cell
#define MAX_ERASURE_LIMIT 1000

typedef unsigned long long size_l;

#endif