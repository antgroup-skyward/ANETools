#include <stdio.h>
#include "ANETD.h"
const struct aneTDItem aneTDHeader_v5[] = {
    {0, 0,  16, "aneTD.Header[0].TID"}, // +24 
    {0, 16, 8,  "aneTD.Header[0].NID"},
    {0, 24, 1,  "aneTD.Header[0].LNID"},
    {0, 25, 1,  "aneTD.Header[0].EON"},
    {1, 0,  16, "aneTD.Header[1].ExeCycles"},
    {1, 16, 8,  "aneTD.Header[1].NextSize"},
    {2, 0,  16, "aneTD.Header[2].LogEvents"},
    {2, 16, 16, "aneTD.Header[2].Exceptions"},
    {3, 0,  16, "aneTD.Header[3].DebugLogEvents"},
    {3, 16, 16, "aneTD.Header[3].DebugExceptions"},
    {4, 11, 1,  "aneTD.Header[4].SPL"},
    {4, 12, 1,  "aneTD.Header[4].TSR"},
    {4, 13, 1,  "aneTD.Header[4].SPC"},
    {4, 14, 1,  "aneTD.Header[4].DPC"},
    {4, 15, 1,  "aneTD.Header[4].TSE"},
    {4, 16, 6,  "aneTD.Header[4].NextPriority"},
    {4, 24, 1,  "aneTD.Header[4].TDE"},
    {4, 28, 1,  "aneTD.Header[4].SrcLoc"},
    {4, 29, 1,  "aneTD.Header[4].DstLoc"},
    {4, 31, 1,  "aneTD.Header[4].TQDis"},
    {5, 0,  32, "aneTD.Header[5].NextPointer"},
    {6, 0,  3,  "aneTD.Header[6].KBase"},
    {6, 3,  1,  "aneTD.Header[6].KBE"},
    {6, 4,  3,  "aneTD.Header[6].RBase"},
    {6, 7,  1,  "aneTD.Header[6].RBE"},
    {6, 8,  3,  "aneTD.Header[6].WBase"},
    {6, 11, 1,  "aneTD.Header[6].WBE"},
    {6, 12, 3,  "aneTD.Header[6].TBase"},
    {6, 15, 1,  "aneTD.Header[6].TBE"},
    {6, 16, 8,  "aneTD.Header[6].ENE"},
    {7, 0,  16, "aneTD.Header[7].DTID"},
};
const struct aneTDItemInt aneTDHeaderInt_v5[] = {
    {&aneTDHeader_v5[0], 4},
    {&aneTDHeader_v5[4], 2},
    {&aneTDHeader_v5[6], 2},
    {&aneTDHeader_v5[8], 2},
    {&aneTDHeader_v5[10], 10},
    {&aneTDHeader_v5[20], 1},
    {&aneTDHeader_v5[21], 9},
    {&aneTDHeader_v5[30], 1},
};

const struct aneTDItem aneRegsKernelDMASrc_v5[] = {
    {0, 0,  1,  "aneRegs.KernelDMASrc[%u].DMAConfig.En"}, // (*+56)+4
    {0, 4,  1,  "aneRegs.KernelDMASrc[%u].DMAConfig.CrH"},
    {0, 12, 4,  "aneRegs.KernelDMASrc[%u].DMAConfig.CacheHint"},
    {0, 28, 1,  "aneRegs.KernelDMASrc[%u].DMAConfig.PrefetchParticipateEn"},
    {1, 6,  26, "aneRegs.KernelDMASrc[%u].BaseAddr.Addr"},
    {2, 6,  11, "aneRegs.KernelDMASrc[%u].BfrSize.MemBfrSize"},
    {3, 0,  32, "aneRegs.KernelDMASrc[%u].Spare0.Spare"},
    {4, 0,  32, "aneRegs.KernelDMASrc[%u].Spare1.Spare"},
};
const struct aneTDItemInt aneRegsKernelDMASrcInt_v5[] = {
    {&aneRegsKernelDMASrc_v5[0], 4},
    {&aneRegsKernelDMASrc_v5[4], 1},
    {&aneRegsKernelDMASrc_v5[5], 1},
    {&aneRegsKernelDMASrc_v5[6], 1},
    {&aneRegsKernelDMASrc_v5[7], 1},
};

