/*  
 *  Tests HGL_Log.c
 *
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT
 */

#define HGL_LOG_IMPLEMENTATION
#include "../HGL_Log.h"

int main(void){
  /* Log Types */
  HG_LOG("Testing HGL_LOG Logging");
  HG_DEBUG("Testing Debug messages");
  HG_WARN("Testing Warning messages");
  HG_ERROR("Testing Error messages");
  HG_FATAL("Testing Fatal messages");

  /* String formating */
  HG_LOG("%s", "Testing...");
  HG_LOG("%s, %d", "Testing", 1);
  HG_LOG("%s, %d, %d", "Testing", 1, 2);
  HG_LOG("%s, %d, %d, %d!", "Testing", 1, 2 ,3);
  
  return 0;
}
