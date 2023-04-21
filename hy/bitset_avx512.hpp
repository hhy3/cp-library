#include "hy/bitset.hpp"
#include <cstdlib>
#include <cstring>
#include <immintrin.h>

namespace hy {

struct BitsetAVX512 {
  constexpr static int block_size = 512;
  int64_t nblock;
  int64_t nbytes;
  __m512i *data;
  explicit BitsetAVX512(int64_t n)
      : nblock((n + 511) / 512), nbytes(nblock * 64),
        data((__m512i *)aligned_alloc(4096, (nbytes + 4095) / 4096 * 4096)) {
    memset(data, 0, nbytes);
  }

  void flip(int64_t u) {
    uint64_t *p = (uint64_t *)data;
    p[u / 64] ^= (1LL << (u & 63));
  }

  bool get(int64_t u) {
    uint64_t *p = (uint64_t *)data;
    return p[u / 64] >> (u & 63) & 1;
  }

  __attribute__((target("avx512vpopcntdq"))) void flip(int64_t l, int64_t r) {
    int64_t bl = l / block_size, br = r / block_size;
    if (bl == br) {
        for (int i = l; i <= r; ++i) {
            flip(i);
        }
        return;
    }
    for (int i = l; i < (bl + 1) * block_size; ++i) {
      flip(i);
    }
    for (int i = br * block_size; i <= r; ++i) {
      flip(i);
    }
    for (int blk = bl + 1; blk < br; ++blk) {
      auto xx = _mm512_loadu_si512((__m512i *)(data + blk));
      xx = _mm512_xor_si512(xx, _mm512_set1_epi32(0xffffffff));
      _mm512_storeu_si512(data + blk, xx);
    }
  }

  __attribute__((target("avx512vpopcntdq"))) int64_t count(int64_t l,
                                                           int64_t r) {
    int64_t cnt = 0;
    int64_t bl = l / block_size, br = r / block_size;
    if (bl == br) {
        for (int i = l; i <= r; ++i) {
            cnt += get(i);
        }
        return cnt;
    }
    for (int i = l; i < (bl + 1) * block_size; ++i) {
      cnt += get(i);
    }
    for (int i = br * block_size; i <= r; ++i) {
      cnt += get(i);
    }
    __m512i cnt_512 = _mm512_setzero_si512();
    for (int blk = bl + 1; blk < br; ++blk) {
      auto xx = _mm512_loadu_si512((__m512i *)(data + blk));
      cnt_512 = _mm512_add_ps(cnt_512, _mm512_popcnt_epi32(xx));
    }
    return cnt + _mm512_reduce_add_epi32(cnt_512);
  }
};

} // namespace hy