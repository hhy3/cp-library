#pragma once

#include <vector>
#include <functional>

#include <cstdint>
#include <cassert>

namespace hy {
namespace math {

/**
 * @brief 中国剩余定理 (Chinese Reminder Theorem)
 *        nZ_{n} = Z_{n_{1}} \times Z_{n_{2}} \times \cdots \times Z_{n_{k}}
 *        简介: https://crypto.stanford.edu/pbc/notes/numbertheory/crt.html 
 *        模板题: https://www.luogu.com.cn/problem/P1495
 * 
 * @tparam T 
 * @param bs 
 * @param ns 
 * @return T 
 */
template<typename T>
T CRT(const std::vector<T> &bs, const std::vector<T> &ns) {

  std::function<T(T, T, T, T)> extgcd = [&] (T a, T b, T& x, T& y) {
    if (b == 0) {
      x = 1, y = 0;
      return a;
    }
    T d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
  };

  assert(bs.size() == ns.size());
  int n = bs.size();
  T N = 1;
  for (const auto x : ns) N *= x;
  T ans = 0;
  for (int i = 0; i < n; ++i) {
    T b, y;
    extgcd(N / ns[i], ns[i], b, y);
    ans += bs[i] * N / ns[i] * b;
    ans = (ans % N + N) % N;
  }
  return ans;
}


} // namespace math
} // namespace hy