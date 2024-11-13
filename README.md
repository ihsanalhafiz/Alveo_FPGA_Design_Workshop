# Alveo FPGA Design Workshop

This repository contains the materials and code for a workshop on deploying applications to the Xilinx Alveo U55C FPGA card. The focus is on using Vitis Unified Software Platform to develop and run a sample streaming High-Level Synthesis (HLS) application.

## Overview

The sample application provided here demonstrates a data streaming process using HLS, leveraging dataflow architecture for efficient data processing on FPGA. The application reads data from High Bandwidth Memory (HBM), processes it by multiplying each element by 2, and writes the results back to output memory.

## Requirements

### Hardware
- Xilinx Alveo U55C FPGA Card

### Software
- **Vitis Unified Software Platform** (version compatible with Alveo U55C)
- **Xilinx Runtime (XRT)** library to manage and interact with the FPGA device

### Installation

1. **Vitis Installation**  
   Download and install Vitis from the [Xilinx website](https://www.xilinx.com/support/download.html). Ensure compatibility with Alveo U55C and follow the official installation guide.

2. **XRT Installation**  
   Install XRT for your specific operating system. Refer to the [Xilinx XRT GitHub](https://github.com/Xilinx/XRT) for detailed installation instructions. 

3. **Environment Setup**  
   After installation, set up the environment variables by sourcing the Vitis and XRT setup scripts. For example:
   ```bash
   source /opt/xilinx/Vitis/<version>/settings64.sh
   source /opt/xilinx/xrt/setup.sh

# License
This repository is licensed under the MIT License.

# Acknowledgments
- Thanks to Artur Podobas Research Group [website](https://people.kth.se/~podobas/team.html)
- Thanks to the Xilinx Vitis and Alveo communities for their valuable resources and support.

