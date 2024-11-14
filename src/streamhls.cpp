#include <hls_stream.h>
#include <ap_int.h>
#include <iostream>
#include <cmath>

#define VECTOR_SIZE 16

struct float16 {
    float data[VECTOR_SIZE];
};

void fetch_from_hbm(hls::stream<float16> &input_stream, float *hbm_data, int num_vectors) {
    for (int i = 0; i < num_vectors; i+=VECTOR_SIZE) {
#pragma HLS PIPELINE II=1
        float16 temp;
        for (int j = 0; j < VECTOR_SIZE; ++j) {
#pragma HLS UNROLL factor=16
            temp.data[j] = hbm_data[i + j];
        }
        input_stream.write(temp);
    }
}

void process_kernel(hls::stream<float16> &input_stream, hls::stream<float16> &output_stream, int num_vectors) {
    for (int i = 0; i < num_vectors; i+=VECTOR_SIZE) {
        #pragma HLS PIPELINE II=1

        float16 in_data = input_stream.read();
        float16 out_data;

        for (int j = 0; j < VECTOR_SIZE; ++j) {
            //#pragma HLS UNROLL factor=16
            out_data.data[j] = in_data.data[j] * 2; // Example processing: multiply by 2
        }

        output_stream.write(out_data);
    }
}

void write_to_output(hls::stream<float16> &output_stream, float *output_data, int num_vectors) {
    for (int i = 0; i < num_vectors; i+=VECTOR_SIZE) {
#pragma HLS PIPELINE II=1
        float16 out_data = output_stream.read();
        for (int j = 0; j < VECTOR_SIZE; ++j) {
            #pragma HLS UNROLL factor=16
            output_data[i + j] = out_data.data[j];
        }
    }
}

void streamhls(float *hbm_data, float *output_data) {
    #pragma HLS INTERFACE m_axi port=hbm_data offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=output_data offset=slave bundle=gmem

    hls::stream<float16> input_stream;
    hls::stream<float16> output_stream;

    #pragma HLS STREAM variable=input_stream depth=16
    #pragma HLS STREAM variable=output_stream depth=16

    int num_vectors = 256;

    #pragma HLS DATAFLOW
    fetch_from_hbm(input_stream, hbm_data, num_vectors);
    process_kernel(input_stream, output_stream, num_vectors);
    write_to_output(output_stream, output_data, num_vectors);
}

// Testbench code
int main() {
    float hbm_data[256];
    float output_data[256];

    // Initialize input data
    for (int i = 0; i < 256; ++i) {
        hbm_data[i] = static_cast<float>(i);
    }

    // Call the kernel
    streamhls(hbm_data, output_data);

    // Verify the output data
    bool pass = true;
    for (int i = 0; i < 256; ++i) {
        float expected = hbm_data[i] * 2;  // As per the processing kernel logic
        if (std::fabs(output_data[i] - expected) > 1e-6) {
            std::cout << "Mismatch at index " << i << ": expected " << expected << ", got " << output_data[i] << std::endl;
            pass = false;
        }
    }

    if (pass) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }

    return 0;
}
