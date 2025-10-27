#ifdef __ARM_NEON__
#include <arm_neon.h>
#else
#error "ARM NEON not available. Please compile with -march=armv8-a+simd"
#endif

void normalizeSseArm(float* v, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; i++)
        sum += v[i] * v[i];

    if (sum == 0) return;

    // Calculate inverse square root using NEON
    // vrsqrte_f32 computes reciprocal square root (1/sqrt(x))
    float32x2_t xm = vset_lane_f32(sum, vdup_n_f32(0), 0);
    float32x2_t est = vrsqrte_f32(xm);
    float y = vget_lane_f32(est, 0);

    // Newton-Raphson refinement for better accuracy
    // y = y * (1.5 - 0.5 * x * y * y)
    y = y * (1.5f - 0.5f * sum * y * y);

    // Multiply all elements by the inverse square root
    for (int i = 0; i < len; i++)
        v[i] *= y;
}
