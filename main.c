/* main.c - Proyecto I: convolucion con vectorizacion e hilos.
 *
 * Uso:  ./conv <version 0..3> <blur|gauss|sobel> <imagen.pgm> [hilos] [salida.pgm]
 *
 *   V0: simple              V1: vectorizada
 *   V2: V0 con hilos        V3: V1 con hilos
 */
#include "pgm.h"
#include <pthread.h>
#include "filtros.h"

#define REPETICIONES 5

static const float K_BLUR[9] = {
    1/9.f, 1/9.f, 1/9.f,
    1/9.f, 1/9.f, 1/9.f,
    1/9.f, 1/9.f, 1/9.f
};

static const float K_GAUSS[25] = {
    1/273.f,  4/273.f,  7/273.f,  4/273.f, 1/273.f,
    4/273.f, 16/273.f, 26/273.f, 16/273.f, 4/273.f,
    7/273.f, 26/273.f, 41/273.f, 26/273.f, 7/273.f,
    4/273.f, 16/273.f, 26/273.f, 16/273.f, 4/273.f,
    1/273.f,  4/273.f,  7/273.f,  4/273.f, 1/273.f
};

static const float K_SOBEL[9] = {
    -1.f, 0.f, 1.f,
    -2.f, 0.f, 2.f,
    -1.f, 0.f, 1.f
};

static const Filtro FILTROS[3] = {
    { "blur",  3, K_BLUR  },
    { "gauss", 5, K_GAUSS },
    { "sobel", 3, K_SOBEL },
};

/* ---- hilos ---- */

typedef struct {
    int version;                 /* 0 o 1: que kernel usar */
    const unsigned char *entrada; /* imagen original (V0) o rellenada (V1) */
    unsigned char *salida;
    int w, h;
    const Filtro *f;
    int y0, y1;                  /* filas que le tocan a este hilo */
} Tarea;

static void *trabajo(void *arg)
{
    Tarea *t = (Tarea *)arg;
    if (t->version == 0) v0_filas(t->entrada, t->salida, t->w, t->h, t->f, t->y0, t->y1);
    else                 v1_filas(t->entrada, t->salida, t->w, t->h, t->f, t->y0, t->y1);
    return NULL;
}

/* Reparte las h filas en bloques contiguos entre nh hilos. */
static void correr_con_hilos(int version, const unsigned char *entrada,
                             unsigned char *salida, int w, int h,
                             const Filtro *f, int nh)
{
    pthread_t *ids = (pthread_t *)malloc(sizeof(pthread_t) * (size_t)nh);
    Tarea *tareas = (Tarea *)malloc(sizeof(Tarea) * (size_t)nh);
    if (!ids || !tareas) { fprintf(stderr, "sin memoria\n"); exit(1); }

    for (int t = 0; t < nh; t++) {
        tareas[t].version = version;
        tareas[t].entrada = entrada;
        tareas[t].salida  = salida;
        tareas[t].w = w;
        tareas[t].h = h;
        tareas[t].f = f;
        tareas[t].y0 = (int)((long long)h * t / nh);
        tareas[t].y1 = (int)((long long)h * (t + 1) / nh);
        if (pthread_create(&ids[t], NULL, trabajo, &tareas[t]) != 0) {
            fprintf(stderr, "no se pudo crear el hilo %d\n", t);
            exit(1);
        }
    }
    for (int t = 0; t < nh; t++) pthread_join(ids[t], NULL);

    free(ids);
    free(tareas);
}

/* Aplica el filtro completo con la version pedida. */
static void aplicar(int version, const unsigned char *in, unsigned char *out,
                    int w, int h, const Filtro *f, int hilos)
{
    if (version == 0) {
        v0_filas(in, out, w, h, f, 0, h);
    } else if (version == 1) {
        unsigned char *pad = v1_rellenar(in, w, h, f->n / 2);
        v1_filas(pad, out, w, h, f, 0, h);
        free(pad);
    } else if (version == 2) {
        correr_con_hilos(0, in, out, w, h, f, hilos);
    } else {
        unsigned char *pad = v1_rellenar(in, w, h, f->n / 2);
        correr_con_hilos(1, pad, out, w, h, f, hilos);
        free(pad);
    }
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "uso: %s <version 0..3> <blur|gauss|sobel> <imagen.pgm> [hilos] [salida.pgm]\n", argv[0]);
        return 1;
    }

    int version = atoi(argv[1]);
    if (version < 0 || version > 3) { fprintf(stderr, "version invalida\n"); return 1; }

    const Filtro *f = NULL;
    for (int k = 0; k < 3; k++)
        if (strcmp(argv[2], FILTROS[k].nombre) == 0) f = &FILTROS[k];
    if (!f) { fprintf(stderr, "filtro invalido: %s\n", argv[2]); return 1; }

    const char *ruta = argv[3];
    int hilos = (argc > 4) ? atoi(argv[4]) : 1;
    if (hilos < 1) hilos = 1;
    const char *ruta_salida = (argc > 5) ? argv[5] : NULL;

    int w, h;
    unsigned char *in = leer_pgm(ruta, &w, &h);
    unsigned char *out = (unsigned char *)calloc((size_t)w * h, 1);
    if (!out) { fprintf(stderr, "sin memoria\n"); return 1; }

    double tiempos[REPETICIONES];
    for (int rep = 0; rep < REPETICIONES; rep++) {
        double t0 = ahora();
        aplicar(version, in, out, w, h, f, hilos);
        tiempos[rep] = ahora() - t0;
    }
    double med = mediana(tiempos, REPETICIONES);

    if (w * h <= 64) {   /* imagen pequena: mostrar la matriz */
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) printf("%3d ", out[y * w + x]);
            printf("\n");
        }
    }
    if (ruta_salida) escribir_pgm(ruta_salida, out, w, h);

    int hilos_usados = (version >= 2) ? hilos : 1;
    printf("v=%d filtro=%s img=%s hilos=%d tiempo=%.6f checksum=%" PRIu64 "\n",
           version, f->nombre, ruta, hilos_usados, med, checksum(out, (size_t)w * h));

    free(in);
    free(out);
    return 0;
}
