#include <stdio.h>
#include <string.h>

typedef struct {
    char x;
    int intX;
} Test;

int main(int argc, char const *argv[]) {
    int RGB = 0xCCFFFF;

    unsigned char *RBGPtr = (unsigned char *)&RGB;

    for (int i = 0; i < sizeof(RGB); i++) {
        printf("ADDRESSES: %p | VALUE: %d | INDEX: %d\n", &RBGPtr[i], RBGPtr[i], i);
    }
}
