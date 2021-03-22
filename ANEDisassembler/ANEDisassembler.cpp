#include <iostream>

extern "C" {
#include "ANETD.h"
#include "wmacho.h"
    int _Z24ZinIrRegBitPrintOutDebugILj7EE11ZinIrStatusjRN11ZinHWTraitsIXT_EE6HwTypeEiRNSt3__113basic_ostreamIcNS5_11char_traitsIcEEEE(
            unsigned int, void * /*ZinHWTraits<7u>::HwType &*/, int, std::ostream &);
}
#define DUMP_INST
int parseText(void *ptr, size_t size) {
    uint8_t *text = (uint8_t *)ptr;
    size_t inst_count = size / 0x300;
    if (size % 0x300)
        inst_count++;
    if (inst_count == 0) {
        LOG("no AneInstruction ????\n");
        return -1;
    }
    printf("inst_count == %lu\n", inst_count);
    size_t i;
    for (i = 0; i < inst_count; ++i) {
        uint8_t ZinAneTd_v7[0x350];
        size_t copy_size = 0x300;
        if (i == (inst_count - 1))
            copy_size = size % 0x300;
        memcpy(ZinAneTd_v7, text + 0x300 * i, copy_size);
        memmove(ZinAneTd_v7 + 0x128, ZinAneTd_v7 + 0x7c, 0x300 - 0x7c - 0x5c);
        _Z24ZinIrRegBitPrintOutDebugILj7EE11ZinIrStatusjRN11ZinHWTraitsIXT_EE6HwTypeEiRNSt3__113basic_ostreamIcNS5_11char_traitsIcEEEE(
                i, ZinAneTd_v7, 16, std::cout);
#ifdef DUMP_INST
        char path[64];
        snprintf(path, sizeof(path), "inst%lu.dump", i);
        FILE *fp = fopen(path, "wb");
        if (fp == NULL) {
            printf("open %s failed\n", path);
            continue;
        }
        //if (fwrite(ZinAneTd_v7, sizeof(ZinAneTd_v7), 1, fp) != 1) {
        if (fwrite(text + 0x300 * i, copy_size, 1, fp) != 1) {
            printf("fwrite %s failed\n", path);
        }
        fclose(fp);
#endif
    }
    return 0;
}
/*
 * uint32_t regInfo
 * uint32_t values[regInfo >> 26]
 * uint32_t pad
 *
 */
int parseRegs_v5(uint8_t *regs, size_t size) {
    uint32_t regOff = 0;
    uint32_t i = 0;
    while(regOff < size) {
        uint32_t left = size - regOff;
        if (left < 4) {
            LOG("bad reg\n");
            return -1;
        }
        uint8_t *ptr = regs + regOff;
        uint32_t regInfo = *(uint32_t *)ptr;
        uint32_t regCnt = regInfo >> 26u;
        uint32_t regAddr = regInfo & 0x3FFFFFFu;
        if (left < (4 + 4 * regCnt)) {
            LOG("bad reg\n");
            return -1;
        }
        printf("idx %u off %lu addr %#010x count %u :\n", i, ptr - regs, regAddr, regCnt);
        uint32_t j;
        for (j = 0; j < (regCnt + 1); ++j) {
            uint32_t value = *(uint32_t *)(ptr + 4 + 4 * j);
            if (((regAddr >> 2) + j) >= 0xC0000) {
                LOG("overflow\n");
                return -1;
            }
            printf("    %#010x  %#010x  %u\n", regAddr + 4 * j, value, value);
            switch(i) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                printANETDv5(v5KernelDMASrc, j, 8, value, i);
                break;
            case 8:
                printANETDv5(v5Common, j, 8, value, -1);
                break;
            case 9:
                printANETDv5(v5TileDMASrc, j, 8, value, -1);
                break;
            case 10:
                printANETDv5(v5L2, j, 8, value, -1);
                break;
            case 11:
                printANETDv5(v5NE, j, 8, value, -1);
                break;
            case 12:
                printANETDv5(v5TileDMADst, j, 8, value, -1);
                break;
            default:
                LOG("bad aneTDv5 i == %u\n", i);
                return -1;
            }
        }
        regOff = regOff + 4 + regCnt * 4 + 4;
        ++i;
    }
    return 0;
}
int parseText_v5(void *ptr, size_t size) {
#define ANETDv5_SIZE 0x200
#define ANETDv5_SIZE_UNALIG 332
    uint8_t *text = (uint8_t *)ptr;
    size_t inst_count = size / ANETDv5_SIZE;
    if (size % ANETDv5_SIZE)
        inst_count++;
    if (inst_count == 0) {
        LOG("no AneInstruction ????\n");
        return -1;
    }
    printf("inst_count == %lu\n", inst_count);
    size_t i;
    for (i = 0; i < inst_count; ++i) {
        printf("-------------- Insttruction %lu ----------------\n", i);
        size_t tdsize = ANETDv5_SIZE_UNALIG;
        if ((size % ANETDv5_SIZE) && (i == (inst_count - 1)))
            tdsize = size % ANETDv5_SIZE;
        if (tdsize < 29) {
            LOG("bad inst_size\n");
            return -1;
        }
        uint8_t *td = text + ANETDv5_SIZE * i;
        printf("aneTDHeader:\n");
        size_t j;
        for (j = 0; j < 7; ++j) {
            uint32_t intValue = *(uint32_t *)(td + 4 * j);
            printf("intIdx %2lu intValue %8u %#10x :\n", j, intValue, intValue);
            printANETDv5(v5TDHeader, j, 4, *(uint32_t *)(td + 4 * j), -1);
        }
        uint32_t regOff = 28;
        if (td[19] & 0x1) {
            regOff++;
            printANETDv5(v5TDHeader, 7, 4, *(uint32_t *)(td + 4 * j), -1);
        }
        printf("reg start off %u\n", regOff);
        uint8_t *regs = td + regOff;//skip td head
        if (parseRegs_v5(regs, tdsize - regOff) != 0) {
            LOG("parseRegs_v5 failed\n");
            return -1;
        }
#ifdef DUMP_INST
        char path[64];
        snprintf(path, sizeof(path), "inst%lu.dump", i);
        FILE *fp = fopen(path, "wb");
        if (fp == NULL) {
            printf("open %s failed\n", path);
            continue;
        }
        if (fwrite(text + ANETDv5_SIZE * i, tdsize, 1, fp) != 1) {
            printf("fwrite %s failed\n", path);
        }
        fclose(fp);
#endif
    }
    return 0;
}
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage:%s <.hwx file>\n", argv[0]);
        //printf("    now support InstructionSet:v7 only\n");
        return -1;
    }
    int ret = -1;
    struct wmacho w;
    if (wmacho_open(&w, argv[1]) != 0) {
        LOG("wmacho_open failed\n");
        return -1;
    }
    void *text;
    size_t text_size;
    if (wmacho_get_sect_by_name(&w, "__text", &text, &text_size) != 0) {
        LOG("wmacho_get_sect_by_name failed\n");
        goto bail;
    }
    printf("__text size is %lu\n", text_size);
    if (parseText_v5(text, text_size) != 0) {
        LOG("parseText failed\n");
        goto bail_text;
    }
    ret = 0;
bail_text:
    free(text);
bail:
    wmacho_close(&w);
    return ret;
}
