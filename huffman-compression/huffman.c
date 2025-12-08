#include <emscripten.h>
#include <stdlib.h>
#include <string.h>

// Simple RLE (Run-Length Encoding) for demonstration
EMSCRIPTEN_KEEPALIVE
int compress(unsigned char* input, int inputSize, unsigned char* output, int maxOutputSize) {
    if (inputSize == 0) return 0;
    
    int outputPos = 0;
    
    // Store original size (4 bytes)
    output[outputPos++] = (inputSize >> 24) & 0xFF;
    output[outputPos++] = (inputSize >> 16) & 0xFF;
    output[outputPos++] = (inputSize >> 8) & 0xFF;
    output[outputPos++] = inputSize & 0xFF;
    
    int i = 0;
    while (i < inputSize) {
        unsigned char current = input[i];
        int count = 1;
        
        // Count consecutive identical bytes (max 255)
        while (i + count < inputSize && input[i + count] == current && count < 255) {
            count++;
        }
        
        // Store character and count
        output[outputPos++] = current;
        output[outputPos++] = (unsigned char)count;
        
        i += count;
    }
    
    return outputPos;
}

EMSCRIPTEN_KEEPALIVE
int decompress(unsigned char* input, int inputSize, unsigned char* output, int maxOutputSize) {
    if (inputSize < 4) return 0;
    
    // Read original size
    int originalSize = (input[0] << 24) | (input[1] << 16) | (input[2] << 8) | input[3];
    
    int inputPos = 4;
    int outputPos = 0;
    
    while (inputPos < inputSize && outputPos < originalSize) {
        unsigned char character = input[inputPos++];
        unsigned char count = input[inputPos++];
        
        // Write character 'count' times
        for (int i = 0; i < count; i++) {
            output[outputPos++] = character;
        }
    }
    
    return outputPos;
}

EMSCRIPTEN_KEEPALIVE
float calculateCompressionRatio(int originalSize, int compressedSize) {
    if (originalSize == 0) return 0.0f;
    return (float)compressedSize / (float)originalSize * 100.0f;
}
