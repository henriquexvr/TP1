#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

float* readCsv(const char* filename, int* numRows, int* numCols);
void normalizeBaseline(float* v, int len);
void normalizeQuake(float* v, int len);
void normalizeSse(float* v, int len);

double getTimeInSeconds(struct timeval* tv) {
    return (double)tv->tv_sec + (double)tv->tv_usec / 1000000.0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Uso: %s <arquivo.csv> <versao>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    char* version = argv[2];

    int rows = 0, cols = 0;
    float* data = readCsv(filename, &rows, &cols);
    if (!data) return 1;

    struct rusage start, end;
    struct timeval tStart, tEnd;

    gettimeofday(&tStart, NULL);
    getrusage(RUSAGE_SELF, &start);

    void (*normalizeFunc)(float*, int) = NULL;
    if (strcmp(version, "baseline") == 0)
        normalizeFunc = normalizeBaseline;
    else if (strcmp(version, "quake") == 0)
        normalizeFunc = normalizeQuake;
    else if (strcmp(version, "sse") == 0)
        normalizeFunc = normalizeSse;
    else {
        printf("Versão inválida!\n");
        free(data);
        return 1;
    }

    for (int r = 0; r < rows; r++) {
        float* v = &data[r * cols];
        normalizeFunc(v, cols);
    }

    gettimeofday(&tEnd, NULL);
    getrusage(RUSAGE_SELF, &end);

    double wall = getTimeInSeconds(&tEnd) - getTimeInSeconds(&tStart);
    double user = (end.ru_utime.tv_sec - start.ru_utime.tv_sec)
                  + (end.ru_utime.tv_usec - start.ru_utime.tv_usec) / 1000000.0;
    double sys = (end.ru_stime.tv_sec - start.ru_stime.tv_sec)
                 + (end.ru_stime.tv_usec - start.ru_stime.tv_usec) / 1000000.0;
    long memory = end.ru_maxrss; // KB

    printf("%s,%d,%d,%.6f,%.6f,%.6f,%ld\n",
           version, rows, cols, wall, user, sys, memory);

    free(data);
    return 0;
}
