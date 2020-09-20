#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>

#include "procmaps.h"

void parse_callback_func(void *data, int row, int total_rows, uint64_t start,
                         uint64_t end, const char *flags, uint64_t offset,
                         int64_t inode, const char *filename) {
  printf("%" PRIx64 "-%" PRIx64 " %s %" PRIx64 " %" PRId64 " \"%s\" %p %d %d\n", start,
         end, flags, offset, inode, filename, data, total_rows, row);
}

int main(int argc, char *argv[]) {
  get_proc_self_maps(parse_callback_func, NULL);
  return 0;
}