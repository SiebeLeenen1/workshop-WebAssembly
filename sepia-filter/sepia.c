#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void sepia_filter(unsigned char* imageData, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 4;
            
            unsigned char r = imageData[index];
            unsigned char g = imageData[index + 1];
            unsigned char b = imageData[index + 2];
            
            // Sepia tone formula
            int tr = (int)(0.393 * r + 0.769 * g + 0.189 * b);
            int tg = (int)(0.349 * r + 0.686 * g + 0.168 * b);
            int tb = (int)(0.272 * r + 0.534 * g + 0.131 * b);
            
            // Clamp values to 0-255
            imageData[index] = tr > 255 ? 255 : tr;
            imageData[index + 1] = tg > 255 ? 255 : tg;
            imageData[index + 2] = tb > 255 ? 255 : tb;
            // Alpha channel stays the same (index + 3)
        }
    }
}
