#ifndef ANECompiler_H
#define ANECompiler_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <string>
#include <iostream>
#include <list>
#import <CoreFoundation/CoreFoundation.h>
enum ANEOptionType {
    AO_BOOL,
    AO_STRING,
    AO_NUMBER,
    AO_ARRAY
};
struct ANECOption {
    const char      *name;
    ANEOptionType   type;
    const char      *desc;
};
struct __attribute__((packed)) ZinAneTd {
    uintptr_t   vtbl;
    uint8_t     ZinHWTraits[848];
    uintptr_t   target_hw_limits_v7;
    uintptr_t   pad;
};
struct __attribute__((packed)) ZinAneInstruction {
    uint8_t         pad0[80];
    uint32_t        align; //+80
    uint8_t         pad1[4];
    struct ZinAneTd *td; // +88 size = 872 from ZinIrCodegenHandleTdsMakeList<7u>
};
extern "C" {
    int ANECCompile(CFDictionaryRef ios, CFDictionaryRef opts, uintptr_t a3);
    int _Z24ZinIrRegBitPrintOutDebugILj7EE11ZinIrStatusjRN11ZinHWTraitsIXT_EE6HwTypeEiRNSt3__113basic_ostreamIcNS5_11char_traitsIcEEEE(
            unsigned int, void * /*ZinHWTraits<7u>::HwType &*/, int, std::ostream &);
    uint8_t *_ZNK11ZinIrHalH139GetParamsEv(void *thiz);
    uint8_t *_ZNK11ZinIrHalH129GetParamsEv(void *thiz);
    uint8_t *_ZNK11ZinIrHalH119GetParamsEv(void *thiz);
    uint8_t *_ZNK10ZinIrHalT09GetParamsEv(void *thiz);
    uint8_t *_ZNK10ZinIrHalM99GetParamsEv(void *thiz);
}
#endif//ANECompiler_H
