#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float* readCsv(const char* filename, int* numRows, int* numCols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo: %s\n", filename);
        return NULL;
    }

    char line[2048];
    *numRows = 0;
    *numCols = 0;

    // Primeira passagem: contar linhas e colunas
    while (fgets(line, sizeof(line), file)) {
        if (*numRows == 0) {
            char* tmp = strdup(line);
            char* token = strtok(tmp, ",");
            while (token) {
                (*numCols)++;
                token = strtok(NULL, ",");
            }
            free(tmp);
        }
        (*numRows)++;
    }

    rewind(file);

    float* data = malloc((*numRows) * (*numCols) * sizeof(float));
    if (!data) {
        fclose(file);
        return NULL;
    }

    int r = 0;
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        int c = 0;
        while (token) {
            data[r * (*numCols) + c] = strtof(token, NULL);
            token = strtok(NULL, ",");
            c++;
        }
        r++;
    }

    fclose(file);
    return data;
}