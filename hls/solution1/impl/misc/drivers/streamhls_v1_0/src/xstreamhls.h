// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XSTREAMHLS_H
#define XSTREAMHLS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xstreamhls_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XStreamhls_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XStreamhls;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XStreamhls_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XStreamhls_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XStreamhls_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XStreamhls_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XStreamhls_Initialize(XStreamhls *InstancePtr, UINTPTR BaseAddress);
XStreamhls_Config* XStreamhls_LookupConfig(UINTPTR BaseAddress);
#else
int XStreamhls_Initialize(XStreamhls *InstancePtr, u16 DeviceId);
XStreamhls_Config* XStreamhls_LookupConfig(u16 DeviceId);
#endif
int XStreamhls_CfgInitialize(XStreamhls *InstancePtr, XStreamhls_Config *ConfigPtr);
#else
int XStreamhls_Initialize(XStreamhls *InstancePtr, const char* InstanceName);
int XStreamhls_Release(XStreamhls *InstancePtr);
#endif

void XStreamhls_Start(XStreamhls *InstancePtr);
u32 XStreamhls_IsDone(XStreamhls *InstancePtr);
u32 XStreamhls_IsIdle(XStreamhls *InstancePtr);
u32 XStreamhls_IsReady(XStreamhls *InstancePtr);
void XStreamhls_Continue(XStreamhls *InstancePtr);
void XStreamhls_EnableAutoRestart(XStreamhls *InstancePtr);
void XStreamhls_DisableAutoRestart(XStreamhls *InstancePtr);

void XStreamhls_Set_hbm_data(XStreamhls *InstancePtr, u64 Data);
u64 XStreamhls_Get_hbm_data(XStreamhls *InstancePtr);
void XStreamhls_Set_output_data(XStreamhls *InstancePtr, u64 Data);
u64 XStreamhls_Get_output_data(XStreamhls *InstancePtr);

void XStreamhls_InterruptGlobalEnable(XStreamhls *InstancePtr);
void XStreamhls_InterruptGlobalDisable(XStreamhls *InstancePtr);
void XStreamhls_InterruptEnable(XStreamhls *InstancePtr, u32 Mask);
void XStreamhls_InterruptDisable(XStreamhls *InstancePtr, u32 Mask);
void XStreamhls_InterruptClear(XStreamhls *InstancePtr, u32 Mask);
u32 XStreamhls_InterruptGetEnabled(XStreamhls *InstancePtr);
u32 XStreamhls_InterruptGetStatus(XStreamhls *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