const struct aneTDItem aneRegsCommon_v5[] = { //+84
    {0, 0,  15, "aneRegs.Common.InDim.Win"},
    {0, 16, 15, "aneRegs.Common.InDim.Hin"},
    {1, 0,  2,  "aneRegs.Common.ChCfg.InFmt"},
    {1, 4,  2,  "aneRegs.Common.ChCfg.OutFmt"},
    {2, 0,  17, "aneRegs.Common.Cin.Cin"},
    {3, 0,  17, "aneRegs.Common.Cout.Cout"},
    {4, 0,  15, "aneRegs.Common.OutDim.Wout"},
    {4, 16, 15, "aneRegs.Common.OutDim.Hout"},
    {5, 0,  5,  "aneRegs.Common.ConvCfg.Kw"},
    {5, 6,  5,  "aneRegs.Common.ConvCfg.Kh"},
    {5, 12, 3,  "aneRegs.Common.ConvCfg.OCGSize"},
    {5, 16, 2,  "aneRegs.Common.ConvCfg.Sx"},
    {5, 18, 2,  "aneRegs.Common.ConvCfg.Sy"},
    {5, 20, 4,  "aneRegs.Common.ConvCfg.Px"},
    {5, 24, 4,  "aneRegs.Common.ConvCfg.Py"},
    {5, 28, 2,  "aneRegs.Common.ConvCfg.Ox"},
    {5, 30, 2,  "aneRegs.Common.ConvCfg.Oy"},
    {6, 0,  13, "aneRegs.Common.GroupConvCfg.NumGroups"},
    {6, 14, 1,  "aneRegs.Common.GroupConvCfg.UnicastEn"},
    {6, 15, 1,  "aneRegs.Common.GroupConvCfg.ElemMultMode"},
    {6, 16, 16, "aneRegs.Common.GroupConvCfg.UnicastCin"},
    {7, 0,  15, "aneRegs.Common.TileCfg.TileHeight"},
    {8, 2,  1,  "aneRegs.Common.Cfg.SmallSourceMode"},
    {8, 8,  3,  "aneRegs.Common.Cfg.ShPref"},
    {8, 12, 3,  "aneRegs.Common.Cfg.ShMin"},
    {8, 16, 3,  "aneRegs.Common.Cfg.ShMax"},
    {8, 19, 2,  "aneRegs.Common.Cfg.ActiveNE"},
    {8, 22, 1,  "aneRegs.Common.Cfg.ContextSwitchIn"},
    {8, 24, 1,  "aneRegs.Common.Cfg.ContextSwitchOut"},
    {8, 26, 1,  "aneRegs.Common.Cfg.AccDoubleBufEn"},
    {9, 0,  16, "aneRegs.Common.TaskInfo.TaskID"},
    {9, 16, 3,  "aneRegs.Common.TaskInfo.TaskQ"},
    {9, 20, 8,  "aneRegs.Common.TaskInfo.NID"},
    {10,0,  4,  "aneRegs.Common.DPE.Category"},
    {11,0,  32, "aneRegs.Common.Spare0.Spare"},
    {12,0,  32, "aneRegs.Common.Spare1.Spare"},
};
const struct aneTDItemInt aneRegsCommonInt_v5[] = {
    {&aneRegsCommon_v5[0], 2},
    {&aneRegsCommon_v5[2], 2},
    {&aneRegsCommon_v5[4], 1},
    {&aneRegsCommon_v5[5], 1},
    {&aneRegsCommon_v5[6], 2},
    {&aneRegsCommon_v5[8], 9},
    {&aneRegsCommon_v5[17], 4},
    {&aneRegsCommon_v5[21], 1},
    {&aneRegsCommon_v5[22], 8},
    {&aneRegsCommon_v5[30], 3},
    {&aneRegsCommon_v5[33], 1},
    {&aneRegsCommon_v5[34], 1},
    {&aneRegsCommon_v5[35], 1},
};

