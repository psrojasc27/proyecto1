/* v1.c - Version pensada para que el compilador vectorice el bucle de columnas. */
#include "filtros.h"
#include <stdio.h>
#include <stdlib.h>

/* Copia de la imagen con r pixeles extra por lado repitiendo la orilla.
 * Tamano: (w + 2r) x (h + 2r). */
unsigned char *v1_rellenar(const unsigned char *in, int w, int h, int r)
{
    const int pw = w + 2 * r;
    const int ph = h + 2 * r;
    unsigned char *pad = (unsigned char *)malloc((size_t)pw * ph);
    if (!pad) { fprintf(stderr, "sin memoria\n"); exit(1); }

    for (int yy = 0; yy < ph; yy++) {
        int fila = yy - r;
        if (fila < 0) fila = 0;
        if (fila > h - 1) fila = h - 1;
        for (int xx = 0; xx < pw; xx++) {
            int col = xx - r;
            if (col < 0) col = 0;
            if (col > w - 1) col = w - 1;
            pad[(size_t)yy * pw + xx] = in[(size_t)fila * w + col];
        }
    }
    return pad;
}

/* n es constante en cada llamada: asi el compilador desenrolla los bucles
 * de la ventana y el bucle de x queda como el bucle interno (vectorizable). */
static inline __attribute__((always_inline)) void filas_n(
    const unsigned char *restrict pad, unsigned char *restrict out,
    int w, const float *restrict K, const int n, int y0, int y1)
{
    const int pw = w + (n - 1);          /* ancho de la imagen rellenada */

    for (int y = y0; y < y1; y++) {
        const unsigned char *restrict p = pad + (size_t)y * pw;
        unsigned char *restrict o = out + (size_t)y * w;

        for (int x = 0; x < w; x++) {
            float suma = 0.0f;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    suma += K[i * n + j] * p[i * pw + x + j];
                }
            }
            if (suma < 0.0f) suma = -suma;
            if (suma > 255.0f) suma = 255.0f;
            o[x] = (unsigned char)(suma + 0.5f);
        }
    }
}

void v1_filas(const unsigned char *pad, unsigned char *out,
              int w, int h, const Filtro *f, int y0, int y1)
{
    (void)h;
    if (f->n == 3) filas_n(pad, out, w, f->K, 3, y0, y1);
    else           filas_n(pad, out, w, f->K, 5, y0, y1);
}
