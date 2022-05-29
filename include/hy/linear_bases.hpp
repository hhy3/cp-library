#pragma once

#include <vector>
#include <cstdint>

namespace hy {
namespace math {


template <typename T=uint64_t, int M=8*sizeof(T)>
struct linear_bases {
	constexpr static int num_bits = M;
  std::vector<T> B;
  int sz = 0;

	linear_bases(): B(M) {}

  bool insert(T x) {
    for (int i = num_bits - 1; i >= 0; --i) if (x >> i & 1) {
			if (B[i]) x ^= B[i];
			else {
				B[i] = x;
				sz++;
				return true;
			}
		}
		return false;
  }

	bool query(T x) {
		for (int i = num_bits - 1; i >= 0; --i) {
			if (x >> i & 1) x ^= B[i];
		}
		return x == 0;
	}

	T max() {
		T ans = 0;
		for (int i = num_bits - 1; i >= 0; --i) if (B[i]) {
			if ((ans >> i & 1) == 0) ans ^= B[i];
		}
		return ans;
	}
};


} // namespace math
} // namespace hy
