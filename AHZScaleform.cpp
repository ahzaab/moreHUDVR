#include <wchar.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <list>
#include <algorithm>
#include "skse64/GameReferences.h"
#include "skse64/GameObjects.h"
#include "skse64/GameRTTI.h"
#include "skse64/GameSettings.h"
#include "skse64/GameExtraData.h"
#include "skse64/ScaleformCallbacks.h"
#include "skse64/ScaleformMovie.h"
#include "skse64/GameMenus.h"
#include "skse64_common/Utilities.h"
#include "AHZArmorInfo.h"
#include "AHZWeaponInfo.h"
#include "AHZScaleform.h"
#include "AHZScaleformHook.h"
#include "AHZFormLookup.h"
#include "AHZUtilities.h"

static std::map<UInt8, string> m_soulMap;

//Unpacked
//HxD Raw FF C0 83 F8 07 77 0A F3 0F 10 8A 70 01 00 00 EB 54 4C 8D 0D 80 B3 A7 01 C7 44 24 20 00 00 00 00
RelocAddr<GET_ACTOR_WARMTH_RATING> GetActorWarmthRating_Native(0x003BD5F0);

//text:00007FF7F661D850; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//   .text:00007FF7F661D850
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850                         sub_7FF7F661D850 proc near; CODE XREF : sub_7FF7F6537280 + 2E↑p
//   .text : 00007FF7F661D850; sub_7FF7F6B0F2F0 + 129↓p ...
//   .text:00007FF7F661D850
//   .text : 00007FF7F661D850                         var_38 = qword ptr - 38h
//   .text : 00007FF7F661D850                         var_30 = qword ptr - 30h
//   .text : 00007FF7F661D850                         var_28 = dword ptr - 28h
//   .text : 00007FF7F661D850                         var_18 = xmmword ptr - 18h
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850; FUNCTION CHUNK AT.text:00007FF7F661DCD0 SIZE 0000000B BYTES
//   .text : 00007FF7F661D850; FUNCTION CHUNK AT.text:00007FF7F7605A05 SIZE 0000000C BYTES
//   .text : 00007FF7F661D850
//   .text : 00007FF7F661D850; __unwind{ // __CxxFrameHandler3
//   .text:00007FF7F661D850 40 53                                   push    rbx
//   .text : 00007FF7F661D852 48 83 EC 50                             sub     rsp, 50h
//   .text : 00007FF7F661D856 48 C7 44 24 20 FE FF FF + mov[rsp + 58h + var_38], 0FFFFFFFFFFFFFFFEh
//   .text : 00007FF7F661D85F 0F 29 74 24 40                          movaps[rsp + 58h + var_18], xmm6
//   .text : 00007FF7F661D864 48 8B D9                                mov     rbx, rcx
//   .text : 00007FF7F661D867 0F 57 F6                                xorps   xmm6, xmm6
//   .text : 00007FF7F661D86A E8 91 B7 E1 FF                          call    sub_7FF7F6439000
//   .text : 00007FF7F661D86F 48 85 C0                                test    rax, rax
//   .text : 00007FF7F661D872 74 27                                   jz      short loc_7FF7F661D89B
//   .text : 00007FF7F661D874 48 8D 0D E5 44 21 01                    lea     rcx, ? ? _7WarmthCalcFunc@?A0x527f96c7@@6B@; const `anonymous namespace'::WarmthCalcFunc::`vftable'
//   .text:00007FF7F661D87B 48 89 4C 24 28                          mov[rsp + 58h + var_30], rcx
//   .text : 00007FF7F661D880 C7 44 24 30 00 00 00 00                 mov[rsp + 58h + var_28], 0
//   .text : 00007FF7F661D888
//   .text : 00007FF7F661D888                         loc_7FF7F661D888 : ; DATA XREF : .rdata : 00007FF7F7CBDB9C↓o
//   .text : 00007FF7F661D888;   try {
//   .text:00007FF7F661D888 48 8D 54 24 28                          lea     rdx,[rsp + 58h + var_30]
//      .text : 00007FF7F661D88D 48 8B C8                                mov     rcx, rax
//      .text : 00007FF7F661D890 E8 1B 7B E2 FF                          call    sub_7FF7F64453B0
//      .text : 00007FF7F661D895 F3 0F 10 74 24 30                       movss   xmm6,[rsp + 58h + var_28]
//      .text : 00007FF7F661D895;
//} // starts at 7FF7F661D888
//     .text:00007FF7F661D89B
//        .text : 00007FF7F661D89B                         loc_7FF7F661D89B : ; CODE XREF : sub_7FF7F661D850 + 22↑j
//        .text : 00007FF7F661D89B; DATA XREF : .rdata : 00007FF7F7CBDBA4↓o
//        .text : 00007FF7F661D89B 48 8D 8B B0 00 00 00                    lea     rcx,[rbx + 0B0h]
//        .text : 00007FF7F661D8A2 48 8B 01                                mov     rax,[rcx]
//        .text : 00007FF7F661D8A5 BA 4C 00 00 00                          mov     edx, 4Ch
//        .text : 00007FF7F661D8AA FF 50 08                                call    qword ptr[rax + 8]
//        .text:00007FF7F661D8AD F3 0F 58 C6                             addss   xmm0, xmm6
//        .text : 00007FF7F661D8B1 0F 28 74 24 40                          movaps  xmm6,[rsp + 58h + var_18]
//        .text : 00007FF7F661D8B6 48 83 C4 50                             add     rsp, 50h
//        .text : 00007FF7F661D8BA 5B                                      pop     rbx
//        .text : 00007FF7F661D8BB C3                                      retn
//        .text : 00007FF7F661D8BB; } // starts at 7FF7F661D850
//   .text:00007FF7F661D8BB                         sub_7FF7F661D850 endp
//        .text : 00007FF7F661D8BB
//        .text : 00007FF7F661D8BB; -------------------------------------------------------------------------- -
//        .text:00007FF7F661D8BC                         algn_7FF7F661D8BC : ; DATA XREF : .pdata : 00007FF7F97668D0↓o
//        .text : 00007FF7F661D8BC CC CC CC CC                             align 20h

//Unpacked 
//Hxd Raw F0 44 0F 28 44 24 30 0F 28 C6 0F 28 74 24 50 48 83 C4 60 5F C3 0F 1F 00 7D E2 3B 00 7D E2 3B 00
RelocAddr<GET_ARMOR_WARMTH_RATING>GetArmorWarmthRating_Native(0x003BD510);

//text:00007FF7F661D770
//   .text : 00007FF7F661D770; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//   .text:00007FF7F661D770
//   .text : 00007FF7F661D770
//   .text : 00007FF7F661D770; float __fastcall GetWarmth(TESForm *a1)
//   .text:00007FF7F661D770                         GetWarmth       proc near; CODE XREF : sub_7FF7F661DF90 + 11↓p
//   .text : 00007FF7F661D770; GetTotalArmorAndWarmth + 1FB↓p ...
//   .text:00007FF7F661D770
//   .text : 00007FF7F661D770                         var_38 = qword ptr - 38h
//   .text : 00007FF7F661D770                         var_30 = qword ptr - 30h
//   .text : 00007FF7F661D770                         var_28 = qword ptr - 28h
//   .text : 00007FF7F661D770                         var_18 = xmmword ptr - 18h
//   .text : 00007FF7F661D770                         arg_0 = byte ptr  8
//   .text : 00007FF7F661D770                         arg_8 = dword ptr  10h
//   .text : 00007FF7F661D770                         arg_10 = qword ptr  18h
//   .text : 00007FF7F661D770
//   .text : 00007FF7F661D770 48 83 EC 58                             sub     rsp, 58h
//   .text : 00007FF7F661D774 0F B6 41 1A                             movzx   eax, byte ptr[rcx + 1Ah]
//   .text : 00007FF7F661D778 0F 29 74 24 40                          movaps[rsp + 58h + var_18], xmm6
//   .text : 00007FF7F661D77D 0F 57 F6                                xorps   xmm6, xmm6
//   .text : 00007FF7F661D780 83 F8 1A                                cmp     eax, 1Ah
//   .text : 00007FF7F661D783 74 1B                                   jz      short loc_7FF7F661D7A0
//   .text : 00007FF7F661D785 83 F8 1F                                cmp     eax, 1Fh
//   .text : 00007FF7F661D788 0F 85 A1 00 00 00                       jnz     loc_7FF7F661D82F
//   .text : 00007FF7F661D78E F3 0F 10 05 B2 37 A4 01                 movss   xmm0, cs : dword_7FF7F8060F48
//   .text : 00007FF7F661D796 0F 28 74 24 40                          movaps  xmm6, [rsp + 58h + var_18]
//   .text : 00007FF7F661D79B 48 83 C4 58                             add     rsp, 58h
//   .text : 00007FF7F661D79F C3                                      retn
//   .text : 00007FF7F661D7A0; -------------------------------------------------------------------------- -
//   .text:00007FF7F661D7A0
//   .text : 00007FF7F661D7A0                         loc_7FF7F661D7A0 : ; CODE XREF : GetWarmth + 13↑j
//   .text : 00007FF7F661D7A0 48 8D 05 E9 0B A4 01                    lea     rax, off_7FF7F805E390
//   .text:00007FF7F661D7A7 C7 44 24 68 00 00 00 00                 mov[rsp + 58h + arg_8], 0
//   .text : 00007FF7F661D7AF 48 89 44 24 70                          mov[rsp + 58h + arg_10], rax
//   .text : 00007FF7F661D7B4 48 8D 54 24 20                          lea     rdx, [rsp + 58h + var_38]
//   .text : 00007FF7F661D7B9 48 8D 44 24 60                          lea     rax, [rsp + 58h + arg_0]
//   .text : 00007FF7F661D7BE 48 81 C1 D8 01 00 00                    add     rcx, 1D8h
//   .text : 00007FF7F661D7C5 48 89 44 24 20                          mov[rsp + 58h + var_38], rax
//   .text : 00007FF7F661D7CA 48 8D 44 24 68                          lea     rax, [rsp + 58h + arg_8]
//   .text : 00007FF7F661D7CF 48 89 44 24 28                          mov[rsp + 58h + var_30], rax
//   .text : 00007FF7F661D7D4 48 8D 44 24 70                          lea     rax, [rsp + 58h + arg_10]
//   .text : 00007FF7F661D7D9 48 89 44 24 30                          mov[rsp + 58h + var_28], rax
//   .text : 00007FF7F661D7DE E8 8D 02 00 00                          call    sub_7FF7F661DA70
//   .text : 00007FF7F661D7E3 8B 54 24 68                             mov     edx, [rsp + 58h + arg_8]
//   .text : 00007FF7F661D7E7 85 D2                                   test    edx, edx
//   .text : 00007FF7F661D7E9 74 44                                   jz      short loc_7FF7F661D82F
//   .text : 00007FF7F661D7EB 48 8B 4C 24 70                          mov     rcx, [rsp + 58h + arg_10]
//   .text : 00007FF7F661D7F0 F6 C2 01                                test    dl, 1
//   .text : 00007FF7F661D7F3 74 08                                   jz      short loc_7FF7F661D7FD
//   .text:00007FF7F661D7F5 48 8B 01                                mov     rax, [rcx]
//   .text : 00007FF7F661D7F8 F3 0F 10 70 08                          movss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D7FD
//   .text : 00007FF7F661D7FD                         loc_7FF7F661D7FD : ; CODE XREF : GetWarmth + 83↑j
//   .text : 00007FF7F661D7FD F6 C2 02                                test    dl, 2
//   .text : 00007FF7F661D800 74 09                                   jz      short loc_7FF7F661D80B
//   .text:00007FF7F661D802 48 8B 41 08                             mov     rax, [rcx + 8]
//   .text:00007FF7F661D806 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D80B
//   .text : 00007FF7F661D80B                         loc_7FF7F661D80B : ; CODE XREF : GetWarmth + 90↑j
//   .text : 00007FF7F661D80B F6 C2 04                                test    dl, 4
//   .text : 00007FF7F661D80E 74 09                                   jz      short loc_7FF7F661D819
//   .text:00007FF7F661D810 48 8B 41 10                             mov     rax, [rcx + 10h]
//   .text : 00007FF7F661D814 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D819
//   .text : 00007FF7F661D819                         loc_7FF7F661D819 : ; CODE XREF : GetWarmth + 9E↑j
//   .text : 00007FF7F661D819 F6 C2 08                                test    dl, 8
//   .text:00007FF7F661D81C 74 09                                   jz      short loc_7FF7F661D827
//   .text:00007FF7F661D81E 48 8B 41 18                             mov     rax, [rcx + 18h]
//   .text : 00007FF7F661D822 F3 0F 58 70 08                          addss   xmm6, dword ptr[rax + 8]
//   .text:00007FF7F661D827
//   .text : 00007FF7F661D827                         loc_7FF7F661D827 : ; CODE XREF : GetWarmth + AC↑j
//   .text : 00007FF7F661D827 F3 0F 59 35 01 37 A4 01                 mulss   xmm6, cs : dword_7FF7F8060F30
//   .text : 00007FF7F661D82F
//   .text : 00007FF7F661D82F                         loc_7FF7F661D82F : ; CODE XREF : GetWarmth + 18↑j
//   .text : 00007FF7F661D82F; GetWarmth + 79↑j
//   .text:00007FF7F661D82F 0F 28 C6                                movaps  xmm0, xmm6
//   .text : 00007FF7F661D832 0F 28 74 24 40                          movaps  xmm6, [rsp + 58h + var_18]
//   .text : 00007FF7F661D837 48 83 C4 58                             add     rsp, 58h
//   .text : 00007FF7F661D83B C3                                      retn
//   .text : 00007FF7F661D83B                         GetWarmth       endp
//   .text : 00007FF7F661D83B
//   .text : 00007FF7F661D83B; -------------------------------------------------------------------------- -

//Unpacked
//HxD Raw 03 00 4C 89 B7 D0 03 03 00 44 89 B7 D8 03 03 00 4C 89 B7 E8 03 03 00 4C 89 B7 F0 03 03 00 83 CB
//CFF Explorer .text 030300008891FC0303008891FE030300488DB9A0020300488BCFE821A191FF40
#ifndef IS_VR
	RelocAddr<_IsSurvivalMode> IsSurvivalMode(0x008DAAB0);
