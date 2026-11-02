# Resultados

- Procesador: Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
- Nucleos (nproc): 8
- Cada tiempo es la mediana de 5 corridas, en segundos.
- Speedup = tiempo de V0 / tiempo de la version.

### blur - img2048.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 0.136585 | 1.00x | OK |
| V1 | 1 | 0.020397 | 6.70x | OK |
| V2 | 1 | 0.118330 | 1.15x | OK |
| V2 | 2 | 0.063243 | 2.16x | OK |
| V2 | 4 | 0.069797 | 1.96x | OK |
| V2 | 8 | 0.060450 | 2.26x | OK |
| V3 | 1 | 0.022370 | 6.11x | OK |
| V3 | 2 | 0.021998 | 6.21x | OK |
| V3 | 4 | 0.016412 | 8.32x | OK |
| V3 | 8 | 0.020433 | 6.68x | OK |

### gauss - img2048.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 0.326514 | 1.00x | OK |
| V1 | 1 | 0.039337 | 8.30x | OK |
| V2 | 1 | 0.370771 | 0.88x | OK |
| V2 | 2 | 0.160216 | 2.04x | OK |
| V2 | 4 | 0.119237 | 2.74x | OK |
| V2 | 8 | 0.093433 | 3.49x | OK |
| V3 | 1 | 0.049473 | 6.60x | OK |
| V3 | 2 | 0.037734 | 8.65x | OK |
| V3 | 4 | 0.036738 | 8.89x | OK |
| V3 | 8 | 0.032953 | 9.91x | OK |

### sobel - img2048.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 0.169432 | 1.00x | OK |
| V1 | 1 | 0.023124 | 7.33x | OK |
| V2 | 1 | 0.178872 | 0.95x | OK |
| V2 | 2 | 0.087930 | 1.93x | OK |
| V2 | 4 | 0.064323 | 2.63x | OK |
| V2 | 8 | 0.050742 | 3.34x | OK |
| V3 | 1 | 0.029968 | 5.65x | OK |
| V3 | 2 | 0.026324 | 6.44x | OK |
| V3 | 4 | 0.029453 | 5.75x | OK |
| V3 | 8 | 0.024318 | 6.97x | OK |

### blur - img4096.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 0.552880 | 1.00x | OK |
| V1 | 1 | 0.091779 | 6.02x | OK |
| V2 | 1 | 0.550209 | 1.00x | OK |
| V2 | 2 | 0.326579 | 1.69x | OK |
| V2 | 4 | 0.231140 | 2.39x | OK |
| V2 | 8 | 0.178312 | 3.10x | OK |
| V3 | 1 | 0.152078 | 3.64x | OK |
| V3 | 2 | 0.134308 | 4.12x | OK |
| V3 | 4 | 0.125485 | 4.41x | OK |
| V3 | 8 | 0.071040 | 7.78x | OK |

### gauss - img4096.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 1.236113 | 1.00x | OK |
| V1 | 1 | 0.193978 | 6.37x | OK |
| V2 | 1 | 1.336463 | 0.92x | OK |
| V2 | 2 | 0.697167 | 1.77x | OK |
| V2 | 4 | 0.450139 | 2.75x | OK |
| V2 | 8 | 0.353081 | 3.50x | OK |
| V3 | 1 | 0.172929 | 7.15x | OK |
| V3 | 2 | 0.123458 | 10.01x | OK |
| V3 | 4 | 0.097844 | 12.63x | OK |
| V3 | 8 | 0.092528 | 13.36x | OK |

### sobel - img4096.pgm

| Version | Hilos | Tiempo (s) | Speedup | Checksum |
|---|---|---|---|---|
| V0 | 1 | 0.707384 | 1.00x | OK |
| V1 | 1 | 0.090431 | 7.82x | OK |
| V2 | 1 | 0.703426 | 1.01x | OK |
| V2 | 2 | 0.398433 | 1.78x | OK |
| V2 | 4 | 0.256768 | 2.75x | OK |
| V2 | 8 | 0.182994 | 3.87x | OK |
| V3 | 1 | 0.118411 | 5.97x | OK |
| V3 | 2 | 0.070613 | 10.02x | OK |
| V3 | 4 | 0.068168 | 10.38x | OK |
| V3 | 8 | 0.063588 | 11.12x | OK |

