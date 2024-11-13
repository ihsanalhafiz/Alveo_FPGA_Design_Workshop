############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project -reset ./hls
set_top streamhls
add_files ./src/streamhls.cpp
open_solution "solution1" -flow_target vitis
set_part {xcu55c-fsvh2892-2L-e}
create_clock -period 5 -name default
config_interface -m_axi_alignment_byte_size 64 -m_axi_latency 64 -m_axi_max_widen_bitwidth 512
config_rtl -register_reset_num 3
#config_compile -unsafe_math_optimizations 
source "./directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
