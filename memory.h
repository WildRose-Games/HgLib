/*
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT
 */

#ifndef HGL_MEM_H
#define HGL_MEM_H

typedef struct HgArena {
  uint64_t size;
  uint64_t position;
  uint8_t *memory;
}HgArena;

void* hgArenaPush(HgArena *hgArena, uint64_t allocSize);

inline void* hgArenaPushZero(HgArena *hgArena, uint64_t allocSize);

void hgArenaPop(HgArena *hgArena, uint64_t freeSize);

void hgArenaPopAll(HgArena *hgArena);

#define HGL_MEM_PAD 16

#endif /* HGL_MEM_H */

#include <string.h>


void* hgArenaPush(HgArena *arena, uint64_t allocSize){
  if(arena->position + allocSize > arena->size){
    HG_ERROR("Arena Alloc FAILED! Ran out of memory!");
    return NULL;
  }
  uint64_t oldPosition = arena->position;
  uint64_t newPosition = allocSize;
  if(newPosition % HGL_MEM_PAD != 0){
    newPosition += HGL_MEM_PAD - (newPosition % HGL_MEM_PAD);
  }
  arena->position += newPosition;
  return arena->memory + oldPosition;
}

inline void* hgArenaPushZero(HgArena *arena, uint64_t allocSize){
  void* memory = hgArenaPush(arena, allocSize);
  memset(memory, 0, allocSize);
  return memory;
}

void hgArenaPop(HgArena *arena, uint64_t freeSize){
  if(freeSize > arena->position){
    HG_WARN("Tried to free too much from Arena Alocator");
    arena->position = 0;
    return;
  }
  uint16_t newPosition = freeSize;
  if(newPosition % HGL_MEM_PAD != 0){
    newPosition += HGL_MEM_PAD - (newPosition % HGL_MEM_PAD);
  }
  arena->position -= newPosition;
}

void hgArenaPopAll(HgArena *arena){
  arena->position = 0;
}
