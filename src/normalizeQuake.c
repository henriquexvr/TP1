#include <stdint.h>

static float fastInvSqrt(float x) {
    union { float f; uint32_t i; } conv = { x };
    conv.i = 0x5f3759df - (conv.i >> 1);
    float y = conv.f;
    y = y * (1.5f - 0.5f * x * y * y);
    return y;
}

void normalizeQuake(float* v, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; i++)
        sum += v[i] * v[i];

    if (sum == 0) return;

    float inv = fastInvSqrt(sum);
    for (int i = 0; i < len; i++)
        v[i] *= inv;
}