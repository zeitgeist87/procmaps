#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "procmaps.h"

#define INIT_BUFFER_SIZE (64 * 1024)
#define MAX_BUFFER_SIZE (10 * 1024 * 1024)

#if defined(__linux__) || defined(__CYGWIN__) || defined(__CYGWIN32__)
#define MAPS_PATH "/proc/%d/maps"
#define MAPS_SELF_PATH "/proc/self/maps"
#elif defined(__FreeBSD__)
#define MAPS_PATH "/proc/%d/map"
#define MAPS_SELF_PATH "/proc/curproc/map"
#elif defined(__sun__)
#define MAPS_PATH "/proc/%d/map"
#define MAPS_SELF_PATH "/proc/self/map"
#else
#define MAPS_PATH ""
#define MAPS_SELF_PATH ""
#endif

/**
 * Returns true if EOF was reached an the whole file is in the buffer
 */
static bool read_file(const char *path, char *buffer, size_t buffer_size,
                      size_t *bytes_read) {
  bool res = false;
  FILE *file;

  file = fopen(path, "rb");
  if (!file) {
    return res;
  }

  *bytes_read = fread(buffer, 1, buffer_size, file);

  if (feof(file) && *bytes_read != 0) {
    res = true;
  }

  fclose(file);
  return res;
}

/*
 * Allocates a buffer and reads the whole file into it. Returns false if an
 * error occurred or the the file is bigger than MAX_BUFFER_SIZE
 */
static bool read_whole_file(const char *path, char **buffer_out,
                            size_t *file_size_out) {
  char *buffer = malloc(INIT_BUFFER_SIZE);
  size_t buffer_size = INIT_BUFFER_SIZE;
  bool res = false;

  while (buffer && buffer_size <= MAX_BUFFER_SIZE && !res) {
    res = read_file(path, buffer, buffer_size, file_size_out);
    if (!res) {
      /* In case of an error, increase buffer size and try again */
      buffer_size *= 2;
      buffer = realloc(buffer, buffer_size);
    }
  }

  if (res) {
    *buffer_out = buffer;
  } else {
    free(buffer);
  }

  return res;
}

bool populate_proc_self_maps_df(populate_callback cb, void *data) {
  char *content;
  size_t content_len;
  unsigned int i, total_rows = 0;

  if (!read_whole_file(MAPS_SELF_PATH, &content, &content_len)) {
    return false;
  }

  for (i = 0; i < content_len; ++i) {
    if (content[i] == '\n') {
      ++total_rows;
    }
  }

  /*"55bd7ee28000-55bd7ee2a000 r--p 00000000 00:19 16394429 /usr/bin/cat"

  sscanf(text, "%"SCNx64"-%"SCNx64" %4s %"SCNx64" %x:%x %"SCNd64" %n",
   *        start, end, flags, offset, major, minor, inode, filename_offset)*/
  return false;
}