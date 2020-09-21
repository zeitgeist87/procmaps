#include "procmaps.h"

#ifdef ENABLE_LINUX_BUILD

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)

#include <linux/limits.h>

#define PARSE_FORMAT "%" SCNx64 "-%" SCNx64 " %4s %" SCNx64 " %*x:%*x %" SCNd64
#define PARSE_VARS &start, &end, flags, &offset, &inode
#define PARSE_VARS_COUNT 5

#elif defined(__CYGWIN__) || defined(__CYGWIN32__)

#define PARSE_FORMAT "%llx-%llx %*s %*llx %*x:%*x %lld"
#define PARSE_VARS &start, &end, &inode
#define PARSE_VARS_COUNT 3

#else

#error Unsupported Unix variant

#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

bool get_proc_self_maps(parse_callback cb, void *data) {
  FILE *file = fopen("/proc/self/maps", "rb");
  char line[PATH_MAX + 1024];
  char filename[PATH_MAX];
  bool success;
  unsigned int row = 0;

  if (!file)
    return false;

  while (fgets(line, sizeof(line), file) != NULL) {
    uint64_t start, end, offset = 0;
    int64_t inode = 0;
    char flags[] = "r-xp";

    if (sscanf(line, PARSE_FORMAT " %s", PARSE_VARS, filename) !=
        PARSE_VARS_COUNT + 1) {

      // Try again without a filename
      filename[0] = '\0';
      if (sscanf(line, PARSE_FORMAT, PARSE_VARS) != PARSE_VARS_COUNT) {
        return false;
      }
    }

    cb(data, row, start, end, flags, offset, inode, filename);

    ++row;
  }

  success = feof(file) != 0;

  fclose(file);
  return success;
}

#endif
