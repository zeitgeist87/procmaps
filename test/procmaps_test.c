#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "procmaps.h"

void parse_callback_func(void *data, int row, uint64_t start, uint64_t end,
                         const char *flags, uint64_t offset, int64_t inode,
                         const char *filename) {
  bool *success = (bool *)data;

  success[1] = true;

  if (start >= end) {
    fprintf(stderr, "Error: start > end\n");
    success[0] = false;
  }

  if (strlen(flags) != 4) {
    fprintf(stderr, "Error: strlen(flags) != 4\n");
    success[0] = false;
  }

  printf("%" PRIx64 "-%" PRIx64 " %s %" PRIx64 " %" PRId64 " \"%s\" %p %d\n",
         start, end, flags, offset, inode, filename, data, row);
}

int main() {
  bool callback_success[] = {true, false};
  bool main_success;

  main_success = get_proc_self_maps(parse_callback_func, callback_success);
  if (!main_success || !callback_success[0] || !callback_success[1]) {
    fprintf(stderr,
            "get_proc_self_maps() failed (main_success: %d, callback_success: "
            "%d, %d)\n",
            main_success, callback_success[0], callback_success[1]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
