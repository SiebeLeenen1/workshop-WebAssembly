#include <emscripten/emscripten.h>
#include <string.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
char* reverse(const char* str) {
    int len = strlen(str);

    char* result = (char*)malloc(len + 1);

    for(int i = 0; i < len; i++){
        result[i] = str[len - 1 -i];

    }
    result[len] = '\0';
    return result;
}
