/* v0.c - Version simple (sin vectorizar). */
#include "filtros.h"

void v0_filas(const unsigned char *in, unsigned char *out,
              int w, int h, const Filtro *f, int y0, int y1)
{
    const int n = f->n;
    const int r = n / 2;

    for (int y = y0; y < y1; y++) {
        for (int x = 0; x < w; x++) {
            float suma = 0.0f;
            for (int i = -r; i <= r; i++) {
                int fila = y + i;
                if (fila < 0) fila = 0;
                if (fila > h - 1) fila = h - 1;
                for (int j = -r; j <= r; j++) {
                    int col = x + j;
                    if (col < 0) col = 0;
                    if (col > w - 1) col = w - 1;
                    suma += f->K[(i + r) * n + (j + r)] * in[fila * w + col];
                }
            }
            if (suma < 0.0f) suma = -suma;
            if (suma > 255.0f) suma = 255.0f;
            out[y * w + x] = (unsigned char)(suma + 0.5f);
        }
    }
}
