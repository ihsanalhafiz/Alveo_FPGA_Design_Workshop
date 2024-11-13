set SynModuleInfo {
  {SRCNAME entry_proc MODELNAME entry_proc RTLNAME streamhls_entry_proc}
  {SRCNAME fetch_from_hbm MODELNAME fetch_from_hbm RTLNAME streamhls_fetch_from_hbm
    SUBMODULES {
      {MODELNAME streamhls_flow_control_loop_pipe RTLNAME streamhls_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME streamhls_flow_control_loop_pipe_U}
    }
  }
  {SRCNAME process_kernel MODELNAME process_kernel RTLNAME streamhls_process_kernel
    SUBMODULES {
      {MODELNAME streamhls_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME streamhls_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME write_to_output_Pipeline_VITIS_LOOP_44_1 MODELNAME write_to_output_Pipeline_VITIS_LOOP_44_1 RTLNAME streamhls_write_to_output_Pipeline_VITIS_LOOP_44_1
    SUBMODULES {
      {MODELNAME streamhls_flow_control_loop_pipe_sequential_init RTLNAME streamhls_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME streamhls_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME write_to_output MODELNAME write_to_output RTLNAME streamhls_write_to_output}
  {SRCNAME streamhls MODELNAME streamhls RTLNAME streamhls IS_TOP 1
    SUBMODULES {
      {MODELNAME streamhls_fifo_w64_d4_S RTLNAME streamhls_fifo_w64_d4_S BINDTYPE storage TYPE fifo IMPL srl ALLOW_PRAGMA 1 INSTNAME output_data_c_U}
      {MODELNAME streamhls_fifo_w512_d4_A RTLNAME streamhls_fifo_w512_d4_A BINDTYPE storage TYPE fifo IMPL memory ALLOW_PRAGMA 1 INSTNAME input_stream_U}
      {MODELNAME streamhls_fifo_w512_d4_A RTLNAME streamhls_fifo_w512_d4_A BINDTYPE storage TYPE fifo IMPL memory ALLOW_PRAGMA 1 INSTNAME output_stream_U}
      {MODELNAME streamhls_start_for_write_to_output_U0 RTLNAME streamhls_start_for_write_to_output_U0 BINDTYPE storage TYPE fifo IMPL srl ALLOW_PRAGMA 1 INSTNAME start_for_write_to_output_U0_U}
      {MODELNAME streamhls_start_for_process_kernel_U0 RTLNAME streamhls_start_for_process_kernel_U0 BINDTYPE storage TYPE fifo IMPL srl ALLOW_PRAGMA 1 INSTNAME start_for_process_kernel_U0_U}
      {MODELNAME streamhls_gmem_m_axi RTLNAME streamhls_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME streamhls_control_s_axi RTLNAME streamhls_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