#endif
//.text:00000001408DAAB0                                                 IsSurvivalMode  proc near; CODE XREF : sub_1401A1730:loc_1401A17ACp
//.text:00000001408DAAB0; sub_1401A1730 + 9Ep ...
//.text:00000001408DAAB0 48 83 EC 28                                                     sub     rsp, 28h
//.text:00000001408DAAB4 E8 57 C7 81 FF                                                  call    sub_1400F7210
//.text:00000001408DAAB9 80 B8 C2 0C 00 00 00                                            cmp     byte ptr[rax + 0CC2h], 0
//.text:00000001408DAAC0 74 2B                                                           jz      short loc_1408DAAED
//.text:00000001408DAAC2 48 8B 88 30 0A 00 00                                            mov     rcx, [rax + 0A30h]
//.text:00000001408DAAC9 48 85 C9                                                        test    rcx, rcx
//.text:00000001408DAACC 74 1F                                                           jz      short loc_1408DAAED
//.text:00000001408DAACE F3 0F 10 05 12 88 C4 00                                         movss   xmm0, cs:dword_1415232E8
//.text : 00000001408DAAD6 0F 2E 41 34                                                     ucomiss xmm0, dword ptr[rcx + 34h]
//.text:00000001408DAADA 75 0A                                                           jnz     short loc_1408DAAE6
//.text:00000001408DAADC B8 01 00 00 00                                                  mov     eax, 1
//.text:00000001408DAAE1 48 83 C4 28                                                     add     rsp, 28h
//.text:00000001408DAAE5 C3                                                              retn
//.text:00000001408DAAE6; -------------------------------------------------------------------------- -


RelocAddr<GET_MAGIC_ITEM_DESCRIPTION> GetMagicItemDescription2(0x008C0940);

