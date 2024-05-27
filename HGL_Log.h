/*
 *  HGL_Log - v0.1 - simple stb style logger with color
 *  
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT (see bottom of file) 
 *  No warranty implied; use at your own risk
 *
 *  TO CREATE THE IMPLEMENTATION:
 *  define HGL_LOG_IMPLEMENTATION before including HGL_Log.h
 *
 *    Example:
 *
 *    #include ...
 *    #include ...
 *    #define HGL_LOG_IMPLEMENTATION
 *    #include "HGL_Log.h"
 *    #include ...
 */

#ifndef HGL_LOG_H
#define HGL_LOG_H

/*
 *  DOCUMENTATION:
 *
 *  Basic Usage:
 *  Log macros take formatted strings like it's printf();
 *
 *  examles:
 *
 *  HG_LOG("Hello World!");
 *
 *  int var = 10;
 *  HG_LOG("var is: %d", var);
 *
 *  Log macros include:
 *  
 *  HG_LOG();
 *  HG_DEBUG();
 *  HG_WARN();
 *  HG_ERROR();
 *  HG_FATAL();
 *
 *  Does not memory allocate. Max char log length is
 *  defined with HGL_LOG_LENGTH
 *  
 *  if all files are inside of one source folder (i.e: src/)
 *  you can remove that from file location printing by changing
 *  HGL_LOG_FILE_OFFSET to remove that number of characters.
 *  
 *  To remove LOG calls from all builds that do not define HG_DEBUG
 *  comment out HGL_LOG_BUILD_IN_RELEASE 
 */

#define HGL_LOG_BUILD_IN_RELEASE

/*Don;t use HglLogType or HGL_LogFunc directly*/
typedef enum HglLogType{
  HGL_LOG_DBG,
  HGL_LOG_LOG,
  HGL_LOG_WRN,
  HGL_LOG_ERR,
  HGL_LOG_FTL
}HglLogType;

void HGL_LogFunc(HglLogType err, char* file, int line, char* fmt, ...);

#ifdef HG_DEBUG 

#define HG_LOG(...) HGL_LogFunc(HGL_LOG_LOG, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_DEBUG(...) HGL_LogFunc(HGL_LOG_DBG, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_WARN(...) HGL_LogFunc(HGL_LOG_WRN, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_ERROR(...) HGL_LogFunc(HGL_LOG_ERR, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_FATAL(...) HGL_LogFunc(HGL_LOG_FTL, __FILE__, __LINE__, \
    __VA_ARGS__)

#else
#ifdef HGL_LOG_BUILD_IN_RELEASE

#define HG_LOG(...) HGL_LogFunc(HGL_LOG_LOG, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_DEBUG(...) HGL_LogFunc(HGL_LOG_DBG, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_WARN(...) HGL_LogFunc(HGL_LOG_WRN, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_ERROR(...) HGL_LogFunc(HGL_LOG_ERR, __FILE__, __LINE__, \
    __VA_ARGS__)
#define HG_FATAL(...) HGL_LogFunc(HGL_LOG_FTL, __FILE__, __LINE__, \
    __VA_ARGS__)
#else

#define HG_LOG(...)
#define HG_DEBUG(...)
#define HG_WARN(...)
#define HG_ERROR(...)
#define HG_FATAL(...)

#endif /* HGL_LOG_BUILD_IN_RELEASE */
#endif /* HG_DEBUG */
#endif /* HGL_LOG_H */

#ifdef HGL_LOG_IMPLEMENTATION

/* Set the max char length of one log message here: */
#define HGL_LOG_LENGTH 1028

#include <stdarg.h>
#include <stdio.h>

#define HGL_LOG_FILE_OFFSET 0

/*
 * hg_logFunction should not be called manually, use helper macros.
 */

void HGL_LogFunc(HglLogType err, char* file, int line, char* fmt, ...){
  
  char msg[HGL_LOG_LENGTH];
  va_list args;

  switch(err){
  case HGL_LOG_DBG:
    snprintf(msg,
             HGL_LOG_LENGTH,
             "\033[0;36m[DEBUG] \033[0;37m%s %d: \033[0;0m%s\n",
             file + HGL_LOG_FILE_OFFSET,
             line,
             fmt);
    break;
  case HGL_LOG_LOG:
    snprintf(msg,
             HGL_LOG_LENGTH,
             "\033[0;32m[LOG] \033[0;37m%s %d: \033[0;0m%s\n",
             file + HGL_LOG_FILE_OFFSET,
             line,
             fmt);
    break;
  case HGL_LOG_WRN:
    snprintf(msg, 
             HGL_LOG_LENGTH, 
             "\033[0;33m[WARN] \033[0;37m%s %d: \033[0;0m%s\n",
             file + HGL_LOG_FILE_OFFSET,
             line,
             fmt);
    break;
  case HGL_LOG_ERR:
    snprintf(msg,
             HGL_LOG_LENGTH,
             "\033[0;35m[ERROR] \033[0;37m%s %d: \033[0;0m%s\n",
             file + HGL_LOG_FILE_OFFSET,
             line,
             fmt);
    break;
  case HGL_LOG_FTL:
    snprintf(msg,
             HGL_LOG_LENGTH,
             "\033[31m[FATAL] \033[0;37m%s %d: \033[0;0m%s\n",
             file + HGL_LOG_FILE_OFFSET,
             line,
             fmt);
    break;
  }
  
  va_start(args, fmt);
  vprintf(msg, args);
  va_end(args);
}

#endif /* HGL_LOG_IMPLEMENTATION */

/*
  LICENSE (MIT)

  Copyright (c) 2024 Gwenivere Benzschawel

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
