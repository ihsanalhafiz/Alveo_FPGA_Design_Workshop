#include <xrt/xrt_bo.h>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

// Constants
#define VECTOR_SIZE 16
#define NUM_VECTORS 256
#define BUFFER_SIZE (NUM_VECTORS)

using namespace std;

// Helper function to read binary file
std::vector<char> readBinaryFile(const std::string &xclbin_file_name) {
    std::ifstream bin_file(xclbin_file_name, std::ifstream::binary);
    bin_file.seekg(0, bin_file.end);
    size_t size = bin_file.tellg();
    bin_file.seekg(0, bin_file.beg);

    std::vector<char> buffer(size);
    bin_file.read(buffer.data(), size);
    return buffer;
}

int main(int argc, char** args) {
    string xclbinfile;
    //if (argc > 1)
    //    xclbinfile = args[1];
    //else {
    //    cerr << "Usage: " << args[0] << " <paramfile> <xclbinfile>" << endl;
    //    return 1;
    //}
    xclbinfile = args[1];

    // Initialize input data
    std::vector<float> hbm_data(BUFFER_SIZE);
    std::vector<float> output_data(BUFFER_SIZE);

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        hbm_data[i] = static_cast<float>(i);
    }

    try {
        // Get the Xilinx device and context
        auto device = xrt::device(0);

        // Load the XCLBIN file
        //auto xclbin = readBinaryFile(binaryFile);
        auto uuid = device.load_xclbin(xclbinfile);
        // Create kernel
        auto kernel = xrt::kernel(device, uuid, "streamhls");

        // Create buffers
        auto hbm_data_buf = xrt::bo(device, BUFFER_SIZE * sizeof(float), kernel.group_id(0));
        auto output_data_buf = xrt::bo(device, BUFFER_SIZE * sizeof(float), kernel.group_id(1));

        // Write input data to the buffer
        hbm_data_buf.write(hbm_data.data());
        hbm_data_buf.sync(XCL_BO_SYNC_BO_TO_DEVICE);



        // Set kernel arguments
        auto run = kernel(hbm_data_buf, output_data_buf);

        // Execute the kernel
        run.wait();

        // Read the output data
        output_data_buf.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        output_data_buf.read(output_data.data());

        // Verify the output
        bool match = true;
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (output_data[i] != hbm_data[i] * 2) {
                std::cout << "Error: Result mismatch at index " << i << ": expected " << hbm_data[i] * 2 << " but got " << output_data[i] << std::endl;
                match = false;
                break;
            }
        }

        if (match) {
            std::cout << "TEST PASSED!" << std::endl;
        } else {
            std::cout << "TEST FAILED!" << std::endl;
        }

    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