//.text:00000001408C0940; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//.text:00000001408C0940
//.text:00000001408C0940; Attributes: library function static bp - based frame fpd = 1000h
//.text : 00000001408C0940
//.text:00000001408C0940                         GetMagicDescription proc near; CODE XREF : sub_1408BEBD0 + C55↑p
//.text : 00000001408C0940; sub_1408BEBD0 + CC7↑p ...
//.text:00000001408C0940
//.text:00000001408C0940                         var_10E0 = qword ptr - 10E0h
//.text:00000001408C0940                         var_10D8 = qword ptr - 10D8h
//.text:00000001408C0940                         var_10D0 = qword ptr - 10D0h
//.text:00000001408C0940                         var_10C0 = qword ptr - 10C0h
//.text:00000001408C0940                         var_10B8 = qword ptr - 10B8h
//.text:00000001408C0940                         var_10B0 = qword ptr - 10B0h
//.text:00000001408C0940                         var_10A8 = qword ptr - 10A8h
//.text:00000001408C0940                         var_10A0 = qword ptr - 10A0h
//.text:00000001408C0940                         var_1098 = qword ptr - 1098h
//.text:00000001408C0940                         var_1090 = byte ptr - 1090h
//.text:00000001408C0940                         var_1088 = qword ptr - 1088h
//.text:00000001408C0940                         DstBuf = byte ptr - 1080h
//.text:00000001408C0940                         Dst = byte ptr - 880h
//.text:00000001408C0940                         var_80 = xmmword ptr - 80h
//.text:00000001408C0940                         var_70 = xmmword ptr - 70h
//.text:00000001408C0940                         var_60 = xmmword ptr - 60h
//.text:00000001408C0940                         var_50 = xmmword ptr - 50h
//.text:00000001408C0940                         var_40 = xmmword ptr - 40h
//.text:00000001408C0940                         var_30 = xmmword ptr - 30h
//.text:00000001408C0940                         var_20 = byte ptr - 20h
//.text:00000001408C0940                         arg_0 = qword ptr  10h
//.text:00000001408C0940                         arg_8 = dword ptr  18h
//.text:00000001408C0940                         arg_10 = dword ptr  20h
//.text:00000001408C0940                         arg_18 = qword ptr  28h
//.text:00000001408C0940
//.text:00000001408C0940; FUNCTION CHUNK AT.text:00000001408C11E0 SIZE 0000000B BYTES
//.text:00000001408C0940; FUNCTION CHUNK AT.text:000000014147679B SIZE 0000000C BYTES
//.text:00000001408C0940
//.text:00000001408C0940; __unwind{ // __CxxFrameHandler3
//	.text:00000001408C0940 40 55                                   push    rbp
//	.text:00000001408C0942 57                                      push    rdi
//	.text:00000001408C0943 41 54                                   push    r12
//	.text:00000001408C0945 41 56                                   push    r14
//	.text:00000001408C0947 41 57                                   push    r15
//	.text:00000001408C0949 48 8D AC 24 20 F0 FF FF                 lea     rbp,[rsp - 0FE0h]
//	.text:00000001408C0951 B8 E0 10 00 00                          mov     eax, 10E0h
//	.text:00000001408C0956 E8 35 A2 AC 00                          call    _alloca_probe
//	.text:00000001408C095B 48 2B E0                                sub     rsp, rax
//	.text:00000001408C095E 48 C7 44 24 78 FE FF FF + mov[rsp + 1100h + var_1088], 0FFFFFFFFFFFFFFFEh
//	.text:00000001408C0967 48 89 9C 24 10 11 00 00                 mov[rsp + 1100h + arg_0], rbx
//	.text:00000001408C096F 48 89 B4 24 28 11 00 00                 mov[rsp + 1100h + arg_18], rsi
//	.text:00000001408C0977 0F 29 B4 24 D0 10 00 00                 movaps[rsp + 1100h + var_30], xmm6
//	.text:00000001408C097F 0F 29 BC 24 C0 10 00 00                 movaps[rsp + 1100h + var_40], xmm7
//	.text:00000001408C0987 44 0F 29 84 24 B0 10 00 + movaps[rsp + 1100h + var_50], xmm8
//	.text:00000001408C0990 44 0F 29 8C 24 A0 10 00 + movaps[rsp + 1100h + var_60], xmm9
//	.text:00000001408C0999 44 0F 29 94 24 90 10 00 + movaps[rsp + 1100h + var_70], xmm10
//	.text:00000001408C09A2 44 0F 29 9C 24 80 10 00 + movaps[rsp + 1100h + var_80], xmm11
//	.text:00000001408C09AB 4D 8B F8                                mov     r15, r8
//	.text:00000001408C09AE 48 8B F2                                mov     rsi, rdx
//	.text:00000001408C09B1 40 32 FF                                xor     dil, dil
//	.text:00000001408C09B4 45 33 F6                                xor     r14d, r14d
//	.text:00000001408C09B7 48 85 D2                                test    rdx, rdx
//	.text:00000001408C09BA 74 19                                   jz      short loc_1408C09D5
//	.text:00000001408C09BC 44 39 72 68                             cmp[rdx + 68h], r14d
//	.text:00000001408C09C0 76 09                                   jbe     short loc_1408C09CB
//	.text:00000001408C09C2 48 8B 42 58                             mov     rax,[rdx + 58h]
//	.text:00000001408C09C6 48 8B 18                                mov     rbx,[rax]
//	.text:00000001408C09C9 EB 02                                   jmp     short loc_1408C09CD
//	.text:00000001408C09CB; -------------------------------------------------------------------------- -
//	.text:00000001408C09CB
//	.text:00000001408C09CB                         loc_1408C09CB : ; CODE XREF : GetMagicDescription + 80↑j
//	.text : 00000001408C09CB 33 DB                                   xor     ebx, ebx
//	.text:00000001408C09CD
//	.text:00000001408C09CD                         loc_1408C09CD : ; CODE XREF : GetMagicDescription + 89↑j
//	.text : 00000001408C09CD 41 BE 01 00 00 00                       mov     r14d, 1
//	.text:00000001408C09D3 EB 02                                   jmp     short loc_1408C09D7
//	.text:00000001408C09D5; -------------------------------------------------------------------------- -
//	.text:00000001408C09D5
//	.text:00000001408C09D5                         loc_1408C09D5 : ; CODE XREF : GetMagicDescription + 7A↑j
//	.text : 00000001408C09D5 33 DB                                   xor     ebx, ebx
//	.text:00000001408C09D7
//	.text:00000001408C09D7                         loc_1408C09D7 : ; CODE XREF : GetMagicDescription + 93↑j
//	.text : 00000001408C09D7 33 D2                                   xor     edx, edx; Val
//	.text:00000001408C09D9 41 B8 00 08 00 00                       mov     r8d, 800h; Size
//	.text:00000001408C09DF 48 8D 8D 80 07 00 00                    lea     rcx,[rbp + 1000h + Dst]; Dst
//	.text:00000001408C09E6 E8 ED B0 AC 00                          call    memset
//	.text:00000001408C09EB 45 33 C0                                xor     r8d, r8d
//	.text:00000001408C09EE 48 8D 15 FB 5B CD 00                    lea     rdx, Str1
//	.text:00000001408C09F5 49 8B CF                                mov     rcx, r15
//	.text:00000001408C09F8 E8 43 9A 84 FF                          call    sub_14010A440
//	.text:00000001408C09FD 48 85 F6                                test    rsi, rsi
//	.text:00000001408C0A00 74 48                                   jz      short loc_1408C0A4A
//	.text:00000001408C0A02 33 C0                                   xor     eax, eax
//	.text:00000001408C0A04 48 89 44 24 48                          mov[rsp + 1100h + var_10B8], rax
//	.text:00000001408C0A09 48 8D 05 E0 83 E7 00                    lea     rax, ? ? _7GetMagicItemDescriptionFunctor@?A0xf83b70e7@@6B@; const `anonymous namespace'::GetMagicItemDescriptionFunctor::`vftable'
//	.text:00000001408C0A10 48 89 44 24 40                          mov[rsp + 1100h + var_10C0], rax
//	.text:00000001408C0A15 4C 89 7C 24 50                          mov[rsp + 1100h + var_10B0], r15
//	.text:00000001408C0A1A 48 8B 05 C7 2C 75 02                    mov     rax, cs:qword_1430136E8
//	.text : 00000001408C0A21 48 89 44 24 58                          mov[rsp + 1100h + var_10A8], rax
//	.text:00000001408C0A26 48 8B 05 C3 2C 75 02                    mov     rax, cs:qword_1430136F0
//	.text : 00000001408C0A2D 48 89 44 24 60                          mov[rsp + 1100h + var_10A0], rax
//	.text:00000001408C0A32 48 89 74 24 68                          mov[rsp + 1100h + var_1098], rsi
//	.text:00000001408C0A37 C6 44 24 70 00                          mov[rsp + 1100h + var_1090], 0
//	.text:00000001408C0A3C
//	.text:00000001408C0A3C                         loc_1408C0A3C : ; DATA XREF : .rdata : 0000000141C82B18↓o
//	.text : 00000001408C0A3C;   try {
//	.text:00000001408C0A3C 48 8D 54 24 40                          lea     rdx,[rsp + 1100h + var_10C0]
//		.text:00000001408C0A41 48 8B CE                                mov     rcx, rsi
//		.text:00000001408C0A44 E8 97 1B 85 FF                          call    sub_1401125E0
//		.text:00000001408C0A49 90                                      nop
//		.text:00000001408C0A49;
//} // starts at 1408C0A3C
//.text:00000001408C0A4A
//.text:00000001408C0A4A                         loc_1408C0A4A : ; CODE XREF : GetMagicDescription + C0↑j
//.text : 00000001408C0A4A; DATA XREF : .rdata : 0000000141C82B20↓o
//.text : 00000001408C0A4A 41 0F B7 47 08                          movzx   eax, word ptr[r15 + 8]
//.text:00000001408C0A4F B9 FF FF 00 00                          mov     ecx, 0FFFFh
//.text:00000001408C0A54 66 3B C1                                cmp     ax, cx
//.text:00000001408C0A57 75 12                                   jnz     short loc_1408C0A6B
//.text:00000001408C0A59 49 8B 0F                                mov     rcx,[r15]
//.text:00000001408C0A5C 48 83 C8 FF or rax, 0FFFFFFFFFFFFFFFFh
//.text:00000001408C0A60
//.text:00000001408C0A60                         loc_1408C0A60 : ; CODE XREF : GetMagicDescription + 127↓j
//.text : 00000001408C0A60 48 FF C0                                inc     rax
//.text:00000001408C0A63 80 3C 01 00                             cmp     byte ptr[rcx + rax], 0
//.text:00000001408C0A67 75 F7                                   jnz     short loc_1408C0A60
//.text:00000001408C0A69 EB 03                                   jmp     short loc_1408C0A6E
//.text:00000001408C0A6B; -------------------------------------------------------------------------- -
//.text:00000001408C0A6B
//.text:00000001408C0A6B                         loc_1408C0A6B : ; CODE XREF : GetMagicDescription + 117↑j
//.text : 00000001408C0A6B 0F B7 C0                                movzx   eax, ax
//.text:00000001408C0A6E
//.text:00000001408C0A6E                         loc_1408C0A6E : ; CODE XREF : GetMagicDescription + 129↑j
//.text : 00000001408C0A6E 85 C0                                   test    eax, eax
//.text:00000001408C0A70 0F 85 A5 02 00 00                       jnz     loc_1408C0D1B
//.text:00000001408C0A76 48 85 F6                                test    rsi, rsi
//.text:00000001408C0A79 0F 84 8A 02 00 00                       jz      loc_1408C0D09
//.text:00000001408C0A7F 4C 8D 25 7E 83 E7 00                    lea     r12, asc_141738E04; "+"
//.text:00000001408C0A86 F3 44 0F 10 0D D9 1B DF + movss   xmm9, cs:dword_1416B2668
//.text : 00000001408C0A8F F3 44 0F 10 15 0C 87 D3 + movss   xmm10, cs:dword_1415F91A4
//.text : 00000001408C0A98 0F 57 FF                                xorps   xmm7, xmm7
//.text:00000001408C0A9B F3 0F 10 35 85 9B CD 00                 movss   xmm6, cs:dword_14159A628
//.text : 00000001408C0AA3 F3 44 0F 10 05 D4 FE CE + movss   xmm8, cs:dword_1415B0980
//.text : 00000001408C0AAC F3 44 0F 10 1D F7 32 D3 + movss   xmm11, cs:dword_1415F3DAC
//.text : 00000001408C0AB5
//.text:00000001408C0AB5                         loc_1408C0AB5 : ; CODE XREF : GetMagicDescription + 3C4↓j
//.text : 00000001408C0AB5 48 85 DB                                test    rbx, rbx
//.text:00000001408C0AB8 0F 84 4B 02 00 00                       jz      loc_1408C0D09
//.text:00000001408C0ABE 48 8B 43 10                             mov     rax,[rbx + 10h]
//.text:00000001408C0AC2 8B 48 68                                mov     ecx,[rax + 68h]
//.text:00000001408C0AC5 C1 E9 0F                                shr     ecx, 0Fh
//.text:00000001408C0AC8 F6 C1 01                                test    cl, 1
//.text:00000001408C0ACB 0F 85 1B 02 00 00                       jnz     loc_1408C0CEC
//.text:00000001408C0AD1 40 84 FF                                test    dil, dil
//.text:00000001408C0AD4 74 19                                   jz      short loc_1408C0AEF
//.text:00000001408C0AD6 4C 8D 05 23 83 E7 00                    lea     r8, asc_141738E00; ". "
//.text:00000001408C0ADD BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0AE2 48 8D 8D 80 07 00 00                    lea     rcx,[rbp + 1000h + Dst]; Dst
//.text:00000001408C0AE9 FF 15 69 F5 CB 00                       call    cs : strcat_s
//.text : 00000001408C0AEF
//.text:00000001408C0AEF                         loc_1408C0AEF : ; CODE XREF : GetMagicDescription + 194↑j
//.text : 00000001408C0AEF 48 8B CB                                mov     rcx, rbx
//.text:00000001408C0AF2 E8 E9 7F 84 FF                          call    sub_140108AE0
//.text:00000001408C0AF7 66 0F 6E C0                             movd    xmm0, eax
//.text:00000001408C0AFB 0F 5B C0                                cvtdq2ps xmm0, xmm0
//.text:00000001408C0AFE F3 0F 11 85 18 10 00 00                 movss[rbp + 1000h + arg_8], xmm0
//.text:00000001408C0B06 48 8B CB                                mov     rcx, rbx
//.text:00000001408C0B09 E8 12 7F 84 FF                          call    sub_140108A20
//.text:00000001408C0B0E F3 0F 11 85 20 10 00 00                 movss[rbp + 1000h + arg_10], xmm0
//.text:00000001408C0B16 48 8D 85 18 10 00 00                    lea     rax,[rbp + 1000h + arg_8]
//.text:00000001408C0B1D 48 89 44 24 20                          mov[rsp + 1100h + var_10E0], rax
//.text:00000001408C0B22 45 33 C9                                xor     r9d, r9d
//.text:00000001408C0B25 4C 8B C6                                mov     r8, rsi
//.text:00000001408C0B28 48 8B 15 C1 AE 72 02                    mov     rdx, cs:SizeInBytes
//.text : 00000001408C0B2F 41 8D 49 1E                             lea     ecx,[r9 + 1Eh]
//.text:00000001408C0B33 E8 68 DA A7 FF                          call    sub_14033E5A0
//.text:00000001408C0B38 48 8D 85 20 10 00 00                    lea     rax,[rbp + 1000h + arg_10]
//.text:00000001408C0B3F 48 89 44 24 20                          mov[rsp + 1100h + var_10E0], rax
//.text:00000001408C0B44 45 33 C9                                xor     r9d, r9d
//.text:00000001408C0B47 4C 8B C6                                mov     r8, rsi
//.text:00000001408C0B4A 48 8B 15 9F AE 72 02                    mov     rdx, cs:SizeInBytes
//.text : 00000001408C0B51 41 8D 49 1D                             lea     ecx,[r9 + 1Dh]
//.text:00000001408C0B55 E8 46 DA A7 FF                          call    sub_14033E5A0
//.text:00000001408C0B5A F3 48 0F 2C BD 18 10 00 + cvttss2si rdi,[rbp + 1000h + arg_8]
//.text:00000001408C0B63 F3 48 0F 2C 8D 20 10 00 + cvttss2si rcx,[rbp + 1000h + arg_10]
//.text:00000001408C0B6C 85 C9                                   test    ecx, ecx
//.text:00000001408C0B6E 74 52                                   jz      short loc_1408C0BC2
//.text:00000001408C0B70 48 8D 15 79 5A CD 00                    lea     rdx, Str1
//.text:00000001408C0B77 49 0F 45 D4                             cmovnz  rdx, r12
//.text:00000001408C0B7B 48 8B 05 6E 2B 75 02                    mov     rax, cs:qword_1430136F0
//.text : 00000001408C0B82 48 89 44 24 30                          mov[rsp + 1100h + var_10D0], rax
//.text:00000001408C0B87 89 4C 24 28                             mov     dword ptr[rsp + 1100h + var_10D8], ecx
//.text:00000001408C0B8B 48 89 54 24 20                          mov[rsp + 1100h + var_10E0], rdx
//.text:00000001408C0B90 4C 8B 0D 51 2B 75 02                    mov     r9, cs:qword_1430136E8
//.text : 00000001408C0B97 4C 8D 05 6A 82 E7 00                    lea     r8, aSSUS; "%s%s%u%s "
//.text:00000001408C0B9E BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0BA3 48 8D 4D 80                             lea     rcx,[rbp + 1000h + DstBuf]; DstBuf
//.text:00000001408C0BA7 E8 14 22 89 FF                          call    sprintf_s
//.text:00000001408C0BAC 4C 8D 45 80                             lea     r8,[rbp + 1000h + DstBuf]; Src
//.text:00000001408C0BB0 BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0BB5 48 8D 8D 80 07 00 00                    lea     rcx,[rbp + 1000h + Dst]; Dst
//.text:00000001408C0BBC FF 15 96 F4 CB 00                       call    cs : strcat_s
//.text : 00000001408C0BC2
//.text:00000001408C0BC2                         loc_1408C0BC2 : ; CODE XREF : GetMagicDescription + 22E↑j
//.text : 00000001408C0BC2 48 8B CB                                mov     rcx, rbx
//.text:00000001408C0BC5 E8 C6 7F 84 FF                          call    sub_140108B90
//.text:00000001408C0BCA 48 8B C8                                mov     rcx, rax
//.text:00000001408C0BCD E8 3E A4 90 FF                          call    sub_1401CB010
//.text:00000001408C0BD2 4C 8B C0                                mov     r8, rax; Src
//.text:00000001408C0BD5 BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0BDA 48 8D 8D 80 07 00 00                    lea     rcx,[rbp + 1000h + Dst]; Dst
//.text:00000001408C0BE1 FF 15 71 F4 CB 00                       call    cs : strcat_s
//.text : 00000001408C0BE7 85 FF                                   test    edi, edi
//.text:00000001408C0BE9 0F 84 FA 00 00 00                       jz      loc_1408C0CE9
//.text:00000001408C0BEF 8B C7                                   mov     eax, edi
//.text:00000001408C0BF1 0F 57 C9                                xorps   xmm1, xmm1
//.text:00000001408C0BF4 F3 48 0F 2A C8                          cvtsi2ss xmm1, rax
//.text:00000001408C0BF9 41 0F 2F C9                             comiss  xmm1, xmm9
//.text:00000001408C0BFD 72 35                                   jb      short loc_1408C0C34
//.text:00000001408C0BFF F3 41 0F 59 CA                          mulss   xmm1, xmm10
//.text:00000001408C0C04 F3 0F 2C C1                             cvttss2si eax, xmm1
//.text:00000001408C0C08 66 0F 6E D0                             movd    xmm2, eax
//.text:00000001408C0C0C 0F 5B D2                                cvtdq2ps xmm2, xmm2
//.text:00000001408C0C0F 0F 28 C1                                movaps  xmm0, xmm1
//.text:00000001408C0C12 F3 0F 5C C2                             subss   xmm0, xmm2
//.text:00000001408C0C16 0F 2F C7                                comiss  xmm0, xmm7
//.text:00000001408C0C19 73 04                                   jnb     short loc_1408C0C1F
//.text:00000001408C0C1B F3 0F 5C D6                             subss   xmm2, xmm6
//.text:00000001408C0C1F
//.text:00000001408C0C1F                         loc_1408C0C1F : ; CODE XREF : GetMagicDescription + 2D9↑j
//.text : 00000001408C0C1F 0F 2E D6                                ucomiss xmm2, xmm6
//.text:00000001408C0C22 48 8B 05 67 4F 5E 01                    mov     rax, cs:off_141EA5B90
//.text : 00000001408C0C29 74 72                                   jz      short loc_1408C0C9D
//.text:00000001408C0C2B 48 8B 05 16 4F 5E 01                    mov     rax, cs:off_141EA5B48
//.text : 00000001408C0C32 EB 69                                   jmp     short loc_1408C0C9D
//.text:00000001408C0C34; -------------------------------------------------------------------------- -
//.text:00000001408C0C34
//.text:00000001408C0C34                         loc_1408C0C34 : ; CODE XREF : GetMagicDescription + 2BD↑j
//.text : 00000001408C0C34 41 0F 2F C8                             comiss  xmm1, xmm8
//.text:00000001408C0C38 72 35                                   jb      short loc_1408C0C6F
//.text:00000001408C0C3A F3 41 0F 59 CB                          mulss   xmm1, xmm11
//.text:00000001408C0C3F F3 0F 2C C1                             cvttss2si eax, xmm1
//.text:00000001408C0C43 66 0F 6E D0                             movd    xmm2, eax
//.text:00000001408C0C47 0F 5B D2                                cvtdq2ps xmm2, xmm2
//.text:00000001408C0C4A 0F 28 C1                                movaps  xmm0, xmm1
//.text:00000001408C0C4D F3 0F 5C C2                             subss   xmm0, xmm2
//.text:00000001408C0C51 0F 2F C7                                comiss  xmm0, xmm7
//.text:00000001408C0C54 73 04                                   jnb     short loc_1408C0C5A
//.text:00000001408C0C56 F3 0F 5C D6                             subss   xmm2, xmm6
//.text:00000001408C0C5A
//.text:00000001408C0C5A                         loc_1408C0C5A : ; CODE XREF : GetMagicDescription + 314↑j
//.text : 00000001408C0C5A 0F 2E D6                                ucomiss xmm2, xmm6
//.text:00000001408C0C5D 48 8B 05 14 4F 5E 01                    mov     rax, cs:off_141EA5B78
//.text : 00000001408C0C64 74 37                                   jz      short loc_1408C0C9D
//.text:00000001408C0C66 48 8B 05 C3 4E 5E 01                    mov     rax, cs:off_141EA5B30
//.text : 00000001408C0C6D EB 2E                                   jmp     short loc_1408C0C9D
//.text:00000001408C0C6F; -------------------------------------------------------------------------- -
//.text:00000001408C0C6F
//.text:00000001408C0C6F                         loc_1408C0C6F : ; CODE XREF : GetMagicDescription + 2F8↑j
//.text : 00000001408C0C6F F3 0F 2C C1                             cvttss2si eax, xmm1
//.text:00000001408C0C73 66 0F 6E D0                             movd    xmm2, eax
//.text:00000001408C0C77 0F 5B D2                                cvtdq2ps xmm2, xmm2
//.text:00000001408C0C7A 0F 28 C1                                movaps  xmm0, xmm1
//.text:00000001408C0C7D F3 0F 5C C2                             subss   xmm0, xmm2
//.text:00000001408C0C81 0F 2F C7                                comiss  xmm0, xmm7
//.text:00000001408C0C84 73 04                                   jnb     short loc_1408C0C8A
//.text:00000001408C0C86 F3 0F 5C D6                             subss   xmm2, xmm6
//.text:00000001408C0C8A
//.text:00000001408C0C8A                         loc_1408C0C8A : ; CODE XREF : GetMagicDescription + 344↑j
//.text : 00000001408C0C8A 0F 2E D6                                ucomiss xmm2, xmm6
//.text:00000001408C0C8D 48 8B 05 CC 4E 5E 01                    mov     rax, cs:off_141EA5B60
//.text : 00000001408C0C94 74 07                                   jz      short loc_1408C0C9D
//.text:00000001408C0C96 48 8B 05 63 33 5E 01                    mov     rax, cs:off_141EA4000
//.text : 00000001408C0C9D
//.text:00000001408C0C9D                         loc_1408C0C9D : ; CODE XREF : GetMagicDescription + 2E9↑j
//.text : 00000001408C0C9D; GetMagicDescription + 2F2↑j ...
//.text:00000001408C0C9D 48 89 44 24 30                          mov[rsp + 1100h + var_10D0], rax
//.text:00000001408C0CA2 48 8B 05 47 2A 75 02                    mov     rax, cs:qword_1430136F0
//.text : 00000001408C0CA9 48 89 44 24 28                          mov[rsp + 1100h + var_10D8], rax
//.text:00000001408C0CAE 0F 5A C1                                cvtps2pd xmm0, xmm1
//.text:00000001408C0CB1 F2 0F 11 44 24 20                       movsd[rsp + 1100h + var_10E0], xmm0
//.text:00000001408C0CB7 4C 8B 0D 2A 2A 75 02                    mov     r9, cs:qword_1430136E8
//.text : 00000001408C0CBE 4C 8D 05 53 81 E7 00                    lea     r8, aS0fSS; " %s%.0f%s %s"
//.text:00000001408C0CC5 BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0CCA 48 8D 4D 80                             lea     rcx,[rbp + 1000h + DstBuf]; DstBuf
//.text:00000001408C0CCE E8 ED 20 89 FF                          call    sprintf_s
//.text:00000001408C0CD3 4C 8D 45 80                             lea     r8,[rbp + 1000h + DstBuf]; Src
//.text:00000001408C0CD7 BA 00 08 00 00                          mov     edx, 800h; SizeInBytes
//.text:00000001408C0CDC 48 8D 8D 80 07 00 00                    lea     rcx,[rbp + 1000h + Dst]; Dst
//.text:00000001408C0CE3 FF 15 6F F3 CB 00                       call    cs : strcat_s
//.text : 00000001408C0CE9
//.text:00000001408C0CE9                         loc_1408C0CE9 : ; CODE XREF : GetMagicDescription + 2A9↑j
//.text : 00000001408C0CE9 40 B7 01                                mov     dil, 1
//.text:00000001408C0CEC
//.text:00000001408C0CEC                         loc_1408C0CEC : ; CODE XREF : GetMagicDescription + 18B↑j
//.text : 00000001408C0CEC 44 3B 76 68                             cmp     r14d,[rsi + 68h]
//.text:00000001408C0CF0 73 0D                                   jnb     short loc_1408C0CFF
//.text:00000001408C0CF2 41 8B CE                                mov     ecx, r14d
//.text:00000001408C0CF5 48 8B 46 58                             mov     rax,[rsi + 58h]
//.text:00000001408C0CF9 48 8B 1C C8                             mov     rbx,[rax + rcx * 8]
//.text:00000001408C0CFD EB 02                                   jmp     short loc_1408C0D01
//.text:00000001408C0CFF; -------------------------------------------------------------------------- -
//.text:00000001408C0CFF
//.text:00000001408C0CFF                         loc_1408C0CFF : ; CODE XREF : GetMagicDescription + 3B0↑j
//.text : 00000001408C0CFF 33 DB                                   xor     ebx, ebx
//.text:00000001408C0D01
//.text:00000001408C0D01                         loc_1408C0D01 : ; CODE XREF : GetMagicDescription + 3BD↑j
//.text : 00000001408C0D01 41 FF C6                                inc     r14d
//.text:00000001408C0D04 E9 AC FD FF FF                          jmp     loc_1408C0AB5
//.text:00000001408C0D09; -------------------------------------------------------------------------- -
//.text:00000001408C0D09
//.text:00000001408C0D09                         loc_1408C0D09 : ; CODE XREF : GetMagicDescription + 139↑j
//.text : 00000001408C0D09; GetMagicDescription + 178↑j
//.text:00000001408C0D09 45 33 C0                                xor     r8d, r8d
//.text:00000001408C0D0C 48 8D 95 80 07 00 00                    lea     rdx,[rbp + 1000h + Dst]
//.text:00000001408C0D13 49 8B CF                                mov     rcx, r15
//.text:00000001408C0D16 E8 25 97 84 FF                          call    sub_14010A440
//.text:00000001408C0D1B
//.text:00000001408C0D1B                         loc_1408C0D1B : ; CODE XREF : GetMagicDescription + 130↑j
//.text : 00000001408C0D1B 4C 8D 9C 24 E0 10 00 00                 lea     r11,[rsp + 1100h + var_20]
//.text:00000001408C0D23 49 8B 5B 30                             mov     rbx,[r11 + 30h]
//.text:00000001408C0D27 49 8B 73 48                             mov     rsi,[r11 + 48h]
//.text:00000001408C0D2B 41 0F 28 73 F0                          movaps  xmm6, xmmword ptr[r11 - 10h]
//.text:00000001408C0D30 41 0F 28 7B E0                          movaps  xmm7, xmmword ptr[r11 - 20h]
//.text:00000001408C0D35 45 0F 28 43 D0                          movaps  xmm8, xmmword ptr[r11 - 30h]
//.text:00000001408C0D3A 45 0F 28 4B C0                          movaps  xmm9, xmmword ptr[r11 - 40h]
//.text:00000001408C0D3F 45 0F 28 53 B0                          movaps  xmm10, xmmword ptr[r11 - 50h]
//.text:00000001408C0D44 45 0F 28 5B A0                          movaps  xmm11, xmmword ptr[r11 - 60h]
//.text:00000001408C0D49 49 8B E3                                mov     rsp, r11
//.text:00000001408C0D4C 41 5F                                   pop     r15
//.text:00000001408C0D4E 41 5E                                   pop     r14
//.text:00000001408C0D50 41 5C                                   pop     r12
//.text:00000001408C0D52 5F                                      pop     rdi
//.text:00000001408C0D53 5D                                      pop     rbp
//.text:00000001408C0D54 C3                                      retn
//.text:00000001408C0D54; } // starts at 1408C0940
//.text:00000001408C0D54                         GetMagicDescription endp
//.text:00000001408C0D54
//.text:00000001408C0D54; -------------------------------------------------------------------------- -



