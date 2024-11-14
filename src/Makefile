# Compiler
GPP = g++

# Directories
SRCDIR = ./
OBJDIR = ./bin
OUTDIR = ./

# Compilation and Linking Flags
CFLAGS = -std=c++17 -g -O3 -I/opt/xilinx/xrt/include -L/opt/xilinx/xrt/lib -I/opt/xilinx/Vitis_HLS/2023.2/include -L/opt/xilinx/Vitis_HLS/2023.2/lib
LFLAGS = -I/opt/xilinx/xrt/include -L/opt/xilinx/xrt/lib -I/opt/xilinx/Vitis_HLS/2023.2/include -L/opt/xilinx/Vitis_HLS/2023.2/lib -lxrt_coreutil -lrt -lxrt_core -lxrt++

# Source and Object files
SRCS = $(SRCDIR)streamhls.cpp
OBJS = $(OBJDIR)/streamhls.o

# Output Executable
EXEC = $(OUTDIR)streamhls

# Default target
all: clean $(EXEC)

# Ensure the bin directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Linking
$(EXEC): $(OBJS)
	$(GPP) $(OBJS) $(LFLAGS) -o $@

# Compilation
$(OBJDIR)/%.o: $(SRCDIR)%.cpp | $(OBJDIR)
	$(GPP) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(EXEC) *.bin *.log *~ 
	rmdir $(OBJDIR) 2>/dev/null || true
