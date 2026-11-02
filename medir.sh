#!/bin/bash
# medir.sh - corre todas las versiones y arma la tabla de tiempos (resultados.md).
# Uso:  ./medir.sh            (usa img2048.pgm e img4096.pgm de esta carpeta)
set -e

N=$(nproc)
HILOS=$(printf "%s\n" 1 2 4 "$N" | sort -n | uniq | tr '\n' ' ')
CPU=$(lscpu | sed -n 's/^Model name:[[:space:]]*//p' | head -1)

declare -A ESPERADO=(
  [blur_img2048.pgm]=15228573027849069044  [gauss_img2048.pgm]=6704049370287127316
  [sobel_img2048.pgm]=13749065433343460504 [blur_img4096.pgm]=14133797607195559027
  [gauss_img4096.pgm]=11810212636788029950 [sobel_img4096.pgm]=15895088315003003173
)

SALIDA=resultados.md
{
  echo "# Resultados"
  echo
  echo "- Procesador: $CPU"
  echo "- Nucleos (nproc): $N"
  echo "- Cada tiempo es la mediana de 5 corridas, en segundos."
  echo "- Speedup = tiempo de V0 / tiempo de la version."
  echo
} > "$SALIDA"

for img in img2048.pgm img4096.pgm; do
  for filtro in blur gauss sobel; do
    echo "### $filtro - $img" >> "$SALIDA"
    echo >> "$SALIDA"
    echo "| Version | Hilos | Tiempo (s) | Speedup | Checksum |" >> "$SALIDA"
    echo "|---|---|---|---|---|" >> "$SALIDA"

    base=""
    for combo in "0 1" "1 1" $(for t in $HILOS; do echo "2:$t"; done) $(for t in $HILOS; do echo "3:$t"; done); do
      v=${combo%%[ :]*}; t=${combo##*[ :]}
      linea=$(./conv "$v" "$filtro" "$img" "$t")
      tiempo=$(sed 's/.*tiempo=\([0-9.]*\).*/\1/' <<< "$linea")
      cs=$(sed 's/.*checksum=\([0-9]*\).*/\1/' <<< "$linea")
      [ -z "$base" ] && base=$tiempo
      sp=$(awk -v b="$base" -v t="$tiempo" 'BEGIN{printf "%.2f", b/t}')
      ok="OK"; [ "$cs" = "${ESPERADO[${filtro}_${img}]}" ] || ok="FALLA"
      echo "| V$v | $t | $tiempo | ${sp}x | $ok |" >> "$SALIDA"
      echo "V$v hilos=$t $filtro $img  $tiempo s  (${sp}x)  $ok"
    done
    echo >> "$SALIDA"
  done
done
echo "Listo: $SALIDA"