//Unpacked
//HxD Raw 1C 91 00 00 00 48 8B 0D 2C 7F 6B 02 E8 4F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.16
//HxD Raw 1C 91 00 00 00 48 8B 0D FC 7E 6B 02 E8 4F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.23
//HxD Raw 1C 91 00 00 00 48 8B 0D FC 85 6B 02 E8 9F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.39
//HxD Raw 1C 91 00 00 00 48 8B 0D BC 88 6B 02 E8 3F 15 38 00 84 C0 75 06 83 4B 1C 04 EB 1C 48 8B 4B 10 48 -->1.5.50
//CFF Explorer .text F6C701742740F6C7047513488B0D4E507C02488B01488BD3FF506090EB0EBA38 --> 1.5.16
//CFF Explorer .text F6C701742740F6C7047513488B0D1E507C02488B01488BD3FF506090EB0EBA38 --> 1.5.23
RelocAddr<PROCESS_SURVIVAL_MODE> ProcessSurvivalMode(0x008930F0);
//.text:00000001408930F0; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//.text:00000001408930F0
//.text:00000001408930F0
//.text:00000001408930F0                                                 ProcessSurvivalMode proc near; CODE XREF : sub_140890E70 + 96Bp
//.text:00000001408930F0; sub_140890E70 + D2Fp ...
//.text:00000001408930F0
//.text:00000001408930F0                                                 var_18 = qword ptr - 18h
//.text:00000001408930F0                                                 var_10 = qword ptr - 10h
//.text:00000001408930F0                                                 arg_0 = qword ptr  8
//.text:00000001408930F0                                                 arg_8 = qword ptr  10h
//.text:00000001408930F0                                                 arg_10 = qword ptr  18h
//.text:00000001408930F0
//.text:00000001408930F0 41 56                                                           push    r14
//.text:00000001408930F2 48 83 EC 30                                                     sub     rsp, 30h
//.text:00000001408930F6 48 8B 01                                                        mov     rax, [rcx]
//.text:00000001408930F9 4C 8B F1                                                        mov     r14, rcx
//.text:00000001408930FC 48 85 C0                                                        test    rax, rax
//.text:00000001408930FF 48 8D 0D AA C1 C8 00                                            lea     rcx, Str1
//.text:0000000140893106 BA 5B 00 00 00                                                  mov     edx, 5Bh; Val
//.text:000000014089310B 48 0F 45 C8                                                     cmovnz  rcx, rax; Str
//.text:000000014089310F FF 15 6B 67 C7 00                                               call    cs : __imp_strchr
//.text : 0000000140893115 48 85 C0                                                        test    rax, rax
//.text:0000000140893118 0F 84 E1 01 00 00                                               jz      loc_1408932FF
//.text:000000014089311E 41 0F B7 46 08                                                  movzx   eax, word ptr[r14 + 8]
//.text:0000000140893123 B9 FF FF 00 00                                                  mov     ecx, 0FFFFh
//.text:0000000140893128
//.text:0000000140893128                                                 loc_140893128 : ; DATA XREF : .rdata : 0000000141BD35FCo
//.text:0000000140893128;.rdata:0000000141BD3610o ...
//.text:0000000140893128 48 89 5C 24 40                                                  mov[rsp + 38h + arg_0], rbx
//.text:000000014089312D 48 89 6C 24 48                                                  mov[rsp + 38h + arg_8], rbp
//.text:0000000140893132 48 89 7C 24 28                                                  mov[rsp + 38h + var_10], rdi
//.text:0000000140893137 4C 89 7C 24 20                                                  mov[rsp + 38h + var_18], r15
//.text:000000014089313C 66 3B C1                                                        cmp     ax, cx
//.text:000000014089313F 75 1A                                                           jnz     short loc_14089315B
//.text:0000000140893141 49 8B 0E                                                        mov     rcx, [r14]
//.text:0000000140893144 48 83 C8 FF or rax, 0FFFFFFFFFFFFFFFFh
//.text:0000000140893148 0F 1F 84 00 00 00 00 00                                         nop     dword ptr[rax + rax + 00000000h]
//.text:0000000140893150
//.text:0000000140893150                                                 loc_140893150 : ; CODE XREF : ProcessSurvivalMode + 67j
//.text:0000000140893150 48 FF C0                                                        inc     rax
//.text:0000000140893153 80 3C 01 00                                                     cmp     byte ptr[rcx + rax], 0
//.text:0000000140893157 75 F7                                                           jnz     short loc_140893150
//.text:0000000140893159 EB 03                                                           jmp     short loc_14089315E
//.text:000000014089315B; -------------------------------------------------------------------------- -


// Base Address = 7FF690BE0000
//.text:00007FF691471740; == == == == == == == = S U B R O U T I N E == == == == == == == == == == == == == == == == == == == =
//.text:00007FF691471740
//.text : 00007FF691471740
//.text : 00007FF691471740 sub_7FF691471740 proc near; CODE XREF : sub_7FF69146F4C0 + 96B↑p
//.text : 00007FF691471740; sub_7FF69146F4C0 + D2F↑p ...
//.text:00007FF691471740
//.text : 00007FF691471740 var_18 = qword ptr - 18h
//.text : 00007FF691471740 var_10 = qword ptr - 10h
//.text : 00007FF691471740 arg_0 = qword ptr  8
//.text : 00007FF691471740 arg_8 = qword ptr  10h
//.text : 00007FF691471740 arg_10 = qword ptr  18h
//.text : 00007FF691471740
//.text : 00007FF691471740                 push    r14
//.text : 00007FF691471742                 sub     rsp, 30h
//.text : 00007FF691471746                 mov     rax, [rcx]
//.text : 00007FF691471749                 mov     r14, rcx
//.text : 00007FF69147174C                 test    rax, rax
//.text : 00007FF69147174F                 lea     rcx, Str1
//.text : 00007FF691471756                 mov     edx, 5Bh; Val
//.text:00007FF69147175B                 cmovnz  rcx, rax; Str
//.text:00007FF69147175F                 call    cs : __imp_strchr
//.text : 00007FF691471765                 test    rax, rax
//.text : 00007FF691471768                 jz      loc_7FF69147194F
//.text : 00007FF69147176E                 movzx   eax, word ptr[r14 + 8]
//.text : 00007FF691471773                 mov     ecx, 0FFFFh
//.text : 00007FF691471778
//.text : 00007FF691471778 loc_7FF691471778 : ; DATA XREF : .rdata : 00007FF6927C4F3C↓o
//.text : 00007FF691471778;.rdata:00007FF6927C4F50↓o ...
//.text : 00007FF691471778                 mov[rsp + 38h + arg_0], rbx
//.text : 00007FF69147177D                 mov[rsp + 38h + arg_8], rbp
//.text : 00007FF691471782                 mov[rsp + 38h + var_10], rdi
//.text : 00007FF691471787                 mov[rsp + 38h + var_18], r15
//.text : 00007FF69147178C                 cmp     ax, cx
//.text : 00007FF69147178F                 jnz     short loc_7FF6914717AB
//.text : 00007FF691471791                 mov     rcx, [r14]
//.text : 00007FF691471794 or rax, 0FFFFFFFFFFFFFFFFh
//.text : 00007FF691471798                 nop     dword ptr[rax + rax + 00000000h]
//.text : 00007FF6914717A0
//.text : 00007FF6914717A0 loc_7FF6914717A0 : ; CODE XREF : sub_7FF691471740 + 67↓j
//.text : 00007FF6914717A0                 inc     rax
//.text : 00007FF6914717A3                 cmp     byte ptr[rcx + rax], 0
//.text : 00007FF6914717A7                 jnz     short loc_7FF6914717A0
//.text : 00007FF6914717A9                 jmp     short loc_7FF6914717AE
//.text : 00007FF6914717AB; -------------------------------------------------------------------------- -
//.text:00007FF6914717AB
//.text : 00007FF6914717AB loc_7FF6914717AB : ; CODE XREF : sub_7FF691471740 + 4F↑j
//.text : 00007FF6914717AB                 movzx   eax, ax
//.text : 00007FF6914717AE
//.text : 00007FF6914717AE loc_7FF6914717AE : ; CODE XREF : sub_7FF691471740 + 69↑j
//.text : 00007FF6914717AE                 cmp     cs : dword_7FF692AB6C88, 2
//.text : 00007FF6914717B5                 lea     ebx, [rax + 1]
//.text : 00007FF6914717B8                 jz      short loc_7FF6914717CD
//.text : 00007FF6914717BA                 lea     rdx, dword_7FF692AB6C88
//.text : 00007FF6914717C1                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF6914717C8                 call    sub_7FF6917E0D30
//.text : 00007FF6914717CD
//.text : 00007FF6914717CD loc_7FF6914717CD : ; CODE XREF : sub_7FF691471740 + 78↑j
//.text : 00007FF6914717CD                 xor     edx, edx
//.text : 00007FF6914717CF                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF6914717D6                 call    sub_7FF6917DFE60
//.text : 00007FF6914717DB                 mov     rcx, rax
//.text : 00007FF6914717DE                 mov     r8d, 8
//.text : 00007FF6914717E4                 mov     rdx, rbx
//.text : 00007FF6914717E7                 call    sub_7FF6917E1B00
//.text : 00007FF6914717EC                 mov     rcx, [r14]
//.text : 00007FF6914717EF                 lea     r8, Str1
//.text : 00007FF6914717F6                 test    rcx, rcx
//.text : 00007FF6914717F9                 mov     rdx, rbx; SizeInBytes
//.text:00007FF6914717FC                 mov     r15, rax
//.text : 00007FF6914717FF                 cmovnz  r8, rcx; Src
//.text:00007FF691471803                 mov     rcx, rax; Dst
//.text:00007FF691471806                 call    cs : __imp_strcpy_s
//.text : 00007FF69147180C                 xor     r8d, r8d
//.text : 00007FF69147180F                 lea     rdx, Str1
//.text : 00007FF691471816                 mov     rcx, r14
//.text : 00007FF691471819                 call    sub_7FF690CD9F90
//.text : 00007FF69147181E                 mov     edx, 5Bh; Val
//.text:00007FF691471823                 mov     rcx, r15; Str
//.text:00007FF691471826                 mov     rbp, r15
//.text : 00007FF691471829                 call    cs : __imp_strchr
//.text : 00007FF69147182F                 mov     rdi, rax
//.text : 00007FF691471832                 test    rax, rax
//.text : 00007FF691471835                 jz      loc_7FF6914718FB
//.text : 00007FF69147183B
//.text : 00007FF69147183B loc_7FF69147183B : ; DATA XREF : .rdata : 00007FF6927C4F50↓o
//.text : 00007FF69147183B;.rdata:00007FF6927C4F60↓o ...
//.text : 00007FF69147183B                 mov[rsp + 38h + arg_10], rsi
//.text : 00007FF691471840
//.text : 00007FF691471840 loc_7FF691471840 : ; CODE XREF : sub_7FF691471740 + 1B0↓j
//.text : 00007FF691471840                 mov     edx, 5Dh; Val
//.text:00007FF691471845                 mov     rcx, rdi; Str
//.text:00007FF691471848                 call    cs : __imp_strchr
//.text : 00007FF69147184E                 mov     rsi, rax
//.text : 00007FF691471851                 test    rax, rax
//.text : 00007FF691471854                 jz      short loc_7FF6914718BB
//.text : 00007FF691471856                 mov     edx, 3Dh; Val
//.text:00007FF69147185B                 mov     byte ptr[rax], 0
//.text : 00007FF69147185E                 mov     rcx, rdi; Str
//.text:00007FF691471861                 call    cs : __imp_strchr
//.text : 00007FF691471867                 mov     rbx, rax
//.text : 00007FF69147186A                 test    rax, rax
//.text : 00007FF69147186D                 jz      short loc_7FF69147187E
//.text : 00007FF69147186F                 cmp     rax, rsi
//.text : 00007FF691471872                 jbe     short loc_7FF691471878
//.text : 00007FF691471874                 xor     ebx, ebx
//.text : 00007FF691471876                 jmp     short loc_7FF69147187E
//.text : 00007FF691471878; -------------------------------------------------------------------------- -
//.text:00007FF691471878
//.text : 00007FF691471878 loc_7FF691471878 : ; CODE XREF : sub_7FF691471740 + 132↑j
//.text : 00007FF691471878                 mov     byte ptr[rax], 0
//.text : 00007FF69147187B                 inc     rbx
//.text : 00007FF69147187E
//.text : 00007FF69147187E loc_7FF69147187E : ; CODE XREF : sub_7FF691471740 + 12D↑j
//.text : 00007FF69147187E; sub_7FF691471740 + 136↑j
//.text:00007FF69147187E                 mov     rdx, rbp
//.text : 00007FF691471881                 mov     byte ptr[rdi], 0
//.text : 00007FF691471884                 mov     rcx, r14
//.text : 00007FF691471887                 call    sub_7FF690CD9290
//.text : 00007FF69147188C                 lea     rcx, [rdi + 1]; Str1
//.text:00007FF691471890                 lea     rdx, aSurv; "SURV"
//.text:00007FF691471897                 call    cs : __imp__stricmp
//.text : 00007FF69147189D                 test    eax, eax
//.text : 00007FF69147189F                 jnz     short loc_7FF6914718B5
//.text : 00007FF6914718A1                 call    sub_7FF6914B9220
//.text : 00007FF6914718A6                 test    al, al
//.text : 00007FF6914718A8                 jz      short loc_7FF6914718B5
//.text : 00007FF6914718AA                 mov     rdx, rbx
//.text : 00007FF6914718AD                 mov     rcx, r14
//.text : 00007FF6914718B0                 call    sub_7FF690CD9290
//.text : 00007FF6914718B5
//.text : 00007FF6914718B5 loc_7FF6914718B5 : ; CODE XREF : sub_7FF691471740 + 15F↑j
//.text : 00007FF6914718B5; sub_7FF691471740 + 168↑j
//.text:00007FF6914718B5                 lea     rbp, [rsi + 1]
//.text : 00007FF6914718B9                 jmp     short loc_7FF6914718DC
//.text : 00007FF6914718BB; -------------------------------------------------------------------------- -
//.text:00007FF6914718BB
//.text : 00007FF6914718BB loc_7FF6914718BB : ; CODE XREF : sub_7FF691471740 + 114↑j
//.text : 00007FF6914718BB                 mov     rdx, rbp
//.text : 00007FF6914718BE                 mov     byte ptr[rdi], 0
//.text : 00007FF6914718C1                 mov     rcx, r14
//.text : 00007FF6914718C4                 call    sub_7FF690CD9290
//.text : 00007FF6914718C9                 lea     rdx, asc_7FF6922A66D0; "["
//.text:00007FF6914718D0                 mov     rcx, r14
//.text : 00007FF6914718D3                 call    sub_7FF690CD9290
//.text : 00007FF6914718D8                 lea     rbp, [rdi + 1]
//.text : 00007FF6914718DC
//.text : 00007FF6914718DC loc_7FF6914718DC : ; CODE XREF : sub_7FF691471740 + 179↑j
//.text : 00007FF6914718DC                 mov     edx, 5Bh; Val
//.text:00007FF6914718E1                 mov     rcx, rbp; Str
//.text:00007FF6914718E4                 call    cs : __imp_strchr
//.text : 00007FF6914718EA                 mov     rdi, rax
//.text : 00007FF6914718ED                 test    rax, rax
//.text : 00007FF6914718F0                 jnz     loc_7FF691471840
//.text : 00007FF6914718F6                 mov     rsi, [rsp + 38h + arg_10]
//.text : 00007FF6914718FB
//.text : 00007FF6914718FB loc_7FF6914718FB : ; CODE XREF : sub_7FF691471740 + F5↑j
//.text : 00007FF6914718FB; DATA XREF : .pdata : 00007FF69411E4B8↓o ...
//.text : 00007FF6914718FB                 mov     rdx, rbp
//.text : 00007FF6914718FE                 mov     rcx, r14
//.text : 00007FF691471901                 call    sub_7FF690CD9290
//.text : 00007FF691471906                 cmp     cs : dword_7FF692AB6C88, 2
//.text : 00007FF69147190D                 mov     rdi, [rsp + 38h + var_10]
//.text : 00007FF691471912                 mov     rbp, [rsp + 38h + arg_8]
//.text : 00007FF691471917                 mov     rbx, [rsp + 38h + arg_0]
//.text : 00007FF69147191C                 jz      short loc_7FF691471931
//.text : 00007FF69147191E
//.text : 00007FF69147191E loc_7FF69147191E : ; DATA XREF : .pdata : 00007FF69411E4C4↓o
//.text : 00007FF69147191E;.pdata:00007FF69411E4D0↓o
//.text : 00007FF69147191E                 lea     rdx, dword_7FF692AB6C88
//.text : 00007FF691471925                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF69147192C                 call    sub_7FF6917E0D30
//.text : 00007FF691471931
//.text : 00007FF691471931 loc_7FF691471931 : ; CODE XREF : sub_7FF691471740 + 1DC↑j
//.text : 00007FF691471931                 xor     edx, edx
//.text : 00007FF691471933                 lea     rcx, unk_7FF692AB6800
//.text : 00007FF69147193A                 call    sub_7FF6917DFE60
//.text : 00007FF69147193F                 mov     rcx, rax
//.text : 00007FF691471942                 mov     rdx, r15
//.text : 00007FF691471945                 call    sub_7FF6917E2120
//.text : 00007FF69147194A                 mov     r15, [rsp + 38h + var_18]
//.text : 00007FF69147194F
//.text : 00007FF69147194F loc_7FF69147194F : ; CODE XREF : sub_7FF691471740 + 28↑j
//.text : 00007FF69147194F; DATA XREF : .pdata : 00007FF69411E4D0↓o ...
//.text : 00007FF69147194F                 add     rsp, 30h
//.text : 00007FF691471953                 pop     r14
//.text : 00007FF691471955                 retn
//.text : 00007FF691471955 sub_7FF691471740 endp
//.text : 00007FF691471955
//.text : 00007FF691471955; -------------------------------------------------------------------------- -

