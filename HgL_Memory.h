/*
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT
 */

#ifndef HGL_MEM_H
#define HGL_MEM_H

#include <stdint.h>

#define  HGL_MEM_NO_ALLOC 1
#define  HGL_MEM_WRONG_PTR 2

#define hgArenaPop(a, r) do {                   \
  switch(hgl_memory_ArenaPopFunc((a), (r))){    \
    case(HGL_MEM_NO_ALLOC):                     \
      HG_ERROR("No memory pushed in arena!");   \
      break;                                    \
    case(HGL_MEM_WRONG_PTR):                    \
      HG_ERROR("Wrong pointer popped!");        \
      break;                                    \
    default:                                    \
      break;                                    \
  }                                             \
} while ( 0 )

typedef struct HgArena HgArena;

HgArena* hgCreateArena(uint64_t initSize, int memoryMultable);

void hgDestroyArena(HgArena *hgArena);

void* hgArenaPush(HgArena *hgArena, uint64_t allocSize);

void* hgArenaPushZero(HgArena *hgArena, uint64_t allocSize);


void hgArenaPopAll(HgArena *hgArena);


#endif /* HGL_MEM_H */

#ifdef HGL_MEMORY_IMPLEMENTATION

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Include Hgl_Log.h before including this file for better logging */
#ifndef HG_ERROR
#define HG_ERROR(...) fprintf(stderr, ...);
#endif /* HG_ERROR */

struct HgArena {
  /* Data */
  uint8_t *dataMemory;
  uint64_t dataSize;
  uint64_t dataPosition;
  uint8_t dataMultiple;
  
  /* Pointer check memory */
  uint64_t ptrSize;
  uint64_t ptrPosition;
  void** ptrMemory;
};

HgArena* hgCreateArena(uint64_t initSize, int memMultiple){
  HgArena* arena = malloc(sizeof(HgArena));
  arena->dataMultiple = memMultiple;
  if(arena == NULL){
    HG_ERROR("Out of Memory, Can't make new HgArena!");
    return NULL;
  }

  arena->dataSize = initSize;
  arena->dataPosition = 0;
  arena->dataMemory = malloc(arena->dataSize); 
  if(arena->dataMemory == NULL){
    HG_ERROR("Out of Memory, Can't make HgArena Data Memory!");
      free(arena);
      return NULL;
  }
  
  arena->ptrSize = sizeof(void*) * 20;
  arena->ptrPosition = 0;
  arena->ptrMemory = malloc(arena->ptrSize); 
  if(arena->ptrMemory == NULL){
    HG_ERROR("Out of Memory, Can't make HgArena Pointer Memory!");
      free(arena);
      free(arena->dataMemory);
      return NULL;
  }

  return arena;
}

void hgDestroyArena(HgArena *arena){
 
  free(arena->dataMemory);
  free(arena->ptrMemory);
  free(arena);
}

void* hgArenaPush(HgArena *arena, uint64_t allocSize){
  /* calc alignment */
  uint64_t memOffset = allocSize;
  if(memOffset % arena->dataMultiple != 0){
    memOffset += arena->dataMultiple 
      - (memOffset % arena->dataMultiple);
  }

  if(arena->dataPosition + memOffset > arena->dataSize){
    HG_ERROR("Arena Alloc FAILED! Ran out of memory!");
    return NULL;
  }
  if(arena->ptrPosition + sizeof(void*) > arena->ptrSize){
    void* newMemory = realloc(arena->ptrMemory, arena->ptrSize * 1.5);
    if(newMemory == NULL){
    HG_ERROR("Arena Alloc FAILED! Ran out of memory!");
    return NULL; 
    }
    arena->ptrMemory = newMemory;
  }

  uint64_t oldPosition = arena->dataPosition;
  arena->dataPosition += memOffset;
  void* ptr = arena->dataMemory + oldPosition;
 
  arena->ptrMemory[arena->ptrPosition] = ptr;
  arena->ptrPosition++;

  return ptr;

}

void* hgArenaPushZero(HgArena *arena, uint64_t allocSize){
  void* memory = hgArenaPush(arena, allocSize);
  memset(memory, 0, allocSize);
  return memory;
}

int hgl_memory_ArenaPopFunc(HgArena *arena, void* returnMemory){

  if(arena->ptrPosition == 0){
    return HGL_MEM_NO_ALLOC;
  }
  void* peek = arena->ptrMemory[arena->ptrPosition - 1];
  if(returnMemory == peek){
    arena->dataPosition = (uint64_t)returnMemory 
                          - (uint64_t)arena->dataMemory;
    arena->ptrPosition--;
    return 0;
  }else{
    return HGL_MEM_WRONG_PTR;
  }
}

void hgArenaPopAll(HgArena *arena){
  arena->dataPosition = 0;
}

#endif /* HGL_MEMORY_IMPLEMENTATION */
