#pragma once

#include <cmath>
#include <cstdint>
#include <functional>
#include <map>
#include <type_traits>
#include <vector>

namespace hy {

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> binary_gcd(T x, T y) {
  if (x == 0)
    return y;
  if (y == 0)
    return x;
  int X = __builtin_ctz(x), Y = __builtin_ctz(y);
  int shift = std::min(X, Y);
  y >> Y;
  for (; x;) {
    x >>= X;
    int d = y - x;
    X = __builtin_ctz(d);
    y = std::min(x, y);
    x = std::abs(d);
  }
  return y << shift;
}

inline std::vector<int> prime_sieve(int n, std::vector<int> &sieve) {
  sieve.resize(n + 1);
  std::vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (!sieve[i])
      primes.push_back(i);
    for (auto p : primes) {
      if (i * p > n)
        break;
      sieve[i * p] = p;
      if (i % p == 0)
        break;
    }
  }
  return primes;
}

template <typename T = int64_t> std::vector<int> multinv(int n, T p) {
  std::vector<T> inv(n + 1, 1);
  for (int64_t i = 2; i <= n; ++i) {
    inv[i] = (p - p / i) * inv[p % i] % p;
  }
  return inv;
}

template <typename T = int64_t> T lucas(T m, T n, T p) {
  std::vector<T> fac(p), ifac(p), inv(p);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < p; ++i) {
    inv[i] = (i == 1 ?: (p - p / i) * inv[p % i] % p);
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
  auto comb = [&](auto m, auto n, auto p) {
    return m >= n ? fac[m] * ifac[n] % p * ifac[m - n] % p : 0;
  };
  std::function<T(T, T, T)> lucas_ = [&](T m, T n, T p) {
    return m ? lucas_(m / p, n / p, p) * comb(m % p, n % p, p) % p : 1;
  };
  return lucas_(m, n, p);
}

template <typename T>
T CRT(const std::vector<T> &bs, const std::vector<T> &ns) {
  std::function<T(T, T, T, T)> extgcd = [&](T a, T b, T &x, T &y) {
    if (b == 0) {
      return x = 1, y = 0, a;
    }
    T d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
  };
  assert(bs.size() == ns.size());
  int n = bs.size();
  T N = 1;
  for (const auto x : ns) {
    N *= x;
  }
  T ans = 0;
  for (int i = 0; i < n; ++i) {
    T b, y;
    extgcd(N / ns[i], ns[i], b, y);
    ans = ((ans + bs[i] * N / ns[i] * b) % N + N) % N;
  }
  return ans;
}

template <typename Func> void iterate_subsets(int state, Func &f) {
  for (int s = state; s; s = (s - 1) & state) {
    f(s);
  }
}

template <typename Func> std::vector<int> GospersHack(int n, int k, Func &f) {
  for (int i = (1 << k) - 1; i < 1 << n;) {
    f(i);
    i = (((i + (i & -i)) ^ i) >> (__builtin_ctz(i & -i) + 2)) | (i + (i & -i));
  }
}

template <typename T = int64_t> std::vector<std::vector<T>> comb(int n, T mod) {
  std::vector<std::vector<T>> C(n + 1, std::vector<T>(n + 1));
  C[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  }
  return C;
}

template <typename T> std::vector<T> catalan(int n, T mod) {
  std::vector<T> cat(n + 1);
  cat[0] = cat[1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      cat[i] = (cat[i] + cat[i - j - 1] * cat[j]) % mod;
    }
  }
  return cat;
}

template <typename Func> int64_t InclusionExclusion(int n, Func f) {
  int64_t ans = 0;
  for (int s = 1; s < 1 << n; ++s) {
    if (__builtin_popcount(s) % 2) {
      ans += f(s);
    } else {
      ans -= f(s);
    }
  }
  return ans;
}

template <typename T> T extgcd(T a, T b, T &x, T &y) {
  if (!b) {
    return x = 1, y = 0, a;
  }
  T d = extgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

// Baby-step giant-step algorithm.
// It is used to solve discrete logarithm problem.
// i.e. find x s.t. a^x = b (mod p)
template <typename T> T BSGS(T a, T b, T mod) {
  std::map<T, T> mp;
  T cur = 1, t = std::sqrt(mod) + 1;
  for (int B = 1; B <= t; ++B) {
    cur = cur * a % mod;
    mp[b * cur % mod] = B;
  }
  T now = cur;
  for (int A = 1; A <= t; ++A) {
    if (mp.count(now)) {
      return A * t - mp[now];
    }
    now = now * cur % mod;
  }
  return -1;
}

template <typename Func> std::pair<int, int> floydCycleFinding(int x0, Func f) {
  // finding k * mu
  int slow = f(x0), fast = f(f(x0));
  while (slow != fast) {
    slow = f(slow);
    fast = f(f(fast));
  }
  // finding mu
  fast = x0;
  while (slow != fast) {
    slow = f(slow);
    fast = f(fast);
  }
  int mu = slow;
  // finding lambda
  int lambda = 1;
  fast = f(slow);
  while (slow != fast) {
    fast = f(fast);
    lambda++;
  }
  return std::make_pair(mu, lambda);
}

} // namespace hy
