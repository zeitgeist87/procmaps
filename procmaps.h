#ifndef PROCMAPS_H
#define PROCMAPS_H

#include <stdbool.h>

typedef void (*populate_callback)(void *data, int row, int col, int total_rows,
                                  const char *);

bool populate_proc_self_maps_df(populate_callback cb, void *data);

#endif