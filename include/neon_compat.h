#pragma once
#include <arm_neon.h>

// উদাহরণ: SSE _mm_add_ps → NEON vaddq_f32
inline float32x4_t add_ps(float32x4_t a, float32x4_t b) {
    return vaddq_f32(a, b);
}
