#pragma once

#include <vector>
#include <functional>
#include <cstdint>

namespace hy {
namespace math {

/**
 * @brief 求出1-n的关于质数p的乘法逆元
 *        
 *        简介: 
 *            https://oi-wiki.org/math/number-theory/inverse/
 *            
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3811       
 *        
 *        Time Complexity: O(n)
 * 
 */
std::vector<int> multinv(int n, int p) {
  std::vector<int> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = long(p - p / i) * inv[p % i] % p;
  }
  return inv;
}


/**
 * @brief Lucas定理
 *  
 *        简介:
 *            https://brilliant.org/wiki/lucas-theorem/
 * 
 *        模板题:
 *            https://www.luogu.com.cn/problem/P3807
 * 
 * @param m 
 * @param n 
 * @param p 
 * @return int64_t 
 */
int64_t lucas(int64_t m, int64_t n, int64_t p) {
  
  std::vector<int64_t> fac(p), ifac(p), inv(p);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < p; ++i) {
    inv[i] = (i == 1? : (p - p / i) * inv[p % i] % p);
    fac[i] = fac[i-1] * i % p;
    ifac[i] = ifac[i-1] * inv[i] % p;
  }

  auto comb = [&] (auto m, auto n, auto p) {
    return m >= n? fac[m] * ifac[n] % p * ifac[m-n] % p : 0;
  };

  std::function<int64_t(int64_t, int64_t, int64_t)> 
  lucas_ = [&] (int64_t m, int64_t n, int64_t p) {
    return m? lucas_(m / p, n / p, p) * comb(m % p, n % p, p) % p : 1;
  };
  return lucas_(m, n, p); 
}


/**
 * @brief 中国剩余定理 (Chinese Reminder Theorem)
 *        Z_{n} = Z_{n_{1}} \times Z_{n_{2}} \times \cdots \times Z_{n_{k}}
 *        
 *        简介: 
 *            https://crypto.stanford.edu/pbc/notes/numbertheory/crt.html 
 *        
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P1495
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


vector<int> iterate_subsets(int state) {
  vector<int> ans;
  for (int s = state; s; s = (s - 1) & state) {
    ans.push_back(s);
  }
  ans.push_back(0);
  return ans;
}

vector<int> GospersHack(int n, int k) {
  vector<int> ans;
  for (int i = (1 << k) - 1; i < 1 << n; ) {
    ans.push_back(i);
    int lb = cur & -cur;
    int r = cur + lb;
    cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
  }
  return ans;
}

}
}
