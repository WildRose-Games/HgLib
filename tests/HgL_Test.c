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

#define HGL_ARENA_IMPLEMENTATION
#include "../HgL_Arena.h"

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
  HG_LOG("Testing HgL_Arena.h");
  {

    /* Basic usage, filling too much */
    HG_LOG("Creating and allocating arena, pushing some memory to.");
  
    HgArena* arena = hgCreateArena(20, 8); 
  
    int* i = (int*)hgArenaPush(arena, sizeof(int));
    *i = 10;
  
    int* j = (int*)hgArenaPush(arena, sizeof(int));
    *j = 20;
    HG_LOG("Pushing some more memory past max (Should error)");
  
    int* k = (int*)hgArenaPush(arena, sizeof(int));
    hgDestroyArena(arena);
  }
  {
    HG_LOG("Trying to push and pop some memory in correct order");
    HgArena* arena = hgCreateArena(100, 1);
    int* i = (int*)hgArenaPush(arena, sizeof(int));
    int* j = (int*)hgArenaPush(arena, sizeof(int));
    int* k = (int*)hgArenaPush(arena, sizeof(int));
    
    hgArenaPop(arena, k, sizeof(int));
    hgArenaPop(arena, j, sizeof(int));
    hgArenaPop(arena, i, sizeof(int));

    hgDestroyArena(arena);
  }
  HG_LOG("Pushing and Poping in wrong order (should error twice on debug build)");
  {
    HgArena* arena = hgCreateArena(100, 1);
    int* i = (int*)hgArenaPush(arena, sizeof(int));
    int* j = (int*)hgArenaPush(arena, sizeof(int));
    int* k = (int*)hgArenaPush(arena, sizeof(int));
    
    hgArenaPop(arena, i, sizeof(int));
    hgArenaPop(arena, j, sizeof(int));

    hgDestroyArena(arena);
  }
  HG_LOG("Testing offsets");
  {
  
    HgArena* arena = hgCreateArena(50, 10);
    int* i = (int*)hgArenaPush(arena, sizeof(int));
    int* j = (int*)hgArenaPush(arena, sizeof(int));
    int* k = (int*)hgArenaPush(arena, sizeof(int));
    
    hgArenaPop(arena, k, sizeof(int));
    hgArenaPop(arena, j, sizeof(int));
    hgArenaPop(arena, i, sizeof(int));

    hgDestroyArena(arena);
  }
  return 0;
}
