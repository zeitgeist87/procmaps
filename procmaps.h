#ifndef PROCMAPS_H
#define PROCMAPS_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*parse_callback)(void *data, int row, int total_rows,
                               uint64_t start, uint64_t end, const char *flags,
                               uint64_t offset, int64_t inode, const char *filename);

bool get_proc_self_maps(parse_callback cb, void *data);

#endif
