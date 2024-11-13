// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xstreamhls.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XStreamhls_CfgInitialize(XStreamhls *InstancePtr, XStreamhls_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XStreamhls_Start(XStreamhls *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL) & 0x80;
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XStreamhls_IsDone(XStreamhls *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XStreamhls_IsIdle(XStreamhls *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XStreamhls_IsReady(XStreamhls *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XStreamhls_Continue(XStreamhls *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL) & 0x80;
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XStreamhls_EnableAutoRestart(XStreamhls *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XStreamhls_DisableAutoRestart(XStreamhls *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_AP_CTRL, 0);
}

void XStreamhls_Set_hbm_data(XStreamhls *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_HBM_DATA_DATA, (u32)(Data));
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_HBM_DATA_DATA + 4, (u32)(Data >> 32));
}

u64 XStreamhls_Get_hbm_data(XStreamhls *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_HBM_DATA_DATA);
    Data += (u64)XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_HBM_DATA_DATA + 4) << 32;
    return Data;
}

void XStreamhls_Set_output_data(XStreamhls *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_OUTPUT_DATA_DATA, (u32)(Data));
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_OUTPUT_DATA_DATA + 4, (u32)(Data >> 32));
}

u64 XStreamhls_Get_output_data(XStreamhls *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_OUTPUT_DATA_DATA);
    Data += (u64)XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_OUTPUT_DATA_DATA + 4) << 32;
    return Data;
}

void XStreamhls_InterruptGlobalEnable(XStreamhls *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_GIE, 1);
}

void XStreamhls_InterruptGlobalDisable(XStreamhls *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_GIE, 0);
}

void XStreamhls_InterruptEnable(XStreamhls *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_IER);
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_IER, Register | Mask);
}

void XStreamhls_InterruptDisable(XStreamhls *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_IER);
    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_IER, Register & (~Mask));
}

void XStreamhls_InterruptClear(XStreamhls *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamhls_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_ISR, Mask);
}

u32 XStreamhls_InterruptGetEnabled(XStreamhls *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_IER);
}

u32 XStreamhls_InterruptGetStatus(XStreamhls *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XStreamhls_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMHLS_CONTROL_ADDR_ISR);
}

