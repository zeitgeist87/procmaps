#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "procmaps.h"

void parse_callback_func(void *data, int row, int total_rows, uint64_t start,
                         uint64_t end, const char *flags, uint64_t offset,
                         int64_t inode, const char *filename) {
  bool *success = (bool *)data;

  if (start >= end) {
    fprintf(stderr, "Error: start > end\n");
    *success = false;
  }

  if (strlen(flags) != 4) {
    fprintf(stderr, "Error: strlen(flags) != 4\n");
    *success = false;
  }

  if (row >= total_rows) {
    fprintf(stderr, "Error: row >= total_rows\n");
    *success = false;
  }

  printf("%" PRIx64 "-%" PRIx64 " %s %" PRIx64 " %" PRId64 " \"%s\" %p %d %d\n",
         start, end, flags, offset, inode, filename, data, total_rows, row);
}

int main() {
  bool callback_success = true;
  bool main_success;

  main_success = get_proc_self_maps(parse_callback_func, &callback_success);
  if (!main_success || !callback_success) {
    fprintf(stderr,
            "get_proc_self_maps() failed (main_success: %d, callback_success: "
            "%d)\n",
            main_success, callback_success);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
