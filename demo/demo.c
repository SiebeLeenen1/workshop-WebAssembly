#include <emscripten/emscripten.h>
#include <stdlib.h>
#include <math.h>

EMSCRIPTEN_KEEPALIVE
void edge_detection(unsigned char* imageData, int width, int height) {
    // Create a temporary buffer for output
    unsigned char* temp = (unsigned char*)malloc(width * height * 4);
    
    // Sobel operator kernels
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    // Process each pixel
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int gx = 0, gy = 0;
            
            // Apply Sobel operator
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int idx = ((y + ky) * width + (x + kx)) * 4;
                    int gray = (imageData[idx] + imageData[idx + 1] + imageData[idx + 2]) / 3;
                    
                    gx += gray * sobelX[ky + 1][kx + 1];
                    gy += gray * sobelY[ky + 1][kx + 1];
                }
            }
            
            // Calculate magnitude
            int magnitude = (int)sqrt(gx * gx + gy * gy);
            if (magnitude > 255) magnitude = 255;
            
            // Write to temp buffer
            int idx = (y * width + x) * 4;
            temp[idx] = temp[idx + 1] = temp[idx + 2] = magnitude;
            temp[idx + 3] = 255; // Alpha
        }
    }
    
    // Copy result back to original
    for (int i = 0; i < width * height * 4; i++) {
        imageData[i] = temp[i];
    }
    
    free(temp);
}
