/*  
 *  Tests HGL_Log.c
 *
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT
 */

#include <stdio.h>

#define HGL_LOG_IMPLEMENTATION
#include "../HgL_Log.h"

#define HGL_MEMORY_IMPLEMENTATION
#include "../HgL_Memory.h"

int main(void){

/* HGL_Log.h */
  HG_LOG("testing HgL_Log.h");
  {
    /* Log Types */
    HG_DEBUG("Testing Debug messages");
    HG_WARN("Testing Warning messages");
    HG_ERROR("Testing Error messages");
    HG_FATAL("Testing Fatal messages");

    /* String formating */
    HG_LOG("%s", "Testing...");
    HG_LOG("%s, %d", "Testing", 1);
    HG_LOG("%s, %d, %d", "Testing", 1, 2);
    HG_LOG("%s, %d, %d, %d!", "Testing", 1, 2 ,3);
  }
  
/* HGL_Memory.h */
  printf("\n");
  HG_LOG("Testing HgL_Memory.h");
  HG_LOG("Testing HgArena basic usage:");
  printf("\n");
  {

    /* Basic usage, filling too much */
    HG_LOG("Allocating arena with init size of 20, mem multiple of 8");
  
    HgArena* arena = hgCreateArena(20, 8); 
    HG_LOG("Pushing some memory for int* i");
  
    int* i = hgArenaPush(arena, sizeof(int));
    *i = 10;
    HG_LOG("int* i has value: %d", *i);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    HG_LOG("Pushing some more memory for int* j");
  
    int* j = hgArenaPush(arena, sizeof(int));
    *j = 20;
    HG_LOG("int* i value =  %d, int* j value = %d", *i, *j);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    HG_LOG("Pushing some more memory past initialization");
  
    int* k = hgArenaPush(arena, sizeof(int));
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    hgDestroyArena(arena);
  }
  printf("\n");
  HG_LOG("Pushing and Poping in correct order");
  {
    HgArena* arena = hgCreateArena(100, 1);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    int* i = hgArenaPush(arena, sizeof(int));
    int* j = hgArenaPush(arena, sizeof(int));
    int* k = hgArenaPush(arena, sizeof(int));
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    
    hgArenaPop(arena, k);
    hgArenaPop(arena, j);
    hgArenaPop(arena, i);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);


    hgDestroyArena(arena);
  }
  HG_LOG("Pushing and Poping in wrong order");
  {
    HgArena* arena = hgCreateArena(100, 1);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    int* i = hgArenaPush(arena, sizeof(int));
    int* j = hgArenaPush(arena, sizeof(int));
    int* k = hgArenaPush(arena, sizeof(int));
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);
    
    hgArenaPop(arena, i);
    hgArenaPop(arena, j);
    HG_LOG("Arena is at position: %d, size: %d", arena->dataPosition,
        arena->dataSize);

    hgDestroyArena(arena);
  }
  

  return 0;
}
