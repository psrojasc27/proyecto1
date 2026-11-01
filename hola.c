#include "pgm.h"

int main(void) {
    int w, h;
    unsigned char *img = leer_pgm("prueba.pgm", &w, &h);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf("%3d ", img[y * w + x]);
        }
        printf("\n");
    }

    free(img);
    return 0;
}
