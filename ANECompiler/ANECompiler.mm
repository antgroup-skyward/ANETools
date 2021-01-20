#include "ANECompiler.h"

static struct ANECOption gTestVectors[] = {
    {"TestVectorSymbolName",                AO_STRING, "string"},
    {"TestVectorFileName",                  AO_STRING, "string"},
    {"TestVectorFilePath",                  AO_STRING, "string"},
};
static struct ANECOption gExterns[] = {
    {"Extern",                              AO_STRING, "string"},
};
static struct ANECOption gProcedureParams[] = {
    {"Name",                                AO_STRING, "string"},
    {"KernelRewind",                        AO_BOOL, "bool"},
    {"ScanWeightsForCompression",           AO_BOOL, "bool"},
    {"DisableMergeScaleBias",               AO_BOOL, "bool"},
    {"EnableSingleChannelEWOpCopyRemoval",  AO_BOOL, "bool"},
    {"EnableAggressiveTensorCaching",       AO_BOOL, "bool"},
};
static struct ANECOption gANEOptions[] = {
//Input Output
    // InputNetworks Array only support one net and one weights now
    {"NetworkPlistName",    AO_STRING, "string name of net.plist"},
    {"NetworkPlistPath",    AO_STRING, "string dir of net.plist"},
    {"WeightFileName",      AO_STRING, "string name of weights"},
    {"WeightFilePath",      AO_STRING, "string dir of weights"},
    {"OutputFileName",      AO_STRING, "string output file name of model.hwx"},
    {"OutputFilePath",      AO_STRING, "string output dir of model.hwx"},
//Options
    {"OptionsFilePath",                     AO_STRING, "string file path"},
    //Array TestVectors
    {"TestVectors",                         AO_ARRAY, "array"},
    //Array Externs
    {"Externs",                             AO_ARRAY, "array"},
    {"UndefinedSymbolsBehaviorUseFVMLibs",  AO_BOOL, "bool"},
    {"ForceCoalescedExternSections",        AO_BOOL, "bool"},
    {"TargetArchitecture",                  AO_STRING, "string t0,m9,h11,h12,h13"},
    {"FoldScale",                           AO_BOOL, "bool"},
    {"DisableContextSwitching",             AO_BOOL, "bool"},
    {"DebugContextSwitchingDma",            AO_BOOL, "bool"},
    {"DisableMergeConstants",               AO_BOOL, "bool"},
    {"ForceHazardStalls",                   AO_BOOL, "bool"},
    {"DebugMask",                           AO_NUMBER, "number"},
    {"L3Size",                              AO_NUMBER, "number"},
    {"OptLvlOne",                           AO_BOOL, "bool"},
    {"DisableOptimizations",                AO_BOOL, "bool"},
    {"DisableMergeScaleBias",               AO_BOOL, "bool"},
    {"DisableMergeActivation",              AO_BOOL, "bool"},
    {"DisableDeadCodeElimination",          AO_BOOL, "bool"},
    {"DisableStrideUnitarization",          AO_BOOL, "bool"},
    {"CompressSparseKernels",               AO_BOOL, "bool"},
    {"DisableAdjustInterleaveFactor",       AO_BOOL, "bool"},
    {"DisableCompression",                  AO_BOOL, "bool"},
    {"EnableKernelRewind",                  AO_BOOL, "bool"},
    {"CompileANEProgramForDebugging",       AO_BOOL, "bool"},
    {"DramTensorPriorityType",              AO_STRING, "string NoReuse,FirstFitReuse,BestFitReuse"},
    {"DramAllocatorType",                   AO_STRING, "string orderofcreation,costofreads,sizethenliverange"},
    {"L2AllocatorType",                     AO_STRING, "string FirstFitReuse,BestFitReuse"},
    {"L2CacheMode",                         AO_STRING, "string L2EnableResident,L2DisableResident,L2EnableCachedWrite,L2EnabledCachedReadWrite"},
    {"L3AllocatorType",                     AO_STRING, "string NoReuse,FirstFitReuse,BestFitReuse"},
    {"DisableL2Wraparound",                 AO_BOOL, "bool"},
    {"DisableL2BankConflictOpt",            AO_BOOL, "bool"},
    {"InputAndConstantCaching",             AO_BOOL, "bool"},
    {"EnableSingleChannelElementwiseOpCopyRemoval", AO_BOOL, "bool"},
    {"EnableAggressiveTensorCaching",       AO_BOOL, "bool"},
    {"ProduceRelocatableObjects",           AO_BOOL, "bool"},
    {"Signature",                           AO_STRING, "string Disabled,Ident"},
    {"UseNewMachoMagicNumber",              AO_BOOL, "bool"},
    {"MemCacheStrategy",                    AO_STRING, "string None,Simple"},
    {"MemCacheSize",                        AO_BOOL, "number"},
    {"SpatialSplit",                        AO_STRING, "string Disabled,Test,Memory,Auto"},
    {"KernelRewind",                        AO_BOOL, "bool"},
    {"ScanWeightsForCompression",           AO_BOOL, "bool"},
    //Array ProcedureParams
    {"ProcedureParams",                     AO_ARRAY, "array"},
};
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#endif
static void printOptions(void) {
    size_t i;
    printf("Options:\n");
    for (i = 0; i < ARRAY_SIZE(gANEOptions); ++i) {
        printf("%44s %s\n", gANEOptions[i].name, gANEOptions[i].desc);
    }
    printf("TestVectors Array:\n");
    for (i = 0; i < ARRAY_SIZE(gTestVectors); ++i) {
        printf("%44s %s\n", gTestVectors[i].name, gTestVectors[i].desc);
    }
    printf("Externs Array:\n");
    for (i = 0; i < ARRAY_SIZE(gExterns); ++i) {
        printf("%44s %s\n", gExterns[i].name, gExterns[i].desc);
    }
    printf("ProcedureParams Array:\n");
    for (i = 0; i < ARRAY_SIZE(gProcedureParams); ++i) {
        printf("%44s %s\n", gProcedureParams[i].name, gProcedureParams[i].desc);
    }
}
static void printHelp(void) {
    printf("usage: ANECompiler  -in <net.plist> -out <model.hwx> [-o<name>=<value>]\n");
    printf("    -in <net.plist file> equals -oNetworkPlistPath=<dir of net.plist> -oNetworkPlistName=<name of net.plist>\n");
    printf("    -out <model.hwx file> equals -oOutputFilePath=<dir of model.hwx> -oOutputFileName=<name of model.hwx>\n");
    printf("    -arch <one of t0,m9,h11,h12,h13> equals -oTargetArchitecture=<arch>\n");
    printf("    -debug equals -oDebugMask=0x7fffffff -oCompileANEProgramForDebugging=true\n");
    printf("    -o<option name>=<value> For array -o<option name>=<value>,<value>,...\n");
    printOptions();
}
/*
dic
    arr InputNetworks
        dic
            str NetworkPlistName
            str NetworkPlistPath
            arr NetworkWeights
                dic
                    str WeightFileName
                    str WeightFilePath
    str OutputFileName
    str OutputFilePath
*/
static int parseArgs(int argc, char **argv, CFDictionaryRef *pios, CFDictionaryRef *popts) {
    CFMutableDictionaryRef ios = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    CFMutableDictionaryRef opts = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    ///*
    CFMutableArrayRef InputNetworks = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
    CFMutableDictionaryRef OneNetwork = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    //*/
    size_t i;
    for (i = 0; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "-in") == 0) {
            if (CFDictionaryContainsKey(ios, CFSTR("InputNetworks"))) {
                printf("bad arg : -in already set\n");
                return -1;
            }
            if ((i + 1) >= argc) {
                printf("bad arg : lost arg after -in\n");
                return -1;
            }
            char *dir = dirname(argv[i + 1]);
            char dirSlash[2048];
            if ((strlen(dir) + 1) > sizeof(dirSlash)) {
                printf("bad arg : directory too long.\n");
                return -1;
            }
            dirSlash[sizeof(dirSlash) - 1] = '\0';
            snprintf(dirSlash, sizeof(dirSlash) - 1, "%s/", dir);
            CFStringRef NetworkPlistPath = CFStringCreateWithCString(kCFAllocatorDefault, dirSlash, kCFStringEncodingUTF8);
            char *name = basename(argv[i + 1]);
            CFStringRef NetworkPlistName = CFStringCreateWithCString(kCFAllocatorDefault, name, kCFStringEncodingUTF8);
            CFDictionaryAddValue(OneNetwork, CFSTR("NetworkPlistName"), NetworkPlistName);
            CFDictionaryAddValue(OneNetwork, CFSTR("NetworkPlistPath"), NetworkPlistPath);
            CFArrayAppendValue(InputNetworks, OneNetwork);
            /*
            CFTypeRef keys[2];
            keys[0] = CFSTR("NetworkPlistName");
            keys[1] = CFSTR("NetworkPlistPath");
            CFTypeRef values[2];
            values[0] = NetworkPlistName;
            values[1] = NetworkPlistPath;
            CFDictionaryRef OneNetwork = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
            CFArrayRef InputNetworks = CFArrayCreate(kCFAllocatorDefault, (const void**)&OneNetwork, 1, &kCFTypeArrayCallBacks);
            */
            CFDictionaryAddValue(ios, CFSTR("InputNetworks"), InputNetworks);
        } else if (strcmp(arg, "-out") == 0) {
            if (CFDictionaryContainsKey(ios, CFSTR("OutputFileName"))) {
                printf("bad arg : -out already set\n");
                return -1;
            }
            if ((i + 1) >= argc) {
                printf("bad arg : lost arg after -out\n");
                return -1;
            }
            char *dir = dirname(argv[i + 1]);
            char dirSlash[2048];
            if ((strlen(dir) + 1) > sizeof(dirSlash)) {
                printf("bad arg : directory too long.\n");
                return -1;
            }
            dirSlash[sizeof(dirSlash) - 1] = '\0';
            snprintf(dirSlash, sizeof(dirSlash) - 1, "%s/", dir);
            CFStringRef OutputFilePath = CFStringCreateWithCString(kCFAllocatorDefault, dirSlash, kCFStringEncodingUTF8);
            char *name = basename(argv[i + 1]);
            CFStringRef OutputFileName = CFStringCreateWithCString(kCFAllocatorDefault, name, kCFStringEncodingUTF8); 
            CFDictionaryAddValue(ios, CFSTR("OutputFileName"), OutputFileName);
            CFDictionaryAddValue(ios, CFSTR("OutputFilePath"), OutputFilePath);
        } else if (strcmp(arg, "-debug") == 0) {
            int debug_mask = 0x7fffffff;
            CFDictionaryAddValue(opts, CFSTR("DebugMask"), CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &debug_mask));
            CFDictionaryAddValue(opts, CFSTR("CompileANEProgramForDebugging"), kCFBooleanTrue);
            CFDictionaryAddValue(opts, CFSTR("DisableRegisterPacking"), kCFBooleanTrue);
        } else if (strcmp(arg, "-arch") == 0) {
            if (CFDictionaryContainsKey(ios, CFSTR("TargetArchitecture"))) {
                printf("bad arg : -arch already set\n");
                return -1;
            }
            if ((i + 1) >= argc) {
                printf("bad arg : lost arg after -out\n");
                return -1;
            }
            CFStringRef Arch = CFStringCreateWithCString(kCFAllocatorDefault, argv[i+1], kCFStringEncodingUTF8);
            CFDictionaryAddValue(opts, CFSTR("TargetArchitecture"), Arch);
        } else if (strncmp(arg, "-o", 2) == 0) {
            printf("TODO...\n");
            return -1;
        }
    }
    if (!CFDictionaryContainsKey(opts, CFSTR("TargetArchitecture"))) {
        printf("using default TargetArchitecture h13\n");
        CFDictionaryAddValue(opts, CFSTR("TargetArchitecture"), CFSTR("h13"));
    }
    if (!CFDictionaryContainsKey(ios, CFSTR("OutputFileName")) || !CFDictionaryContainsKey(ios, CFSTR("InputNetworks"))) {
        printf("bad arg : lost necessary -in or -out\n");
        return -1;
    }
