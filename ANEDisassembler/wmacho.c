#include "wmacho.h"
int wmacho_open(struct wmacho *w, const char *path) {
    memset(w, 0, sizeof(*w));
    w->fp = fopen(path, "rb");
    if (w->fp == NULL) {
        printf("open %s failed\n", path);
        return -1;
    }
    w->mh = (struct mach_header_64 *)file_read(w->fp, 0, sizeof(*w->mh));
    if (w->mh == NULL) {
        LOG("file_read failed\n");
        goto bail;
    }
    size_t sizeofcmds = w->mh->sizeofcmds;
    free(w->mh);
    w->mh = (struct mach_header_64 *)
        file_read(w->fp, 0, sizeof(*w->mh) + sizeofcmds);
    if (w->mh == NULL) {
        LOG("file_read failed\n");
        goto bail;
    }
    if (w->mh->sizeofcmds != sizeofcmds) {
        LOG("under attack\n");
        free(w->mh);
        goto bail;
    }
    //valid check
    size_t pos = 0,i;
    for (i = 0; i < w->mh->ncmds; ++i) {
        if (pos + sizeof(struct load_command) > sizeofcmds) {
            LOG("bad head\n");
            goto bail_mh;
        }
        struct load_command *cmd = (struct load_command *)
            (((uint8_t *)w->mh) + sizeof(*w->mh) + pos);
        if (cmd->cmdsize < sizeof(struct load_command)) {
            LOG("bad head\n");
            goto bail_mh;
        }
        if ((pos + cmd->cmdsize) > sizeofcmds) {
            LOG("bad head\n");
            goto bail_mh;
        }
        pos += cmd->cmdsize;
    }
    w->cmds = (struct load_command **)
        calloc(sizeof(struct load_command *), w->mh->ncmds);
    if (w->cmds == NULL) {
        LOG("oom\n");
        goto bail_mh;
    }
    pos = 0;
    for (i = 0; i < w->mh->ncmds; ++i) {
        struct load_command *cmd = (struct load_command *)
            (((uint8_t *)w->mh) + sizeof(*w->mh) + pos);
        w->cmds[i] = cmd;
        pos += cmd->cmdsize;
    }
    return 0;
bail_mh:
    free(w->mh);
bail:
    fclose(w->fp);
    return -1;
}
int wmacho_get_sect_by_name(struct wmacho *w, const char *name, void **pptr, size_t *psize) {
    size_t i;
    for (i = 0; i < w->mh->ncmds; ++i) {
        struct load_command *cmd = w->cmds[i];
        if (cmd->cmd != LC_SEGMENT_64)
            continue;
        if (cmd->cmdsize < sizeof(struct segment_command_64)) {
            LOG("bad seg\n");
            return -1;
        }
        struct segment_command_64 *seg = (struct segment_command_64 *)cmd;
        struct section_64 *secs = (struct section_64 *)(((uint8_t *)seg) + sizeof(*seg));
        if (cmd->cmdsize < (sizeof(*seg) + seg->nsects * sizeof(*secs))) {
            LOG("bad seg\n");
            return -1;
        }
        size_t j;
        for (j = 0; j < seg->nsects; ++j) {
            struct section_64 *sec = &secs[j];
            if (strncmp(sec->sectname, name, 16) == 0) {
                void *ptr = file_read(w->fp, sec->offset, sec->size);
                if (ptr == NULL) {
                    LOG("file_read failed\n");
                    return -1;
                }
                *pptr = ptr;
                *psize = sec->size;
                return 0;
            }
        }
    }
    return -1;
}
int wmacho_close(struct wmacho *w) {
    free(w->mh);
    fclose(w->fp);
    return -1;
}
