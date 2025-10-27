#!/bin/bash

BIN="./normalize"

VERSOES=("baseline" "quake" "sse")
D=(3 10 100)

mkdir -p results
RESULT="results/metrics.csv"
echo "version,N,D,wall,user,sys,memoryKB" > $RESULT

for d in "${D[@]}"; do
    INPUT="tests/data_1000x${d}.csv"
    for version in "${VERSOES[@]}"; do
        echo "Rodando: $version N=$n D=$d"
        $BIN "$INPUT" "$version" >> $RESULT
    done
done