const struct aneTDItem aneRegsTileDMASrc_v5[] = { //+140
    {0, 0,  1,  "aneRegs.TileDMASrc.DMAConfig.En"},
    {0, 4,  1,  "aneRegs.TileDMASrc.DMAConfig.CrH"},
    {0, 12, 4,  "aneRegs.TileDMASrc.DMAConfig.CacheHint"},
    {0, 16, 4,  "aneRegs.TileDMASrc.DMAConfig.CacheHintReuse"},
    {0, 20, 4,  "aneRegs.TileDMASrc.DMAConfig.CacheHintNoReuse"},
    {0, 24, 2,  "aneRegs.TileDMASrc.DMAConfig.DependencyMode"},
    {1, 6,  26, "aneRegs.TileDMASrc.BaseAddr.Addr"},
    {2, 6,  24, "aneRegs.TileDMASrc.Stride.Stride"},
    {3, 6,  24, "aneRegs.TileDMASrc.PlaneStride.PlaneStride"},
    {4, 0,  2,  "aneRegs.TileDMASrc.Fmt.FmtMode"},
    {4, 4,  2,  "aneRegs.TileDMASrc.Fmt.Truncate"},
    {4, 8,  1,  "aneRegs.TileDMASrc.Fmt.Shift"},
    {4, 12, 2,  "aneRegs.TileDMASrc.Fmt.MemFmt"},
    {4, 16, 3,  "aneRegs.TileDMASrc.Fmt.OffsetCh"},
    {4, 24, 4,  "aneRegs.TileDMASrc.Fmt.Interleave"},
    {4, 28, 4,  "aneRegs.TileDMASrc.Fmt.CmpVec"},
    {5, 0,  16, "aneRegs.TileDMASrc.PixelOffset[0].Offset"},
    {6, 0,  16, "aneRegs.TileDMASrc.PixelOffset[1].Offset"},
    {7, 0,  16, "aneRegs.TileDMASrc.PixelOffset[2].Offset"},
    {8, 0,  16, "aneRegs.TileDMASrc.PixelOffset[3].Offset"},
    {9, 0,  32, "aneRegs.TileDMASrc.Spare0.Spare"},
    {10,0,  32, "aneRegs.TileDMASrc.Spare1.Spare"},
};
const struct aneTDItemInt aneRegsTileDMASrcInt_v5[] = {
    {&aneRegsTileDMASrc_v5[0], 6},
    {&aneRegsTileDMASrc_v5[6], 1},
    {&aneRegsTileDMASrc_v5[7], 1},
    {&aneRegsTileDMASrc_v5[8], 1},
    {&aneRegsTileDMASrc_v5[9], 7},
    {&aneRegsTileDMASrc_v5[16], 1},
    {&aneRegsTileDMASrc_v5[17], 1},
    {&aneRegsTileDMASrc_v5[18], 1},
    {&aneRegsTileDMASrc_v5[19], 1},
    {&aneRegsTileDMASrc_v5[20], 1},
    {&aneRegsTileDMASrc_v5[21], 1},
};

