#!/bin/bash

BIN="./normalize"

VERSOES=("baseline" "quake" "sse")
N=(1000 10000)
D=(3 10)

mkdir -p results
RESULT="results/metrics.csv"
echo "version,N,D,wall,user,sys,memoryKB" > $RESULT

for n in "${N[@]}"; do
  for d in "${D[@]}"; do
    INPUT="tests/data_${n}x${d}.csv"
    for version in "${VERSOES[@]}"; do
      echo "Rodando: $version N=$n D=$d"
      $BIN "$INPUT" "$version" >> $RESULT
    done
  done
done
