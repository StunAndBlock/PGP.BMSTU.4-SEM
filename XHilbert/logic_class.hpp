#ifndef HILBERT_HPP
#define HILBERT_HPP
#include "./unlock.hpp"
#if defined(__GNUC__)
#define HB_ALWAYS_INLINE inline __attribute__((__always_inline__))
#elif defined(_MSC_VER)
#define HB_ALWAYS_INLINE __forceinline
#else
#define HB_ALWAYS_INLINE inline
#endif



template <typename ViTy = uint16_t,
          typename ITy = unsigned int,
          typename STy = unsigned int>
class Hilbert {
 public:
  static constexpr void IsToVs(STy N, STy K, ViTy vs[]) {
    IsToVsImpl(N, K, vs);
  }
  template <STy N> static constexpr void IsToVsN(STy K, ViTy vs[]) {
    IsToVsImpl(N, K, vs);
  }

 private:
  Hilbert() = delete;

  HB_ALWAYS_INLINE static constexpr void IsToVsImpl(STy N, STy K, ViTy vs[]) {
    for (STy i = 0; i < N; ++i) {
      vs[i] = 0;
    }
    if (N == 0 || K == 0) {
      return;
    }
    for (STy k = 0; k < K; ++k) {
      for (STy i = 1; i < (1U << N); ++i) {
        STy rotate = N - 1;
        if (i != (1U << N) - 1) {
          STy j = (i - 1) >> 1;
          for (STy bits = ~j & (j + 1); bits != 0; bits >>= 1) {
            --rotate;
          }
        }

        STy gray = ((i - 1) >> 1) ^ (i - 1);
        for (STy p = 0; p < 1U << N * k; ++p) {
          STy write_base = N * ((i << N * k) + p);
          STy read_base = N * p;
          bool reflect = !((i + 1) & 2);
          for (STy j = 0; j < N; ++j) {
            STy order = rotate + j >= N ? rotate + j - N : rotate + j;
            STy coord = (i + (1U << j)) & (1U << (j + 1));
            ViTy offset = coord ? (1U << k) : 0;
            ViTy temp = vs[read_base + order];
            temp = reflect ? ~temp & ((1U << k) - 1) : temp;
            vs[write_base + j] = temp + offset;
            reflect = gray & (1U << (j + 1));
          }
        }
      }

      for (STy p = 0; p < 1U << N * k; ++p) {
        ViTy temp = vs[N * (p + 1) - 1];
        for (STy i = N - 1; i > 0; --i) {
          vs[N * p + i] = vs[N * p + i - 1];
        }
        vs[N * p] = temp;
      }
    }
  }


};

int input();
float window_offset(int);
#endif  // HILBERT_HPP
