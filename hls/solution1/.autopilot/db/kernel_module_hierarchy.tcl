set ModuleHierarchy {[{
"Name" : "streamhls","ID" : "0","Type" : "dataflow",
"SubInsts" : [
	{"Name" : "entry_proc_U0","ID" : "1","Type" : "sequential"},
	{"Name" : "fetch_from_hbm_U0","ID" : "2","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_16_1","ID" : "3","Type" : "pipeline"},]},
	{"Name" : "process_kernel_U0","ID" : "4","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_28_1","ID" : "5","Type" : "pipeline"},]},
	{"Name" : "write_to_output_U0","ID" : "6","Type" : "sequential",
		"SubInsts" : [
		{"Name" : "grp_write_to_output_Pipeline_VITIS_LOOP_44_1_fu_64","ID" : "7","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "VITIS_LOOP_44_1","ID" : "8","Type" : "pipeline"},]},]},]
}]}