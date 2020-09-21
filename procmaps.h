#ifndef PROCMAPS_H
#define PROCMAPS_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*parse_callback)(void *data, int row, uint64_t start,
                               uint64_t end, const char *flags, uint64_t offset,
                               int64_t inode, const char *filename);

bool get_proc_self_maps(parse_callback cb, void *data);

/* All implementations for Linux, MacOS and Windows are always built. We define
 * a macro here, to disable the implementations that are not applicable for the
 * system*/

#if defined(__linux__) || defined(__CYGWIN__) || defined(__CYGWIN32__) ||      \
    defined(__FreeBSD__)

#define ENABLE_LINUX_BUILD 1

#elif defined(__sun__)

#define ENABLE_SUN_BUILD 1

#elif defined(__MACH__)

#define ENABLE_MACOS_BUILD 1

#elif defined(PLATFORM_WINDOWS)

#define ENABLE_WINDOWS_BUILD 1

#endif

#endif
