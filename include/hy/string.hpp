#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>


namespace hy {
namespace string {


std::vector<int> prefix_function(const std::string& s) {
  int n = (int)s.size();
  std::vector<int> p(n+1);
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != s[j]) j = p[j];
    p[i + 1] = j += (s[i] == s[j]);
  }
  return p;
}


struct string_hash {
  int n;
  std::vector<uint64_t> h, power;
  string_hash(const std::string& s, uint64_t K): n((int)s.size()), h(n+1), power(n+1) {
    power[0] = 1;
    for (int i = 1; i <= n; ++i) h[i] = h[i-1] * K + s[i-1], power[i] = power[i-1] * K;
  }
  uint64_t get(int l, int r) { return h[r+1] - h[l] * power[r - l + 1]; }
  uint64_t get() { return get(0, n-1); }
};


std::vector<int> Z(const std::string& s) {
  int n = (int)s.size();
  std::vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = std::min(z[i-l], r - i + 1);
    while (i + z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}


void manacher(const std::string& s, std::vector<int>& d1, std::vector<int>& d2) {
  int n = (int)s.size();
  d1.assign(n, 0), d2.assign(n, 0);
  for (int i = 0, l = 0, r = -1; i < n; ++i) {
    if (i <= r) d1[i] = std::min(d1[l + r - i], r - i);
    while (i - d1[i] - 1 >= 0 && i + d1[i] + 1 < n && s[i - d1[i] - 1] == s[i + d1[i] + 1]) d1[i]++;
    if (i + d1[i] > r) l = i - d1[i], r = i + d1[i];
  }
  for (int i = 0, l = 0, r = -1; i < n; ++i) {
    if (i < r) d2[i] = std::min(d2[l + r - i - 1], r - i);
    while (i - d2[i] >= 0 && i + d2[i] + 1 < n && s[i - d2[i]] == s[i + d2[i] + 1]) d2[i]++;
    if (i + d2[i] > r) l = i - d2[i] + 1, r = i + d2[i];
  }
}


int minimum_rotation(const std::string& s) {
  int n = (int)s.size();
  int i = 0, j = 1, k = 0;
  while (i < n && j < n && k < n) {
    if (s[(i+k)%n] == s[(j+k)%n]) k++;
    else {
      if (s[(i+k)%n] > s[(j+k)%n]) i += k + 1;
      else j += k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  return std::min(i, j);
}


std::vector<int> SA(const std::string& s) {
  int n = s.size();
  std::vector<int> sa(n), rk(2*n);
  for (int i = 0; i < n; ++i) sa[i] = i, rk[i] = s[i];
  for (int w = 1; w < n; w *= 2) {
    std::sort(sa.begin(), sa.end(), [&] (int x, int y) {
      return rk[x] == rk[y]? rk[x+w] < rk[y+w] : rk[x] < rk[y]; }
    );
    auto oldrk = rk;
    rk[sa[0]] = 1;
    for (int p = 1, i = 1; i < n; ++i) {
      if (oldrk[sa[i]] == oldrk[sa[i-1]] && oldrk[sa[i]+w] == oldrk[sa[i-1]+w]) rk[sa[i]] = p;
      else rk[sa[i]] = ++p;
    }
  }
  return sa;
}


struct SAM {
  // TODO 
};


} // namespace string
} // namespace hy