//CFDictionaryAddValue(opts, CFSTR("DisableRegisterPacking"), kCFBooleanTrue);
    *pios = ios;
    *popts = opts;
    return 0;    
}
int main(int argc, char **argv) {
    if (argc <= 1) {
        printHelp();
        return -1;
    }
    CFDictionaryRef ios, opts;
    if (parseArgs(argc--, argv++, &ios, &opts) != 0) {
        printf("parseArgs failed\n");
        return -1;
    }
    //CFShow(ios);
    //CFShow(opts);
    int ret = ANECCompile(ios, opts, 0);
    printf("ANECCompile() return %d\n", ret);
    return 0;
}
#define DUMP_INST
extern "C" void handleAneInstruction(std::list<ZinAneInstruction *> &insts) {
#ifdef DUMP_INST
    size_t instCount = 0;
#endif
    int val = *((int *)(_ZNK11ZinIrHalH119GetParamsEv(NULL) + 4));
    printf("ZinIrHalH11::GetParams(this) + 4 == %d\n", val);
    val = *((int *)(_ZNK11ZinIrHalH129GetParamsEv(NULL) + 4));
    printf("ZinIrHalH12::GetParams(this) + 4 == %d\n", val);
    val = *((int *)(_ZNK11ZinIrHalH139GetParamsEv(NULL) + 4));
    printf("ZinIrHalH13::GetParams(this) + 4 == %d\n", val);
    printf("insts.size() == %lu\n", insts.size());
    std::list<ZinAneInstruction *>::iterator it;
    for(it = insts.begin(); it != insts.end(); ++it) {
        ZinAneInstruction *inst = *it;
        printf("\n\n----------------------------------------------------------------%p\n", inst->td->ZinHWTraits);
        _Z24ZinIrRegBitPrintOutDebugILj7EE11ZinIrStatusjRN11ZinHWTraitsIXT_EE6HwTypeEiRNSt3__113basic_ostreamIcNS5_11char_traitsIcEEEE(
                instCount, inst->td->ZinHWTraits, val, std::cout);
#ifdef DUMP_INST
        char path[64];
        snprintf(path, sizeof(path), "inst%lu.dump", instCount);
        FILE *fp = fopen(path, "wb");
        if (fp == NULL) {
            printf("open %s failed\n", path);
            continue;
        }
        if (fwrite(inst->td->ZinHWTraits, sizeof(inst->td->ZinHWTraits), 1, fp) != 1) {
            printf("fwrite %s failed\n", path);
        }
        fclose(fp);
        instCount++;
#endif
    }
}
