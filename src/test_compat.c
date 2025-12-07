#include "stb_backend_full.c"
#include <stdio.h>

int main() {
    HamoopiImage* img = stb_create_image(640, 480, 4);
    
    printf("Testing field access compatibility:\n");
    printf("  img->width = %d\n", img->width);
    printf("  img->height = %d\n", img->height);
    printf("  img->w = %d\n", img->w);
    printf("  img->h = %d\n", img->h);
    
    if (img->w == 640 && img->h == 480) {
        printf("✅ SUCCESS: ->w and ->h access works!\n");
        stb_destroy_image(img);
        return 0;
    } else {
        printf("❌ FAIL: Field access not working\n");
        stb_destroy_image(img);
        return 1;
    }
}