const struct aneTDItem aneRegsL2_v5[] = { //+188
    {0, 0,  1,  "aneRegs.L2.L2Cfg.InputReLU"},
    {0, 2,  1,  "aneRegs.L2.L2Cfg.PaddingMode"},
    {1, 0,  2,  "aneRegs.L2.TileSourceCfg.TileSourceType"},
    {1, 2,  1,  "aneRegs.L2.TileSourceCfg.Dependent"},
    {1, 4,  1,  "aneRegs.L2.TileSourceCfg.AliasSrc"},
    {1, 5,  1,  "aneRegs.L2.TileSourceCfg.AliasConv"},
    {1, 6,  2,  "aneRegs.L2.TileSourceCfg.DMAFmt"},
    {1, 8,  4,  "aneRegs.L2.TileSourceCfg.DMAInterleave"},
    {1, 12, 4,  "aneRegs.L2.TileSourceCfg.DMACmpVec"},
    {1, 16, 3,  "aneRegs.L2.TileSourceCfg.DMAOffsetCh"},
    {2, 4,  17, "aneRegs.L2.TileSourceBase.Addr"},
    {2, 0,  4,  "aneRegs.L2.TileSourceBase.Sox"},
    {3, 4,  12, "aneRegs.L2.TileSourceChannelStride.Stride"},
    {4, 4,  16, "aneRegs.L2.TileSourceRowStride.Stride"},
    {5, 0,  2,  "aneRegs.L2.ConvResultCfg.ConvResultType"},
    {5, 3,  1,  "aneRegs.L2.ConvResultCfg.L2BfrMode"},
    {5, 4,  1,  "aneRegs.L2.ConvResultCfg.AliasSrc"},
    {5, 5,  1,  "aneRegs.L2.ConvResultCfg.AliasConv"},
    {5, 6,  2,  "aneRegs.L2.ConvResultCfg.DMAFmt"},
    {5, 8,  4,  "aneRegs.L2.ConvResultCfg.DMAInterleave"},
    {5, 12, 4,  "aneRegs.L2.ConvResultCfg.DMACmpVec"},
    {5, 16, 3,  "aneRegs.L2.ConvResultCfg.DMAOffsetCh"},
    {6, 4,  17, "aneRegs.L2.ConvResultBase.Addr"},
    {7, 4,  12, "aneRegs.L2.ConvResultChannelStride.Stride"},
    {8, 4,  16, "aneRegs.L2.ConvResultRowStride.Stride"},
    {9, 0,  32, "aneRegs.L2.Spare0.Spare"},
    {10,0,  32, "aneRegs.L2.Spare1.Spare"},
};
const struct aneTDItemInt aneRegsL2Int_v5[] = {
    {&aneRegsL2_v5[0], 2},
    {&aneRegsL2_v5[2], 8},
    {&aneRegsL2_v5[10], 2},
    {&aneRegsL2_v5[12], 1},
    {&aneRegsL2_v5[13], 1},
    {&aneRegsL2_v5[14], 8},
    {&aneRegsL2_v5[22], 1},
    {&aneRegsL2_v5[23], 1},
    {&aneRegsL2_v5[24], 1},
    {&aneRegsL2_v5[25], 1},
    {&aneRegsL2_v5[26], 1},
};

const struct aneTDItem aneRegsNE_v5[] = { //+236
    {0, 0,  2,  "aneRegs.NE.KernelCfg.KernelFmt"},
    {0, 2,  1,  "aneRegs.NE.KernelCfg.PalettizedEn"},
    {0, 4,  4,  "aneRegs.NE.KernelCfg.PalettizedBits"},
    {0, 8,  1,  "aneRegs.NE.KernelCfg.SparseFmt"},
    {0, 10, 1,  "aneRegs.NE.KernelCfg.GroupKernelReuse"},
    {1, 0,  3,  "aneRegs.NE.MACCfg.OpMode"},
    {1, 3,  1,  "aneRegs.NE.MACCfg.KernelMode"},
    {1, 4,  1,  "aneRegs.NE.MACCfg.BiasMode"},
    {1, 6,  1,  "aneRegs.NE.MACCfg.MatrixBiasEn"},
    {1, 8,  5,  "aneRegs.NE.MACCfg.BinaryPoint"},
    {1, 14, 1,  "aneRegs.NE.MACCfg.PostScaleMode"},
    {1, 16, 2,  "aneRegs.NE.MACCfg.NonlinearMode"},
    {2, 0,  16, "aneRegs.NE.MatrixVectorBias.MatrixVectorBias"},
    {3, 0,  16, "aneRegs.NE.AccBias.AccBias"},
    {3, 16, 5,  "aneRegs.NE.AccBias.AccBiasShift"},
    {4, 0,  16, "aneRegs.NE.PostScale.PostScale"},
    {4, 16, 5,  "aneRegs.NE.PostScale.PostRightShift"},
    {5, 0,  32, "aneRegs.NE.Spare0.Spare"},
    {6, 0,  32, "aneRegs.NE.Spare1.Spare"},
};
const struct aneTDItemInt aneRegsNEInt_v5[] = {
    {&aneRegsNE_v5[0], 5},
    {&aneRegsNE_v5[5], 7},
    {&aneRegsNE_v5[12], 1},
    {&aneRegsNE_v5[13], 2},
    {&aneRegsNE_v5[15], 2},
    {&aneRegsNE_v5[17], 1},
    {&aneRegsNE_v5[18], 1},
};

