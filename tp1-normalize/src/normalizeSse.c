#include <xmmintrin.h>

void normalizeSse(float* v, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; i++)
        sum += v[i] * v[i];

    if (sum == 0) return;

    __m128 xm = _mm_set_ss(sum);
    __m128 est = _mm_rsqrt_ss(xm);
    float y = _mm_cvtss_f32(est);

    y = y * (1.5f - 0.5f * sum * y * y); // Refinamento NR

    for (int i = 0; i < len; i++)
        v[i] *= y;
}