float CAHZScaleform::GetBaseDamage(TESAmmo* pthisAmmo)
{
   return pthisAmmo->settings.damage;
}

string CAHZScaleform::GetSoulLevelName(UInt8 soulLevel)
{
	if (m_soulMap.empty()) //Cache it,  No need to hit the game setting every time
	{
		SettingCollectionMap	* settings = *g_gameSettingCollection;
		m_soulMap[1] = string(settings->Get("sSoulLevelNamePetty")->data.s);
		m_soulMap[2] = string(settings->Get("sSoulLevelNameLesser")->data.s);
		m_soulMap[3] = string(settings->Get("sSoulLevelNameCommon")->data.s);
		m_soulMap[4] = string(settings->Get("sSoulLevelNameGreater")->data.s);
		m_soulMap[5] = string(settings->Get("sSoulLevelNameGrand")->data.s);
	}
	if (m_soulMap.find(soulLevel) == m_soulMap.end())
	{
		return string("");
	}
	return m_soulMap[soulLevel];
}

bool MagicDisallowEnchanting(BGSKeywordForm *pKeywords)
{
	if (pKeywords)
	{
		for (UInt32 k = 0; k < pKeywords->numKeywords; k++) {
			if (pKeywords->keywords[k]) {
				string keyWordName = string(pKeywords->keywords[k]->keyword.Get());
				if (keyWordName == "MagicDisallowEnchanting")
				{
					return true;  // Is enchanted, but cannot be enchanted by player
				}
			}
		}
	}
	return false;
}

UInt32 CAHZScaleform::GetIsKnownEnchantment(TESObjectREFR *targetRef)
{
	PlayerCharacter* pPC = (*g_thePlayer);
	TESForm *baseForm;
	if (pPC && targetRef && (baseForm = targetRef->baseForm) &&
		(baseForm->GetFormType() == kFormType_Weapon || baseForm->GetFormType() == kFormType_Armor || baseForm->GetFormType() == kFormType_Ammo))
	{
		EnchantmentItem * enchantment = NULL;
		TESEnchantableForm * enchantable = DYNAMIC_CAST(baseForm, TESForm, TESEnchantableForm);
		bool wasExtra = false;
		if (enchantable) { // Check the item for a base enchantment
			enchantment = enchantable->enchantment;
		}
		if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(targetRef->extraData.GetByType(kExtraData_Enchantment)))
		{
			wasExtra = true;
			enchantment = extraEnchant->enchant;
		}

		if (enchantment)
		{
			if ((enchantment->flags & TESForm::kFlagPlayerKnows) == TESForm::kFlagPlayerKnows) {
				return MagicDisallowEnchanting(DYNAMIC_CAST(enchantment, EnchantmentItem, BGSKeywordForm)) ? 2 : 1;
			}
			else if (MagicDisallowEnchanting(DYNAMIC_CAST(enchantment, EnchantmentItem, BGSKeywordForm)))
			{
				return 2;
			}

			EnchantmentItem * baseEnchantment = (EnchantmentItem *)(enchantment->data.baseEnchantment);
			if (baseEnchantment)
			{
				if ((baseEnchantment->flags & TESForm::kFlagPlayerKnows) == TESForm::kFlagPlayerKnows) {
					return MagicDisallowEnchanting(DYNAMIC_CAST(baseEnchantment, EnchantmentItem, BGSKeywordForm)) ? 2 : 1;
				}
				else if (MagicDisallowEnchanting(DYNAMIC_CAST(baseEnchantment, EnchantmentItem, BGSKeywordForm)))
				{
					return 2;
				}
			}
		}

		// Its safe to assume that if it not a base enchanted item, that it was enchanted by the player and therefore, they
		// know the enchantment
		if (wasExtra)
		{
			return 1;
		}
		else if (enchantable) {
			return MagicDisallowEnchanting(DYNAMIC_CAST(enchantable, TESEnchantableForm, BGSKeywordForm)) ? 2 : 0;
		}

	}
	return 0;
}
double CAHZScaleform::GetActualDamage(AHZWeaponData *weaponData)
{
   if (!weaponData)
      return 0.0;

   PlayerCharacter* pPC = (*g_thePlayer);

   if (pPC)
   {
      InventoryEntryData objDesc(weaponData->equipData.pForm, 0);

      // Allocate a list to send
      objDesc.extendDataList = new tList<BaseExtraList>();

      if (weaponData->equipData.pExtraData)
      {
         objDesc.extendDataList->Insert(weaponData->equipData.pExtraData);
      }

      float fDamage = CALL_MEMBER_FN(pPC, GetDamage)(&objDesc);

      // Delete the allocated dummy list
      delete objDesc.extendDataList;

      // This could be rounded, but the the script decide
      return mRound(fDamage);
   }

   return 0.0;
}

double CAHZScaleform::GetArmorWarmthRating(AHZArmorData* armorData)
{
   if (!armorData->armor)
      return 0.0;

   InventoryEntryData objDesc(armorData->equipData.pForm, 0);

   // Allocate a dummy list so skyrim does not crash. For armor information
   // skyrim doesn't appear to need the list
   objDesc.extendDataList = new tList<BaseExtraList>();
   if (armorData->equipData.pExtraData)
   {
      objDesc.extendDataList->Insert(armorData->equipData.pExtraData);
   }

   double fRating = GetArmorWarmthRating_Native(objDesc.type);

   // Delete the allocated dummy list
   delete objDesc.extendDataList;

   // This could be rounded, but the the script decide
   return mRound(fRating);

   return 0.0;
}

double CAHZScaleform::GetArmorWarmthRating(TESObjectREFR* targetRef)
{
#ifdef IS_VR
	return 0.0;
#else

   if (!targetRef || !targetRef->baseForm)
      return 0.0;

   if (targetRef->baseForm->GetFormType() != kFormType_Armor || !IsSurvivalMode())
   {
      return 0.0;
   }

   AHZArmorData armorData(targetRef);
   return GetArmorWarmthRating(&armorData);
#endif
}

double CAHZScaleform::GetPlayerWarmthRating(void)
{

   return 0.0;
}

double CAHZScaleform::GetActualArmorRating(AHZArmorData* armorData)
{
   if (!armorData->armor)
      return 0.0;

   PlayerCharacter* pPC = (*g_thePlayer);

   if (pPC)
   {
      InventoryEntryData objDesc(armorData->equipData.pForm, 0);

      // Allocate a dummy list so skyrim does not crash. For armor information
      // skyrim doesn't appear to need the list
      objDesc.extendDataList = new tList<BaseExtraList>();
      if (armorData->equipData.pExtraData)
      {
         objDesc.extendDataList->Insert(armorData->equipData.pExtraData);
      }

      double fRating = CALL_MEMBER_FN(pPC, GetArmorValue)(&objDesc);

      // Delete the allocated dummy list
      delete objDesc.extendDataList;

      // This could be rounded, but the the script decide
      return mRound(fRating);
   }

   return 0.0;
}

double CAHZScaleform::GetTotalActualArmorRating(void)
{
   double totalRating = 0.0;
   double rating = 0.0;
   // Keep a list of items to make sure they are not added more than once
   // Some items take up more than one slot
   std::list<TESForm*> clist;
   for (UInt64 slot = 1; slot <= (UInt64)0x2000; slot <<= 1)
   {
      AHZArmorData armorData = CAHZArmorInfo::GetArmorFromSlotMask(slot);
      if (armorData.equipData.pForm)
      {
         if (find(clist.begin(), clist.end(), armorData.equipData.pForm) == clist.end())
         {
            clist.push_front(armorData.equipData.pForm);
            if (armorData.armor)
            {
               totalRating += GetActualArmorRating(&armorData);
            }
         }
      }
   }
   return mRound(totalRating);
}

double CAHZScaleform::GetTotalWarmthRating(void)
{
   PlayerCharacter* pPC = (*g_thePlayer);

   if (!pPC)
   {
      return 0.0;
   }

   return GetActorWarmthRating_Native(pPC, 0.0);
}

