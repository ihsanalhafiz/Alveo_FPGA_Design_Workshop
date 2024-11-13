// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xstreamhls.h"

extern XStreamhls_Config XStreamhls_ConfigTable[];

#ifdef SDT
XStreamhls_Config *XStreamhls_LookupConfig(UINTPTR BaseAddress) {
	XStreamhls_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XStreamhls_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XStreamhls_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XStreamhls_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XStreamhls_Initialize(XStreamhls *InstancePtr, UINTPTR BaseAddress) {
	XStreamhls_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XStreamhls_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XStreamhls_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XStreamhls_Config *XStreamhls_LookupConfig(u16 DeviceId) {
	XStreamhls_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSTREAMHLS_NUM_INSTANCES; Index++) {
		if (XStreamhls_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XStreamhls_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XStreamhls_Initialize(XStreamhls *InstancePtr, u16 DeviceId) {
	XStreamhls_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XStreamhls_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XStreamhls_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

