#pragma once

#include <vector>
#include <complex>
#include <algorithm>


namespace hy {
namespace math {

using C = std::complex<double>;

void fft(std::vector<C>& a, bool invert) {
  int n = a.size();
  if (n <= 1) return;
  std::vector<C> a0(n/2), a1(n/2);
  for (int i = 0; i < n/2; ++i) {
    a0[i] = a[i*2];
    a1[i] = a[i*2+1];
  }
  fft(a0, invert);
  fft(a1, invert);
  double angle = 2 * acos(-1) / n * (invert? -1 : 1);
  C w(1, 0), w1(cos(angle), sin(angle));
  for (int i = 0; i < n/2; ++i) {
    a[i] = a0[i] + w * a1[i];
    a[i+n/2] = a0[i] - w * a1[i];
    if (invert) {
      a[i] /= 2;
      a[i+n/2] /= 2;
    }
    w *= w1;
  }
}

template <typename T=int64_t>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
  int n1 = a.size(), n2 = b.size(), n = 1;
  while (n < n1 + n2) n <<= 1;
  std::vector<C> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++) fa[i] *= fb[i];
  fft(fa, true);

  std::vector<T> ans(n);
  for (int i = 0; i < n; i++) ans[i] = round(fa[i].real());
  return ans;
}


} // namespace math
} // namespace hy

