#ifndef ANETD_H
#define ANETD_H
#include <stdint.h>
#include <stddef.h>
struct aneTDItem {
    uint32_t    intIdx;
    uint8_t     bitSht;
    uint8_t     bitLen;
    const char  *name;
};
struct aneTDItemInt {
    const struct aneTDItem *start;
    size_t count;
};
enum aneTDv5Type {
    v5TDHeader,
    v5KernelDMASrc,
    v5Common,
    v5TileDMASrc,
    v5L2,
    v5NE,
    v5TileDMADst
};
extern const struct aneTDItem aneTDHeader_v5[];
extern const struct aneTDItem aneRegsKernelDMASrc_v5[];
extern const struct aneTDItem aneRegsCommon_v5[];
extern const struct aneTDItem aneRegsTileDMASrc_v5[];
extern const struct aneTDItem aneRegsL2_v5[];
extern const struct aneTDItem aneRegsNE_v5[];
extern const struct aneTDItem aneRegsTileDMADst_v5[];
int printANETDv5(enum aneTDv5Type type, size_t intIdx, size_t spaces, uint32_t intValue, int DMAIdx);
#endif//ANETD_H