const struct aneTDItem aneRegsTileDMADst_v5[] = { //+268
    {0, 0,  1,  "aneRegs.TileDMADst.DMAConfig.En"},
    {0, 4,  1,  "aneRegs.TileDMADst.DMAConfig.CrH"},
    {0, 12, 4,  "aneRegs.TileDMADst.DMAConfig.CacheHint"},
    {0, 26, 1,  "aneRegs.TileDMADst.DMAConfig.L2BfrMode"},
    {0, 27, 1,  "aneRegs.TileDMADst.DMAConfig.BypassEOW"},
    {1, 6,  26, "aneRegs.TileDMADst.BaseAddr.Addr"},
    {2, 6,  24, "aneRegs.TileDMADst.Stride.Stride"},
    {3, 6,  24, "aneRegs.TileDMADst.PlaneStride.PlaneStride"},
    {4, 0,  2,  "aneRegs.TileDMADst.Fmt.FmtMode"},
    {4, 4,  2,  "aneRegs.TileDMADst.Fmt.Truncate"},
    {4, 8,  1,  "aneRegs.TileDMADst.Fmt.Shift"},
    {4, 12, 2,  "aneRegs.TileDMADst.Fmt.MemFmt"},
    {4, 16, 3,  "aneRegs.TileDMADst.Fmt.OffsetCh"},
    {4, 20, 1,  "aneRegs.TileDMADst.Fmt.ZeroPadLast"},
    {4, 21, 1,  "aneRegs.TileDMADst.Fmt.ZeroPadFirst"},
    {4, 22, 1,  "aneRegs.TileDMADst.Fmt.CmpVecFill"},
    {4, 24, 4,  "aneRegs.TileDMADst.Fmt.Interleave"},
    {4, 28, 4,  "aneRegs.TileDMADst.Fmt.CmpVec"},
    {5, 0,  32, "aneRegs.TileDMADst.Spare0.Spare"},
    {6, 0,  32, "aneRegs.TileDMADst.Spare1.Spare"},
};
const struct aneTDItemInt aneRegsTileDMADstInt_v5[] = {
    {&aneRegsTileDMADst_v5[0], 5},
    {&aneRegsTileDMADst_v5[5], 1},
    {&aneRegsTileDMADst_v5[6], 1},
    {&aneRegsTileDMADst_v5[7], 1},
    {&aneRegsTileDMADst_v5[8], 10},
    {&aneRegsTileDMADst_v5[18], 1},
    {&aneRegsTileDMADst_v5[19], 1},
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#endif
int printANETDv5(enum aneTDv5Type type, size_t intIdx, size_t spaces, uint32_t intValue, int DMAIdx) {
    const struct aneTDItemInt *itemInt = NULL;
    switch(type) {
#define v5CASE(type, arr)\
    case type:\
        if (intIdx >= ARRAY_SIZE(arr)) {\
            printf("out of bound of " #arr "\n");\
            return -1;\
        }\
        itemInt = &arr[intIdx];\
        break;
    v5CASE(v5TDHeader,      aneTDHeaderInt_v5);
    v5CASE(v5KernelDMASrc,  aneRegsKernelDMASrcInt_v5);
    v5CASE(v5Common,        aneRegsCommonInt_v5);
    v5CASE(v5TileDMASrc,    aneRegsTileDMASrcInt_v5);
    v5CASE(v5L2,            aneRegsL2Int_v5);
    v5CASE(v5NE,            aneRegsNEInt_v5);
    v5CASE(v5TileDMADst,    aneRegsTileDMADstInt_v5);
    default:
        printf("bad type\n");
        return -1;
    }
    size_t i;
    for (i = 0; i < itemInt->count; ++i) {
        size_t j;
        for (j = 0; j < spaces; ++j)
            printf(" ");
        uint8_t bitSht = itemInt->start[i].bitSht;
        uint8_t bitLen = itemInt->start[i].bitLen;
        for (j = 0; j < 32; ++j) {
            if ((bitSht + bitLen) > 32) {
                printf("bad aneTDItem\n");
                return -1;
            }
            if (j < (32 - (bitSht + bitLen)) || j >= (32 - bitSht)) {
                printf("-");
            } else {
                if (intValue & (1u << (31 - j)))
                    printf("1");
                else
                    printf("0");
            }
        }
        printf(" ");
        uint32_t value = (uint32_t)(((uint64_t)intValue >> bitSht) & ((1ull << bitLen) - 1ull));
        printf("%8u %#10x ", value, value);
        const char *name = itemInt->start[i].name;
        if (DMAIdx != -1)
            printf(name, DMAIdx);
        else
            printf("%s", name);
        printf("\n");
    }
    return 0;
}
