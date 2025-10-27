#include <math.h>

void normalizeBaseline(float* v, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; i++)
        sum += v[i] * v[i];

    if (sum == 0) return;

    float norm = sqrtf(sum);
    for (int i = 0; i < len; i++)
        v[i] /= norm;
}