double CAHZScaleform::mRound(double r)
{
   return (r >= 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

double CAHZScaleform::GetArmorRatingDiff(TESObjectREFR *thisArmor)
{
   UInt64 slot = 1;
   float oldArmorRating = 0.0;
   float newArmorRating = 0.0;
   float oldTotalArmorRating = 0.0;
   float newTotalArmorRating = 0.0;
   double deltaRating = 0.0;
   if (!thisArmor)
      return 0.0;

   // Get the new armor rating
   AHZArmorData armorData(thisArmor);
   if (!armorData.armor)
      return 0.0;

   newArmorRating = GetActualArmorRating(&armorData);

   // Get the armor rating from the armor that shares the same slot
   AHZArmorData sameSlotData = CAHZArmorInfo::GetArmorFromSlotMask(
      armorData.armor->bipedObject.GetSlotMask());
   if (sameSlotData.armor)
   {
      oldArmorRating = GetActualArmorRating(&sameSlotData);
   }

   // Get the total
   oldTotalArmorRating = GetTotalActualArmorRating();

   newTotalArmorRating = (oldTotalArmorRating - oldArmorRating) + newArmorRating;

   deltaRating = newTotalArmorRating - oldTotalArmorRating;

   return deltaRating;
}

double CAHZScaleform::GetWarmthRatingDiff(TESObjectREFR *thisArmor)
{
   UInt64 slot = 1;
   float oldArmorRating = 0.0;
   float newArmorRating = 0.0;
   float oldTotalArmorRating = 0.0;
   float newTotalArmorRating = 0.0;
   double deltaRating = 0.0;
   if (!thisArmor)
      return 0.0;

   // Get the new armor rating
   AHZArmorData armorData(thisArmor);
   if (!armorData.armor)
      return 0.0;

   newArmorRating = GetArmorWarmthRating(&armorData);

   // Get the armor rating from the armor that shares the same slot
   AHZArmorData sameSlotData = CAHZArmorInfo::GetArmorFromSlotMask(
      armorData.armor->bipedObject.GetSlotMask());
   if (sameSlotData.armor)
   {
      oldArmorRating = GetArmorWarmthRating(&sameSlotData);
   }

   // Get the total
   oldTotalArmorRating = GetTotalWarmthRating();

   newTotalArmorRating = (oldTotalArmorRating - oldArmorRating) + newArmorRating;

   deltaRating = newTotalArmorRating - oldTotalArmorRating;

   return deltaRating;
}

double CAHZScaleform::GetTotalActualWeaponDamage(void)
{
   float totalWeaponDamage = 0.0;
   bool is2Handed = FALSE;
   AHZWeaponData leftWeapon = CAHZWeaponInfo::GetLeftHandWeapon();
   AHZWeaponData rightWeapon = CAHZWeaponInfo::GetRightHandWeapon();
   AHZWeaponData equippedAmmo = CAHZWeaponInfo::GetEquippedAmmo();

   if (leftWeapon.weapon)
   {
      if (IsBow(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsCrossBow(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsTwoHanded(leftWeapon.weapon))
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
      else if (IsOneHanded(leftWeapon.weapon))
      {
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
   }

   if (rightWeapon.weapon)
   {
      if (IsBow(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsCrossBow(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            totalWeaponDamage += GetActualDamage(&equippedAmmo);
         }
      }
      else if (IsTwoHanded(rightWeapon.weapon) && !is2Handed)
      {
         is2Handed = TRUE;
         totalWeaponDamage = GetActualDamage(&rightWeapon);
      }
      else if (IsOneHanded(rightWeapon.weapon))
      {
         // Add the damage from the second weapon
         totalWeaponDamage += GetActualDamage(&rightWeapon);
      }
   }
   return totalWeaponDamage;
}

bool CAHZScaleform::isBolt(TESAmmo *thisAmmo)
{
   return (thisAmmo->isBolt());
}

double CAHZScaleform::GetWeaponDamageDiff(TESObjectREFR *targetWeaponOrAmmo)
{
   double totalWeaponDamage = 0.0;
   double targetArrowDamage = 0.0;
   AHZWeaponData leftWeapon;
   AHZWeaponData rightWeapon;
   AHZWeaponData targetWeapon;
   AHZWeaponData equippedAmmo;

   if (!targetWeaponOrAmmo)
      return 0.0;

   targetWeapon = CAHZWeaponInfo::GetWeaponInfo(targetWeaponOrAmmo);
   equippedAmmo = CAHZWeaponInfo::GetEquippedAmmo();

   //DumpClass(targetWeapon.ammo, 256);

    // Must be a weapon or armor targeted
   if (targetWeapon.weapon)
   {
      if (equippedAmmo.ammo)
      {
         // TODO Try to get the equipped arrow with extra data
         if (IsBow(targetWeapon.weapon) && !isBolt(equippedAmmo.ammo))
         {
            targetArrowDamage = GetActualDamage(&equippedAmmo);
         }
         else if (IsCrossBow(targetWeapon.weapon) && isBolt(equippedAmmo.ammo))
         {
            targetArrowDamage = GetActualDamage(&equippedAmmo);
         }
      }
   }
   else if (targetWeapon.ammo)
   {
      //targetAmmo = targetWeapon.ammo;
   }
   else
   {
      return 0.0;
   }

   rightWeapon = CAHZWeaponInfo::GetRightHandWeapon();
   leftWeapon = CAHZWeaponInfo::GetLeftHandWeapon();

   if (leftWeapon.weapon)
   {
      if (IsBow(leftWeapon.weapon))
      {
         float tempDamage = GetActualDamage(&leftWeapon);
         float tempArrowDamage = 0.0;

         // Add the arrow damage
         if (equippedAmmo.ammo && !isBolt(equippedAmmo.ammo))
         {
            tempArrowDamage = GetActualDamage(&equippedAmmo);
            tempDamage += tempArrowDamage;
         }

         if (targetWeapon.weapon)
         {
            return (GetActualDamage(&targetWeapon) + targetArrowDamage) - tempDamage;
         }
         else if (targetWeapon.ammo && !isBolt(targetWeapon.ammo))
         {
            return ((tempDamage - tempArrowDamage) + GetActualDamage(&targetWeapon)) - tempDamage;
         }
         else
         {
            return 0.0;
         }
      }
      else if (IsCrossBow(leftWeapon.weapon))
      {
         float tempDamage = GetActualDamage(&leftWeapon);
         float tempArrowDamage = 0.0;

         // Add the arrow damage
         if (equippedAmmo.ammo && isBolt(equippedAmmo.ammo))
         {
            tempArrowDamage = GetActualDamage(&equippedAmmo);
            tempDamage += tempArrowDamage;
         }

         if (targetWeapon.weapon)
         {
            return (GetActualDamage(&targetWeapon) + targetArrowDamage) - tempDamage;
         }
         else if (targetWeapon.ammo && isBolt(targetWeapon.ammo))
         {
            return ((tempDamage - tempArrowDamage) + GetActualDamage(&targetWeapon) - tempDamage);
         }
         else
         {
            return 0.0;
         }
      }
      else if (IsTwoHanded(leftWeapon.weapon) && targetWeapon.weapon)
      {
         return (GetActualDamage(&targetWeapon) + targetArrowDamage) - GetActualDamage(&leftWeapon);
      }
      else if (IsOneHanded(leftWeapon.weapon))
      {
         totalWeaponDamage = GetActualDamage(&leftWeapon);
      }
   }

   if (rightWeapon.weapon)
   {
      if (IsOneHanded(rightWeapon.weapon))
      {
         // Add the damage from the second weapon
         totalWeaponDamage += GetActualDamage(&rightWeapon);
      }
   }

   // If we made it this far either no weapon is equipped or single handed weapons are equipped
   if (targetWeapon.weapon)
   {
      return (GetActualDamage(&targetWeapon) + targetArrowDamage) - totalWeaponDamage;
   }

   return 0.0;
}

bool CAHZScaleform::IsTwoHanded(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_TwoHandSword ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_TwoHandAxe ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_2HS ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_2HA ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2 ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
}

bool CAHZScaleform::IsOneHanded(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandSword ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandDagger ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandAxe ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_OneHandMace ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HS ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HD ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HA ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_1HM);
}

//bool CAHZUtility::IsBowType(TESObjectWEAP * thisWeapon)
//{
//			//kType_HandToHandMelee = 0,
//			//kType_OneHandSword,
//			//kType_OneHandDagger,
//			//kType_OneHandAxe,
//			//kType_OneHandMace,
//			//kType_TwoHandSword,
//			//kType_TwoHandAxe,
//			//kType_Bow,
//			//kType_Staff,
//			//kType_CrossBow,
//			//kType_H2H,
//			//kType_1HS,
//			//kType_1HD,
//			//kType_1HA,
//			//kType_1HM,
//			//kType_2HS,
//			//kType_2HA,
//			//kType_Bow2,
//			//kType_Staff2,
//			//kType_CBow
//	return (thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2 ||
//			thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
//}

bool CAHZScaleform::IsBow(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_Bow2);
}

bool CAHZScaleform::IsCrossBow(TESObjectWEAP * thisWeapon)
{
   //kType_HandToHandMelee = 0,
   //kType_OneHandSword,
   //kType_OneHandDagger,
   //kType_OneHandAxe,
   //kType_OneHandMace,
   //kType_TwoHandSword,
   //kType_TwoHandAxe,
   //kType_Bow,
   //kType_Staff,
   //kType_CrossBow,
   //kType_H2H,
   //kType_1HS,
   //kType_1HD,
   //kType_1HA,
   //kType_1HM,
   //kType_2HS,
   //kType_2HA,
   //kType_Bow2,
   //kType_Staff2,
   //kType_CBow
   return (thisWeapon->type() == TESObjectWEAP::GameData::kType_CrossBow ||
      thisWeapon->type() == TESObjectWEAP::GameData::kType_CBow);
}

AlchemyItem * CAHZScaleform::GetAlchemyItemFromLeveledList(TESForm *thisObject)
{
   if (thisObject->formType == kFormType_LeveledItem)
   {
      TESLevItem *lvli = DYNAMIC_CAST(thisObject, TESForm, TESLevItem);

      // Get the first form and see if it is an ingredient
      if (lvli->leveledList.length > 0)
      {
         for (int i = 0; i < lvli->leveledList.length; i++)
         {
            TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
            if (itemform)
            {
               if (itemform->formType == kFormType_Potion)
               {
                  AlchemyItem *alchemyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchemyItem;
               }
            }
         }
         //for (int i = 0; i < lvli->leveledList.length; i++)
         //{
         //   TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
         //   if (itemform)
         //   {
         //      if (itemform->formType == kFormType_Ingredient)
         //      {
         //         IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
         //         return ingredient;
         //      }
         //      // Nested leveled lists
         //      else if (itemform->formType == kFormType_LeveledItem)
         //      {
         //         return GetIngredientFromLeveledList(itemform);
         //      }
         //   }
         //}
      }
   }

   return NULL;
}

IngredientItem* CAHZScaleform::GetIngredientFromLeveledList(TESForm *thisObject)
{
   if (thisObject->formType == kFormType_LeveledItem)
   {
      TESLevItem *lvli = DYNAMIC_CAST(thisObject, TESForm, TESLevItem);

      // Get the first form and see if it is an ingredient
      if (lvli->leveledList.length > 0)
      {
         for (int i = 0; i < lvli->leveledList.length; i++)
         {
            TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
            if (itemform)
            {
               if (itemform->formType == kFormType_Ingredient)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
         //for (int i = 0; i < lvli->leveledList.length; i++)
         //{
         //   TESForm *itemform = (TESForm *)lvli->leveledList.entries[i].form;
         //   if (itemform)
         //   {
         //      if (itemform->formType == kFormType_Ingredient)
         //      {
         //         IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
         //         return ingredient;
         //      }
         //      // Nested leveled lists
         //      else if (itemform->formType == kFormType_LeveledItem)
         //      {
         //         return GetIngredientFromLeveledList(itemform);
         //      }
         //   }
         //}
      }
   }

   return NULL;
}

IngredientItem* CAHZScaleform::GetIngredient(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   if (thisObject->GetFormType() == kFormType_Ingredient)
      return DYNAMIC_CAST(thisObject, TESForm, IngredientItem);

   if (thisObject->GetFormType() == kFormType_Flora)
   {
      TESFlora *flora = DYNAMIC_CAST(thisObject, TESForm, TESFlora);
      if (flora)
      {
         TESForm *form = (TESForm *)flora->produce.produce;

         // If the ingredient is actually an ingredient
         if (form->formType == kFormType_Ingredient)
         {
            return DYNAMIC_CAST(flora->produce.produce, TESForm, IngredientItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetIngredientFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Ingredient)
            {
               IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
               return ingredient;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
      }
   }
   else if (thisObject->GetFormType() == kFormType_Tree)
   {
      TESObjectTREE *tree = DYNAMIC_CAST(thisObject, TESForm, TESObjectTREE);
      if (tree)
      {
         TESForm *form = (TESForm *)tree->produce.produce;//DYNAMIC_CAST(tree->produce.produce, IngredientItem, TESForm);

         // If the ingredient is actually an ingredient
         if (form->formType == kFormType_Ingredient)
         {
            return DYNAMIC_CAST(tree->produce.produce, TESForm, IngredientItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetIngredientFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Ingredient)
            {
               IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
               return ingredient;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  IngredientItem *ingredient = DYNAMIC_CAST(itemform, TESForm, IngredientItem);
                  return ingredient;
               }
            }
         }
      }
   }

   return NULL;
}

SpellItem* CAHZScaleform::GetSpellItem(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   return DYNAMIC_CAST(thisObject, TESForm, SpellItem);
}

AlchemyItem* CAHZScaleform::GetAlchemyItem(TESForm *thisObject)
{
   if (!thisObject)
      return NULL;

   TESObjectREFR*reference = AHZGetReference(thisObject);
   if (reference)
   {
      thisObject = reference->baseForm;
   }

   if (thisObject->GetFormType() == kFormType_Potion)
      return DYNAMIC_CAST(thisObject, TESForm, AlchemyItem);

   if (thisObject->GetFormType() == kFormType_Flora)
   {
      TESFlora *flora = DYNAMIC_CAST(thisObject, TESForm, TESFlora);
      if (flora)
      {
         TESForm *form = (TESForm *)flora->produce.produce;

         // If the food is actually food
         if (form->formType == kFormType_Potion)
         {
            return DYNAMIC_CAST(form, TESForm, AlchemyItem);
         }

         // If the food is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetAlchemyItemFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Potion)
            {
               AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
               return alchmyItem;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchmyItem;
               }
            }
         }
      }
   }
   else if (thisObject->GetFormType() == kFormType_Tree)
   {
      TESObjectTREE *tree = DYNAMIC_CAST(thisObject, TESForm, TESObjectTREE);
      if (tree)
      {
         TESForm *form = (TESForm *)tree->produce.produce;

         // If the produce is actually food
         if (form->formType == kFormType_Potion)
         {
            return DYNAMIC_CAST(form, TESForm, AlchemyItem);
         }

         // If the ingredient is actually a levelitem (Harvest overhaul mod or a coin purse)
         else if (form->formType == kFormType_LeveledItem)
         {
            TESForm *itemform = GetAlchemyItemFromLeveledList(form);

            if (!itemform)
            {
               return NULL;
            }
            else if (itemform->formType == kFormType_Potion)
            {
               AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
               return alchmyItem;
            }
         }
         else if (form->formType == kFormType_List)
         {
            BGSListForm *lvli = DYNAMIC_CAST(form, TESForm, BGSListForm);

            // Get the first form and see if it is an ingredient
            if (lvli->forms.count > 0)
            {
               TESForm *itemform = (TESForm *)lvli->forms.entries[0];
               if (itemform)
               {
                  AlchemyItem *alchmyItem = DYNAMIC_CAST(itemform, TESForm, AlchemyItem);
                  return alchmyItem;
               }
            }
         }
      }
   }

   return NULL;
}

bool CAHZScaleform::CanPickUp(UInt32 formType)
{
   return (formType == kFormType_Weapon ||
      formType == kFormType_Armor ||
      formType == kFormType_SoulGem ||
      formType == kFormType_Potion ||
      formType == kFormType_Misc ||
      formType == kFormType_Ingredient ||
      formType == kFormType_Book ||
      formType == kFormType_Ammo ||
      formType == kFormType_ScrollItem ||
      formType == kFormType_Outfit ||
      formType == kFormType_Key);
}

string CAHZScaleform::GetTargetName(TESForm *thisObject)
{
   string name;
   
   TESObjectREFR * reference = AHZGetReference(thisObject);

   if (!reference)
   {
      return name;
   }

   TESFullName* pFullName = DYNAMIC_CAST(reference->baseForm, TESForm, TESFullName);

   const char* displayName = reference->extraData.GetDisplayName(reference->baseForm);

   // If the name can be created
   if (displayName)
   {
      name.append(displayName);
   }
   // Use the base name
   else if (pFullName)
   {
      name.append(pFullName->name.data);
   }
   else // second attempt to get the name
   {
      name.append(reference->baseForm->GetFullName());
   }

   // If this is a soul gem, also get the gem size name
   if (reference->baseForm->formType == kFormType_SoulGem)
   {
      TESSoulGem *gem = DYNAMIC_CAST(reference->baseForm, TESForm, TESSoulGem);
      if (gem)
      {
         string soulName("");
         SettingCollectionMap	* settings = *g_gameSettingCollection;

		 soulName = GetSoulLevelName(gem->soulSize);


         if (soulName.length())
         {
            name.append(" (");
            name.append(soulName);
            name.append(")");
         }
      }
   }

   return name;
};

bool CAHZScaleform::GetIsBookAndWasRead(TESObjectREFR *theObject)
{
   if (!theObject)
      return false;

   if (theObject->baseForm->GetFormType() != kFormType_Book)
      return false;

   TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);
   if (item && ((item->data.flags & TESObjectBOOK::Data::kType_Read) == TESObjectBOOK::Data::kType_Read))
   {
      return true;
   }
   else
   {
      return false;
   }
}

static UInt32 lasttargetRef;
void CAHZScaleform::ProcessEnemyInformation(GFxFunctionHandler::Args * args)
{
	PlayerCharacter* pPC = (*g_thePlayer);
	CAHZActorData actorData;
	actorData.Level = 0;
	actorData.IsSentient = 0;
	UInt16 playerLevel = 0;
	UInt32 soulType = 0;

	if (pPC)
	{
		actorData = GetCurrentEnemyData();
		if (actorData.Level)
		{
			playerLevel = CALL_MEMBER_FN(pPC, GetLevel)();
			if (!actorData.IsSentient) {  // If sentient, then don't bother all sentients have grand soul gem levels
				soulType = CAHZActorInfo::GetSoulType(actorData.Level, actorData.IsSentient);
			}
		}
	}

	GFxValue obj;
	args->movie->CreateObject(&obj);
	if (actorData.Level)
	{
		RegisterNumber(&obj, "EnemyLevel", actorData.Level);
		RegisterNumber(&obj, "PlayerLevel", playerLevel);
		string soulName = GetSoulLevelName((UInt8)soulType);
		if (soulType && soulName.length())
		{
			RegisterString(&obj, args->movie, "Soul", soulName.c_str());
		}
	}

	if (args->args[0].HasMember("outObj"))
	{
		args->args[0].SetMember("outObj", &obj);
	}
}

string CAHZScaleform::GetArmorWeightClass(TESObjectREFR *theObject)
{
   string desc;

   if (!theObject)
      return desc;

   if (theObject->baseForm->GetFormType() != kFormType_Armor)
      return desc;

   TESObjectARMO *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectARMO);
   if (!item)
      return desc;

   ActorValueList * avList = ActorValueList::GetSingleton();
   if (avList && item->bipedObject.data.weightClass <= 1)
   {
      // Utilize the AV value to get the localized name for "Light Armor"
      if (item->bipedObject.data.weightClass == 0)
      {
         ActorValueInfo * info = avList->GetActorValue(12);
         if (info)
         {
            TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
            if (fname && fname->name.data)
            {
               desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
               desc.append(fname->name.data);
               desc.append("<\\FONT>");
            }
         }
      }

      // Utilize the AV value to get the localized name for "Heavy Armor"
      else if (item->bipedObject.data.weightClass == 1)
      {
         ActorValueInfo * info = avList->GetActorValue(11);
         if (info)
         {
            TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
            if (fname && fname->name.data)
            {
               desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
               desc.append(fname->name.data);
               desc.append("<\\FONT>");
            }
         }
      }
   }
   return desc;
};

string CAHZScaleform::GetValueToWeight(TESObjectREFR *theObject, const char * stringFromHUD, const char * vmTranslated)
{
	string desc;

	if (!theObject)
		return desc;

	if (!theObject->baseForm)
		return desc;

	if (!stringFromHUD)
		return desc;

	//<TEXTFORMAT INDENT="0" LEFTMARGIN="0" RIGHTMARGIN="0" LEADING="2"><P ALIGN="CENTER"><FONT FACE="$EverywhereMediumFont" SIZE="15" COLOR="#999999" KERNING="0">WEIGHT </FONT><FONT FACE="$EverywhereBoldFont" SIZE="24" COLOR="#FFFFFF" KERNING="0">0.5</FONT><FONT FACE="$EverywhereMediumFont" SIZE="15" COLOR="#999999" KERNING="0">      VALUE </FONT><FONT FACE="$EverywhereBoldFont" SIZE="24" COLOR="#FFFFFF" KERNING="0">21</FONT></P></TEXTFORMAT>

	// Using regex from the HUD string to extract the value and weight values.  The SKSE version are either broken or unreliable
	std::regex rgx(R"(\s+([0-9]*\.?[0-9]+))");
	std::smatch match;
	string s = stringFromHUD;
	const string cs = const_cast<string &>(s);
	vector<string> parts;

	while (regex_search(s, match, rgx))
	{
		if (!match.size())
		{
			return desc;
		}

		parts.push_back(match[0]);

		s = match.suffix();
	}

	if (parts.size() < 2)
	{
		return desc;
	}

	// The fixed positions of the matches (containing groups)
	string weight = parts[parts.size() - 2];
	string value = parts[parts.size() - 1];
	char *end;

	float weightValue = strtof(weight.c_str(), &end);
	float valueValue = strtof(value.c_str(), &end);

	// Don't show a neg or 0 ratio, its pointless
	if (weightValue <= 0.0 || valueValue <= 0.0)
	{
		return desc;
	}

	float vW = valueValue / weightValue;

	// Add the VW label
	desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
	desc.append(vmTranslated);
	desc.append(" <\\FONT>");

	char floatHold[64];
	size_t size = 64;

	//Rounding trick
	sprintf_s(floatHold, size, "%.2f", vW);
	vW = strtof(floatHold, &end);

	if (vW < 1.0)
	{
		sprintf_s(floatHold, size, "%.1g", vW);
	}
	else
	{
		sprintf_s(floatHold, size, "%.0f", vW);
	}

	desc.append("<FONT FACE=\"$EverywhereBoldFont\"SIZE=\"24\"COLOR=\"#FFFFFF\"KERNING=\"0\">");
	desc.append(floatHold);
	desc.append("<\\FONT>");

	return desc;


	//string desc;

	//if (!theObject)
	//	return desc;

	//if (!theObject->baseForm)
	//	return desc;

	//if (!stringFromHUD)
	//	return desc;

	//char *end;
	//float weightValue = 0.0;
	//float valueValue = 0.0;
	//std::istringstream iss(stringFromHUD);
	//std::string throwaway;

	//vector<string> parts;
	//int i = 0;
	//// Get the weight and value from the HUD text since there is no decoded way (reliably) to get the value for all forms and references
	//do 
	//{
	//	parts.push_back("");
	//} while (iss >> parts[i++]); // stream the different fields.  THe weight and height are the last
	//
	//if (parts.size() < 4)
	//{
	//	return desc;
	//}

	//// Remove the last empty string if one exists
	//if (parts[parts.size() - 1] == "")
	//{
	//	parts.pop_back();
	//}

	//// check the size again
	//if (parts.size() < 4)
	//{
	//	return desc;
	//}

	//// The last value should be the "Value"
	//// The third from last should be the weight
	//weightValue = atof(parts[parts.size() - 3].c_str());
	//valueValue = atof(parts[parts.size() - 1].c_str());

	//// Don't show a neg or 0 ratio, its pointless
	//if ((mRound(weightValue * 100) / 100) <= 0.0 || (mRound(valueValue * 100) / 100) <= 0.0)
	//{
	//	return desc;
	//}

	//float vW = valueValue / weightValue;

	//// Add the VW label
	//desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">     ");
	//desc.append(vmTranslated);
	//desc.append(" <\\FONT>");

	//char floatHold[64];
	//size_t size = 64;

	////Rounding trick
	//sprintf_s(floatHold, size, "%.2f", vW);
	//vW = strtof(floatHold, &end);

	//if (vW < 1.0)
	//{
	//	sprintf_s(floatHold, size, "%.1g", vW);
	//}
	//else
	//{
	//	sprintf_s(floatHold, size, "%.0f", vW);
	//}

	//desc.append("<FONT FACE=\"$EverywhereBoldFont\"SIZE=\"24\"COLOR=\"#FFFFFF\"KERNING=\"0\">");
	//desc.append(floatHold);
	//desc.append("<\\FONT>");
 //  
	//return desc;
};

string CAHZScaleform::GetBookSkill(TESObjectREFR *theObject)
{
   string desc;
   if (theObject->baseForm->GetFormType() == kFormType_Book)
   {
      TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);

      if (!item)
         return desc;

      // If this is a spell book, then it is not a skill book
      if ((item->data.flags & TESObjectBOOK::Data::kType_Spell) == TESObjectBOOK::Data::kType_Spell)
         return desc;

      if (((item->data.flags & TESObjectBOOK::Data::kType_Skill) == TESObjectBOOK::Data::kType_Skill) &&
         item->data.teaches.skill)
      {
         ActorValueList * avList = ActorValueList::GetSingleton();
         if (avList)
         {
            ActorValueInfo * info = avList->GetActorValue(item->data.teaches.skill);
            if (info)
            {
               TESFullName *fname = DYNAMIC_CAST(info, ActorValueInfo, TESFullName);
               if (fname && fname->name.data)
               {
                  desc.append("<FONT FACE=\"$EverywhereMediumFont\"SIZE=\"15\"COLOR=\"#999999\"KERNING=\"0\">       ");
                  desc.append(fname->name.data);
                  desc.append("<\\FONT>");
               }
            }
         }
      }
   }
   return desc;
}

void CAHZScaleform::AppendDescription(TESDescription *desObj, TESForm *parent, std::string& description)
{
   BSString bsDescription;
   string tempString = "";

   if (parent->GetFormType() == kFormType_Book)
   {
      CALL_MEMBER_FN(desObj, Get)(&bsDescription, parent, 0x4D414E43);
      if (&bsDescription)
      {
         tempString.clear();
         tempString.append(bsDescription.Get());
         if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
         {
            string formatted = "";
            FormatDescription(tempString, formatted);
            description.append(formatted);
         }
      }
   }
   else
   {
      BSString bsDescription2;
      TESDescription * desc = DYNAMIC_CAST(parent, TESForm, TESDescription);
      if (desc)
      {
         CALL_MEMBER_FN(desc, Get)(&bsDescription2, parent, 0x43534544);
         tempString.clear();
         if (&bsDescription2)
            tempString.append(bsDescription2.Get());
         if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
         {
            string formatted = "";
            FormatDescription(tempString, formatted);
            description.append(formatted);
         }
         else
         {
            CALL_MEMBER_FN(desc, Get)(&bsDescription2, parent, 0);
            tempString.clear();
            if (&bsDescription2)
               tempString.append(bsDescription2.Get());
            if (tempString != "LOOKUP FAILED!" && tempString.length() > 1)
            {
               string formatted = "";
               FormatDescription(tempString, formatted);
               description.append(formatted);
            }
         }
      }
   }
}

string CAHZScaleform::GetEffectsDescription(TESObjectREFR *theObject)
{
   BSString description;
   string effectDescription;
   string  desc;
   string effectsString;
   MagicItem * magicItem = NULL;

   if (!theObject)
      return desc;

   tArray<MagicItem::EffectItem*> *effectList = NULL;
   SettingCollectionMap *settings = *g_gameSettingCollection;

   if (theObject->baseForm->GetFormType() == kFormType_Potion)
   {
      AlchemyItem *item = DYNAMIC_CAST(theObject->baseForm, TESForm, AlchemyItem);

      if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
      {
         if (extraEnchant->enchant)
         {
            GetMagicItemDescription(extraEnchant->enchant, effectDescription);
            desc.append(effectDescription);
         }
      }

      if (item)
      {
         GetMagicItemDescription(item, effectDescription);
         desc.append(effectDescription);
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Weapon)
   {
      TESObjectWEAP *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectWEAP);

      // If there was no effects, then display athe description if available
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (item && !desc.length())
      {
         //Get enchantment description
         if (item && item->enchantable.enchantment)
         {
            GetMagicItemDescription(item->enchantable.enchantment, effectDescription);
            desc.append(effectDescription);
         }

         // Items modified by the player
         else if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
         {
            if (extraEnchant->enchant)
            {
               GetMagicItemDescription(extraEnchant->enchant, effectDescription);
               desc.append(effectDescription);
            }
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Armor)
   {
      TESObjectARMO *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectARMO);

      // If there was no effects, then display athe description if available
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (item && !desc.length())
      {
         //Get enchantment description
         if (item && item->enchantable.enchantment)
         {
            GetMagicItemDescription(item->enchantable.enchantment, effectDescription);
            desc.append(effectDescription);
         }

         // Items modified by the player
         else if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
         {
            if (extraEnchant->enchant)
            {
               GetMagicItemDescription(extraEnchant->enchant, effectDescription);
               desc.append(effectDescription);
            }
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Ammo)
   {
      TESAmmo *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESAmmo);

      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);
      }

      if (ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(theObject->extraData.GetByType(kExtraData_Enchantment))) // Enchanted
      {
         if (extraEnchant->enchant)
         {
            GetMagicItemDescription(extraEnchant->enchant, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_Book)
   {
      TESObjectBOOK *item = DYNAMIC_CAST(theObject->baseForm, TESForm, TESObjectBOOK);

      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description2, item, desc);
      }

      if (item &&
         ((item->data.flags & TESObjectBOOK::Data::kType_Spell) == TESObjectBOOK::Data::kType_Spell) && !desc.length())
      {
         if (item->data.teaches.spell)
         {
            GetMagicItemDescription(item->data.teaches.spell, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   else if (theObject->baseForm->GetFormType() == kFormType_ScrollItem)
   {
      ScrollItem *item = DYNAMIC_CAST(theObject->baseForm, TESForm, ScrollItem);
      if (item)
      {
         // Get the description if any (Mostly Dawnguard and Dragonborn stuff uses the descriptions)
         AppendDescription(&item->description, item, desc);

         if (!desc.length())
         {
            GetMagicItemDescription(item, effectDescription);
            desc.append(effectDescription);
         }
      }
   }
   return desc;
};

void CAHZScaleform::ProcessTargetEffects(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   AlchemyItem *alchemyItem = NULL;
   SpellItem *spellItem = NULL;
   IngredientItem *ingredientItem = NULL;
   string name;

   if (!args)
   {
      return;
   }

   bool calculateInvenotry = args->args[1].GetBool();

   if (!calculateInvenotry)
   {
      args->args[0].DeleteMember("inventoryObj");
   }

   // No valid reference
   if (!pTargetReference)
   {
      args->args[0].DeleteMember("effectsObj");
      args->args[0].DeleteMember("ingredientObj");
      args->args[0].DeleteMember("inventoryObj");
      return;
   }

   TESForm *targetForm = AHZGetForm(pTargetReference);

   // See if its an ingredient.  Note they are formated differently with known effects;
   if ((ingredientItem = GetIngredient(targetForm)) != NULL)
   {
      args->args[0].DeleteMember("effectsObj");
      BuildIngredientObject(ingredientItem, args);

      if (calculateInvenotry)
      {
         BuildInventoryObject(ingredientItem, args);
      }

      return;
   }

   // See if its harvestable food
   else if ((alchemyItem = GetAlchemyItem(targetForm)) != NULL)
   {
      string effectDescription;
      GetMagicItemDescription(alchemyItem, effectDescription);
      name.append(effectDescription);

      if (calculateInvenotry)
      {
         BuildInventoryObject(alchemyItem, args);
      }
   }

   // Spell items like blessings
   else if ((spellItem = GetSpellItem(targetForm)) != NULL)
   {
      AppendDescription(&(spellItem->description), spellItem, name);

      if (!name.length())
      {
         string effectDescription;
         GetMagicItemDescription(spellItem, effectDescription);
         name.append(effectDescription);
      }

      if (calculateInvenotry)
      {
         BuildInventoryObject(spellItem, args);
      }
   }
   else //For all effects from books, potions, weapon enchantments, etc.
   {
      // Get the effects description if it exists for this object
      name = GetEffectsDescription(pTargetReference);

      if (calculateInvenotry)
      {
         BuildInventoryObject(targetForm, args);
      }
   }

   // If the name contains a string
   if (name.length())
   {
      GFxValue obj;
      args->movie->CreateObject(&obj);

      name = CAHZUtilities::trim(name);

      RegisterString(&obj, args->movie, "effectsDescription",  name.c_str());

      // Add the object to the scaleform function
      args->args[0].SetMember("effectsObj", &obj);
   }
   else
   {
      args->args[0].DeleteMember("effectsObj");
   }
};

void CAHZScaleform::ProcessArmorClass(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   TESObjectREFR * pTargetReference = targetObject;
   static string weightClass;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   weightClass.clear();
   weightClass.append(GetArmorWeightClass(pTargetReference).c_str());

   SetResultString(args, weightClass.c_str());
};

void CAHZScaleform::ProcessValueToWeight(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   TESObjectREFR * pTargetReference = targetObject;
   static string valueToWeight;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   valueToWeight.clear();
   valueToWeight.append(GetValueToWeight(pTargetReference, args->args[0].GetString(), args->args[1].GetString()).c_str());

   SetResultString(args, valueToWeight.c_str());
};

void CAHZScaleform::ProcessBookSkill(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   static string bookSkill;

   // If the target is not valid or it can't be picked up by the player
   if (!pTargetReference)
   {
      SetResultString(args, "");
      return;
   }

   bookSkill.clear();
   bookSkill.append(GetBookSkill(pTargetReference).c_str());

   SetResultString(args,
      bookSkill.c_str());
};

void CAHZScaleform::SetResultString(GFxFunctionHandler::Args *args, const char * str)
{
   args->result->SetString(str);
};

void CAHZScaleform::ReplaceStringInPlace(std::string& subject, const std::string& search,
   const std::string& replace)
{
   size_t pos = 0;
   while ((pos = subject.find(search, pos)) != std::string::npos)
   {
      subject.replace(pos, search.length(), replace);
      pos += replace.length();
   }
};

void CAHZScaleform::ProcessTargetObject(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;
   float totalArmorOrWeapon = 0.0;
   float difference = 0.0;
   float totalWarmthRating = 0.0;
   float warmthDifference = 0.0;
   bool isSurvivalMode = false;
   float warmthRating = 0.0;

   if (!args)
   {
      return;
   }

   if (!targetObject)
   {
      args->args[0].DeleteMember("targetObj");
      return;
   }

   GFxValue obj;
   args->movie->CreateObject(&obj);

   if (pTargetReference->baseForm->GetFormType() == kFormType_Weapon ||
      pTargetReference->baseForm->GetFormType() == kFormType_Ammo)
   {
      TESForm *form = NULL;
      TESAmmo *ammo = NULL;

      // If ammo is NULL, it is OK
      totalArmorOrWeapon = GetTotalActualWeaponDamage();
      difference = GetWeaponDamageDiff(pTargetReference);
   }
   else if (pTargetReference->baseForm->GetFormType() == kFormType_Armor)
   {
      totalArmorOrWeapon = GetTotalActualArmorRating();
      difference = GetArmorRatingDiff(pTargetReference);

#ifndef IS_VR
      if (IsSurvivalMode())
      {
         isSurvivalMode = true;
         totalWarmthRating = GetTotalWarmthRating();
         warmthDifference = GetWarmthRatingDiff(pTargetReference);
         warmthRating = GetArmorWarmthRating(pTargetReference);
      }
#endif
   }

   // Enter the data into the Scaleform function
   RegisterNumber(&obj, "ratingOrDamage", totalArmorOrWeapon);
   RegisterNumber(&obj, "difference", difference);
   RegisterNumber(&obj, "totalWarmthRating", totalWarmthRating);
   RegisterNumber(&obj, "warmthRating", warmthRating);
   RegisterNumber(&obj, "warmthDifference", warmthDifference);
   RegisterBoolean(&obj, "isSurvivalMode", isSurvivalMode);

   float weight = CALL_MEMBER_FN(pTargetReference, GetWeight)();
   if (pTargetReference->extraData.HasType(kExtraData_Count))
   {
      ExtraCount* xCount = static_cast<ExtraCount*>(pTargetReference->extraData.GetByType(kExtraData_Count));
      if (xCount)
      {
         weight = weight * (float)(SInt16)(xCount->count & 0x7FFF);
      }
   }

   RegisterNumber(&obj, "objWeight", weight);

   // Used by the scaleform script to know if this is a weapon, armor, or something else
   RegisterNumber(&obj, "formType", pTargetReference->baseForm->GetFormType());
   args->args[0].SetMember("targetObj", &obj);
};

void CAHZScaleform::BuildIngredientObject(IngredientItem* ingredient, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   // If no ingredient, then we are done here
   if (!ingredient)
   {
      args->args[0].DeleteMember("ingredientObj");
      return;
   }

   string strings[4];

   // Not all ingredients have 4 effects
   UInt32 effectsCount = ingredient->effectItemList.count;

   for (int i = 0; i < 4; i++)
   {
      strings[i].clear();
      if (GetIsNthEffectKnown(ingredient, i))
      {
         MagicItem::EffectItem* pEI = NULL;
         ingredient->effectItemList.GetNthItem(i, pEI);
         if (pEI)
         {
            TESFullName* pFullName = DYNAMIC_CAST(pEI->mgef, TESForm, TESFullName);
            if (pFullName)
            {
               strings[i].append(pFullName->name.data); 
            }
         }
      }
   }
   GFxValue obj2;
   args->movie->CreateObject(&obj2);

   if (effectsCount >= 1)
      RegisterString(&obj2, args->movie, "effect1", strings[0].c_str());

   if (effectsCount >= 2)
      RegisterString(&obj2, args->movie, "effect2", strings[1].c_str());

   if (effectsCount >= 3)
      RegisterString(&obj2, args->movie, "effect3", strings[2].c_str());

   if (effectsCount >= 4)
      RegisterString(&obj2, args->movie, "effect4", strings[3].c_str());
   args->args[0].SetMember("ingredientObj", &obj2);
};

void CAHZScaleform::BuildInventoryObject(TESForm* form, GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   // Used to store the name
   string name;

   // Used to store the count of the item
   UInt32 itemCount;

   TESObjectREFR * reference = AHZGetReference(form);

   if (reference)
   {
      // Get the number of this in the inventory
      itemCount = CAHZPlayerInfo::GetItemAmount(reference->baseForm->formID);
      name = CAHZScaleform::GetTargetName(reference);
   }
   else if (form)
   {
      // Get the number of this in the inventory
      itemCount = CAHZPlayerInfo::GetItemAmount(form->formID);
      TESFullName* pFullName = DYNAMIC_CAST(form, TESForm, TESFullName);
      if (pFullName)
      {
         name.append(pFullName->name.data);
      }
   }

   // If the name contains a string
   if (name.length())
   {
      GFxValue obj;
      args->movie->CreateObject(&obj);

      RegisterString(&obj, args->movie, "inventoryName", name.c_str());
      RegisterNumber(&obj, "inventoryCount", itemCount);

      // Add the object to the scaleform function
      args->args[0].SetMember("inventoryObj", &obj);
   }
   else
   {
      args->args[0].DeleteMember("inventoryObj");
   }
};

void CAHZScaleform::RegisterString(GFxValue * dst, GFxMovieView * view, const char * name, const char * str)
{
   GFxValue	fxValue;
   fxValue.SetString(str);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::RegisterNumber(GFxValue * dst, const char * name, double value)
{
   GFxValue	fxValue;
   fxValue.SetNumber(value);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::RegisterBoolean(GFxValue * dst, const char * name, bool value)
{
   GFxValue	fxValue;
   fxValue.SetBool(value);
   dst->SetMember(name, &fxValue);
};

void CAHZScaleform::ProcessValidTarget(TESObjectREFR* targetObject, GFxFunctionHandler::Args *args)
{
   TESObjectREFR * pTargetReference = targetObject;

   if (!args)
   {
      return;
   }

   if (!pTargetReference)
   {
      // return false, indicating that the target object is not valid for acquiring data
      args->result->SetBool(false);
      args->args[0].DeleteMember("dataObj");
      return;
   }

   bool canCarry = false;

   TESForm *targetForm = AHZGetForm(pTargetReference);
   TESForm *spellItem = NULL;

   // If the target is not valid or it can't be picked up by the player
   if ((canCarry = (GetIngredient(targetForm) != NULL)) ||
      (canCarry = (GetAlchemyItem(targetForm) != NULL)) ||
      (canCarry = CanPickUp(pTargetReference->baseForm->GetFormType()) ||
      (pTargetReference->baseForm->GetFormType() == kFormType_Activator && targetForm)) ||
         ((spellItem = GetSpellItem(targetForm)) != NULL))
   {
      if (pTargetReference->baseForm->GetFormType() == kFormType_Activator && targetForm && !CanPickUp(targetForm->formType))
      {
         canCarry = false;
      }

      if (spellItem)
      {
         canCarry = false;
      }

      GFxValue obj;
      args->movie->CreateObject(&obj);

      RegisterBoolean(&obj, "canCarry", canCarry);

      // Add the object to the scaleform function
      args->args[0].SetMember("outObj", &obj);

      // return false, indicating that the target object is not valid for acquiring data
      args->result->SetBool(true);
   }
   else
   {
      // Add the object to the scaleform function
      args->args[0].DeleteMember("outObj");

      // The object is valid
      args->result->SetBool(false);
   }
}

void CAHZScaleform::ProcessPlayerData(GFxFunctionHandler::Args *args)
{
   if (!args)
   {
      return;
   }

   GFxValue obj;
   args->movie->CreateObject(&obj);

   UInt32 actorValue = LookupActorValueByName("InventoryWeight");
   float encumbranceNumber = ((*g_thePlayer)->actorValueOwner.GetCurrent(actorValue));
   actorValue = LookupActorValueByName("CarryWeight");
   float maxEncumbranceNumber = ((*g_thePlayer)->actorValueOwner.GetCurrent(actorValue));

   // Enter the data into the Scaleform function
   RegisterNumber(&obj, "encumbranceNumber", encumbranceNumber);
   RegisterNumber(&obj, "maxEncumbranceNumber", maxEncumbranceNumber);
   RegisterNumber(&obj, "goldNumber", CAHZPlayerInfo::GetGoldAmount());
   args->args[0].SetMember("playerObj", &obj);
}

void CAHZScaleform::GetMagicItemDescription(MagicItem * item, std::string& description)
{
   string outerString = "";
   description.clear();

   BSString temp;

   GetMagicItemDescription2(NULL, item, &temp);

#ifndef IS_VR
   char *temp2 = ProcessSurvivalMode(&temp);
#endif
   description.append(temp.Get());
}

void CAHZScaleform::FormatDescription(std::string& unFormated, std::string& formatted)
{
   string outerString = "";
   formatted.clear();

   const char numberFormatter[] = "<font face = '$EverywhereMediumFont' size = '20' color = '#FFFFFF'>%.0f</font>";
   const char stringFormatter[] = "<font face = '$EverywhereMediumFont' size = '20' color = '#FFFFFF'>%s</font>";
   char tempformatter[1000];
   bool canBeAdded = true;

#ifdef IS_VR
   canBeAdded = true;
#else
   std::regex survivalRegex("\\[SURV=.+\\]");
   std::smatch survivalMatch;
   const string survivalConst = const_cast<string &>(unFormated);

   if ((regex_search(survivalConst.begin(), survivalConst.end(), survivalMatch, survivalRegex)))
   {
      ReplaceStringInPlace(unFormated, "[SURV=", "");
      size_t offset = (size_t)(unFormated.length() - 1);
      size_t count = 1;
      unFormated.erase(offset, count);
      canBeAdded = IsSurvivalMode();
   }
   else
   {
      canBeAdded = true;
   }
#endif

   if (canBeAdded)
   {
      std::regex rgx("\\<\\d+?\\.?\\d*\\>|\\<\\w*\\>");
      std::smatch match;

      const string cs = const_cast<string &>(unFormated);
      string::const_iterator searchStart(cs.cbegin());
      string workingString = unFormated;

      while (regex_search(searchStart, cs.end(), match, rgx))
      {
         string temps = match[0];
         ReplaceStringInPlace(temps, "<", "");
         ReplaceStringInPlace(temps, ">", "");
         string origMatch = match[0];

         sprintf_s(tempformatter, 1000, stringFormatter, temps.c_str());
         ReplaceStringInPlace(workingString, origMatch, tempformatter);

         searchStart += match.position() + match.length();
      }
      outerString.append(workingString);
   }

   //TrimHelper(outerString);
   formatted.append(outerString);
}