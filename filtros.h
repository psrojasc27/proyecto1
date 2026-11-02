/* filtros.h - definiciones compartidas entre las versiones */
#ifndef FILTROS_H
#define FILTROS_H

/* Un filtro: su nombre, su tamano n (3 o 5) y los n*n coeficientes por filas. */
typedef struct {
    const char *nombre;
    int n;
    const float *K;
} Filtro;

/* V0: version simple. Calcula las filas [y0, y1) de la salida leyendo la
 * imagen original y corrigiendo los indices que se salen (orillas). */
void v0_filas(const unsigned char *in, unsigned char *out,
              int w, int h, const Filtro *f, int y0, int y1);

/* V1: version pensada para vectorizar.
 * v1_rellenar crea una copia de la imagen con r = n/2 pixeles extra por lado,
 * repitiendo la orilla. v1_filas calcula las filas [y0, y1) sin ningun if
 * de orillas, porque el relleno ya los resolvio. */
unsigned char *v1_rellenar(const unsigned char *in, int w, int h, int r);
void v1_filas(const unsigned char *pad, unsigned char *out,
              int w, int h, const Filtro *f, int y0, int y1);

#endif
