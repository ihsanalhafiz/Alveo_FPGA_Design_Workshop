#!/bin/bash

module load xilinx/2023.2

# Compile the kernel
make xclbin TARGET=hw PLATFORM=xilinx_u55c_gen3x16_xdma_3_202210_1
