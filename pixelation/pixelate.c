#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void pixelate(unsigned char* imageData, int width, int height, int pixelSize) {
    // Ensure pixel size is at least 1
    if (pixelSize < 1) pixelSize = 1;
    
    for (int y = 0; y < height; y += pixelSize) {
        for (int x = 0; x < width; x += pixelSize) {
            // Calculate average color for this block
            int totalR = 0, totalG = 0, totalB = 0, totalA = 0;
            int count = 0;
            
            // Sample all pixels in this block
            for (int dy = 0; dy < pixelSize && (y + dy) < height; dy++) {
                for (int dx = 0; dx < pixelSize && (x + dx) < width; dx++) {
                    int index = ((y + dy) * width + (x + dx)) * 4;
                    totalR += imageData[index];
                    totalG += imageData[index + 1];
                    totalB += imageData[index + 2];
                    totalA += imageData[index + 3];
                    count++;
                }
            }
            
            // Calculate average
            unsigned char avgR = totalR / count;
            unsigned char avgG = totalG / count;
            unsigned char avgB = totalB / count;
            unsigned char avgA = totalA / count;
            
            // Apply average color to entire block
            for (int dy = 0; dy < pixelSize && (y + dy) < height; dy++) {
                for (int dx = 0; dx < pixelSize && (x + dx) < width; dx++) {
                    int index = ((y + dy) * width + (x + dx)) * 4;
                    imageData[index] = avgR;
                    imageData[index + 1] = avgG;
                    imageData[index + 2] = avgB;
                    imageData[index + 3] = avgA;
                }
            }
        }
    }
}
