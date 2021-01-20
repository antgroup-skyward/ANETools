#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#define LOG(fmt, __args...) printf("LOG %16s %4d %s : " fmt, __FILE__, __LINE__, __func__, ##__args);
int file_size(FILE *fp, size_t *psize);
int file_copy(char *src, char *dst);
uint8_t *file_read(FILE *fp, size_t off, size_t size);
int file_write(FILE *fp, size_t off, void *data, size_t size);
char *file_string(FILE *fp, size_t off);
#endif//UTIL_H
