#include "util.h"
#include <stdlib.h>
int file_size(FILE *fp, size_t *psize) {
    if (fseek(fp, 0, SEEK_END) != 0) {
        LOG("fseek failed\n");
        return -1;
    }
    long off = ftell(fp);
    if (off < 0) {
        LOG("ftell failed\n");
        return -1;
    }
    *psize = (size_t)off;
    return 0;
}
int file_copy(char *src, char *dst) {
    int ret = -1;
    FILE *sfp = fopen(src, "rb");
    if (sfp == NULL) {
        LOG("fopen %s failed\n", src);
        return -1;
    }
    FILE *dfp = fopen(dst, "wb");
    if (dfp == NULL) {
        LOG("fopen %s failed\n", dst);
        fclose(sfp);
        return -1;
    }
    uint8_t buf[4096];
    size_t once = 0;
    while((once = fread(buf, 1, sizeof(buf), sfp)) > 0) {
        if (fwrite(buf, once, 1, dfp) != 1) {
            LOG("fwrite failed\n");
            goto bail;
        }
    }
    if (!feof(sfp)) {
        LOG("fread failed\n");
        goto bail;
    }
    ret = 0;
bail:
    fclose(sfp);
    fclose(dfp);
    return ret;
}
uint8_t *file_read(FILE *fp, size_t off, size_t size) {
    if (fseek(fp, off, SEEK_SET) != 0) {
        LOG("fseek failed\n");
        return NULL;
    }
    uint8_t *buf = (uint8_t *)malloc(size);
    if (buf == NULL) {
        LOG("oom\n");
        return NULL;
    }
    if (fread(buf, size, 1, fp) != 1) {
        LOG("fread failed\n");
        return NULL;
    }
    return buf;
}
int file_write(FILE *fp, size_t off, void *data, size_t size) {
    if (fseek(fp, off, SEEK_SET) != 0) {
        LOG("fseek failed\n");
        return -1;
    }
    if (fwrite(data, size, 1, fp) != 1) {
        LOG("fwrite failed\n");
        return -1;
    }
    return 0;
}
char *file_string(FILE *fp, size_t off) {
    long ori = ftell(fp);
    if (ori < 0) {
        LOG("ftell failed\n");
        return NULL;
    }
    if (fseek(fp, off, SEEK_SET) != 0) {
        LOG("fseek failed\n");
        return NULL;
    }
    size_t len = 0;
    char c;
    do {
        if (fread(&c, sizeof(c), 1, fp) != 1) {
            LOG("fread failed\n");
            return NULL;
        }
        len++;
    } while(c != '\0');
    if (fseek(fp, off, SEEK_SET) != 0) {
        LOG("fseek failed\n");
        return NULL;
    }
    char *str = (char *)malloc(len);
    if (str == NULL) {
        LOG("oom\n");
        return NULL;
    }
    size_t i;
    for (i = 0; i < len; ++i) {
        if (fread(&str[i], sizeof(char), 1, fp) != 1) {
            LOG("fread failed\n");
            free(str);
            return NULL;
        }
    }
    if (fseek(fp, ori, SEEK_SET) != 0) {
        LOG("fseek failed\n");
        free(str);
        return NULL;
    }
    return str;
}
