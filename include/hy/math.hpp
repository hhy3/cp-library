#pragma once

#include <vector>
#include <functional>
#include <cstdint>

namespace hy {
namespace math {

std::vector<int> prime_sieve(int n, std::vector<int> &sieve) {
  sieve.resize(n+1);
  std::vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (!sieve[i]) primes.push_back(i);
    for (auto p : primes) {
      if (i * p > n) break;
      sieve[i * p] = p;
      if (i % p == 0) break;
    }
  }
  return primes;
}


std::vector<int> multinv(int n, int p) {
  std::vector<int> inv(n + 1, 1);
  for (int i = 2; i <= n; ++i) inv[i] = long(p - p / i) * inv[p % i] % p;
  return inv;
}


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
  std::function<int64_t(int64_t, int64_t, int64_t)> lucas_ = [&] (int64_t m, int64_t n, int64_t p) {
    return m? lucas_(m / p, n / p, p) * comb(m % p, n % p, p) % p : 1;
  };
  return lucas_(m, n, p); 
}


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
    ans = ((ans + bs[i] * N / ns[i] * b) % N + N) % N;
  }
  return ans;
}


std::vector<int> iterate_subsets(int state) {
  std::vector<int> ans;
  for (int s = state; s; s = (s - 1) & state) ans.push_back(s);
  ans.push_back(0);
  return ans;
}


std::vector<int> GospersHack(int n, int k) {
  std::vector<int> ans;
  for (int i = (1 << k) - 1; i < 1 << n; ) {
    ans.push_back(i);
    i = (((i + (i & -i)) ^ i) >> __builtin_ctz(i & -i) + 2) | (i + (i & -i));
  }
  return ans;
}

std::vector<std::vector<int>> comb(int n, int64_t mod) {
  std::vector<std::vector<int>> C(n+1, std::vector<int>(n+1));
  C[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
  }
  return C;
}

std::vector<int> Catalan(int n, int64_t mod) {
  std::vector<int> cat(n+1);
  cat[0] = cat[1] = 1;
  for (int i = 2; i <= n; ++i) for (int j = 0; j < i; ++j) 
    cat[i] = (cat[i] + cat[i-j-1] * cat[j]) % mod;
  return cat;
}

int64_t InclusionExclusion(int n) {
  auto calc = [&] (int s) -> int64_t {
    // TODO
  };
  int64_t ans = 0;
  for (int s = 1; s < 1 << n; ++s) {
    if (__builtin_popcount(s) % 2) ans += calc(s);
    else ans -= calc(s);  
  }
}

}
}
