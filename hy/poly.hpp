#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <cassert>

namespace hy {

template <typename F>
struct Poly {
  int deg; 
  std::vector<F> coef;
  Poly(): deg(0), coef(1) {}
  Poly(int deg_): deg(deg_), coef(deg_+1) {}
  Poly(std::vector<F> coef_): deg((int)coef_.size()-1), coef(coef_) {}
  
  F& operator [] (int idx) {
    assert(idx >= 0 && idx <= deg);
    return coef[idx];
  }
  const F& operator [] (int idx) const {
    assert(idx >= 0 && idx <= deg);
    return coef[idx];
  }

  friend Poly operator + (const Poly& lhs, const Poly& rhs) {
    int deg = std::max(lhs.deg, rhs.deg);
    Poly p(deg);
    for (int i = 0; i <= deg; ++i) {
      if (i <= lhs.deg) p[i] += lhs[i];
      if (i <= rhs.deg) p[i] += rhs[i];
    }
    return p;
  }
  friend Poly operator - (const Poly& lhs, const Poly& rhs) {
    Poly tmp(rhs);
    for (auto& x : tmp.coef) x = -x;
    return lhs + tmp;
  }
  friend Poly operator * (const Poly& lhs, const Poly& rhs) {
    return Poly(FFT::convolution(lhs.coef, rhs.coef));    
  }
  struct FFT {
    using C = std::complex<double>;

    static void fft(std::vector<C>& a, bool invert) {
      int n = (int)a.size();
      if (n <= 1) return;
      std::vector<C> a0(n/2), a1(n/2);
      for (int i = 0; i < n/2; ++i) a0[i] = a[i*2], a1[i] = a[i*2+1];
      fft(a0, invert), fft(a1, invert);
      double angle = 2 * acos(-1) / n * (invert? -1 : 1);
      C w(1, 0), w1(cos(angle), sin(angle));
      for (int i = 0; i < n/2; ++i) {
        a[i] = a0[i] + w * a1[i], a[i+n/2] = a0[i] - w * a1[i];
        if (invert) a[i] /= 2, a[i+n/2] /= 2;
        w *= w1;
      }
    }

    static std::vector<F> convolution(const std::vector<F>& a, const std::vector<F>& b) {
      int n1 = (int)a.size(), n2 = (int)b.size(), n = 1;
      while (n < n1 + n2) n <<= 1;
      std::vector<C> fa(a.begin(), a.end()), fb(b.begin(), b.end());
      fa.resize(n), fb.resize(n);
      fft(fa, false), fft(fb, false);
      for (int i = 0; i < n; i++) fa[i] *= fb[i];
      fft(fa, true);
      std::vector<F> ans(n);
      for (int i = 0; i < n; i++) ans[i] = (F)round(fa[i].real());
      return ans;
    }
  };

  static Poly interpolate(std::vector<std::pair<F, F>> points) {
    // TODO 
  }

};

} //namespace hy
