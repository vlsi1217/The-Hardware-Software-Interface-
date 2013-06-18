#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include "mm.h"
#include "config.h"
#include "memlib.h"
#include "fsecs.h"

int main()
{
    int i=2;
    void *a[12];
    int index = 0;
    int size = 2048;
    mem_init();

    if(mm_init()<0)
    {
        fprintf(stderr,"memory init error\n");
        return -1;
    }
    
    for(;i<size;i*=2)
    {
        a[index] = mm_malloc(i);
        fprintf(stderr,"after malloc\n");
        examine_heap();
        a[index] = mm_realloc(a[index],i*2);
        fprintf(stderr,"after realloc\n");
        examine_heap();

        index++;
    }
    
    index = 0;
    for(i=2;i<size;i*=2)
    {
        mm_free(a[index]);
        index ++;
    }
    fprintf(stderr,"success\n");
    
}

