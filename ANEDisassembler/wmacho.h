#ifndef WMACHO_H
#define WMACHO_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "macho.h"
#include "util.h"
struct wmacho {
    FILE                    *fp;
    struct mach_header_64   *mh;
    struct load_command     **cmds;
};
int wmacho_open(struct wmacho *w, const char *path);
int wmacho_get_sect_by_name(struct wmacho *w, const char *name, void **pptr, size_t *psize);
int wmacho_close(struct wmacho *w);
#endif//WMACHO_H
