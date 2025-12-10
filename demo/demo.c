#include <emscripten/emscripten.h>
#include <stdlib.h>
#include <math.h>

EMSCRIPTEN_KEEPALIVE
void edge_detection(unsigned char *imageData, int width, int height)
{
    unsigned char *temp = (unsigned char)malloc(width * height * 4);

    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int sobelY[3][3] = {{-1, -2, 1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < height; y++)
    {
        for (int x = 1; x < width; x++)
        {
            int gx = 0, gy = 0;
            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int idx = ((y + ky) * width + (x + kx)) * 4;
                    int gray = (imageData[idx] + imageData[idx + 1] + imageData[idx + 2]) / 3;
                    gx += gray * sobelX[ky + 1][kx + 1];
                    gy += gray * sobelY[ky + 1][kx + 1];
                }
            }
            int magnitude = (int)sqrt(gx * gx + gy * gy);
            if (magnitude > 255)
                magnitude = 255;
            int idx = (y * width + x) * 4;
            temp[idx] = temp[idx + 1] = temp[idx + 2] = magnitude;
            temp[idx + 3] = 255;
        }
    }
    for (int i = 0; i < width * height * 4; i++)
    {
        imageData[i] = temp[i];
    }
    free(temp);
}