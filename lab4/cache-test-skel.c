/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  addr_t start = 0x80400000L;
  addr_t i;
  int size;
  access_cache(start);
  for(i=start;;i++)
  {
      if(access_cache(i) == FALSE)
          break;
  }
  size = i - start;
  return size;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  int block_size = get_block_size();
  int count = 1;
  addr_t start = 0x80400000L;
  int i;
    
  while(1)
  {
    flush_cache();
    for(i=0;i<=count;i++)
        access_cache(start + i*block_size);
    if(access_cache(start))
    {
        count++;
    }
    else
    {
        break;
    }
  }

  return count*block_size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int cache_size = get_cache_size(0);
  int block_size = get_block_size();
  int blocks = cache_size/block_size;
  int assoc = 1;
  int array = blocks/assoc;
  int i;
  addr_t step;
  addr_t start = start = 0x80400000L;

  while(1)
  {
    flush_cache();
    step = cache_size*array;
    for(i=0;i<assoc;i++)
    {
        access_cache(start+i*step);
    }
    access_cache(start+assoc*step);
    if(access_cache(start))
    {
        assoc*=2;
        array = blocks/assoc;
    }
    else
    {
        break;
    }
  }
  
  return assoc;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
