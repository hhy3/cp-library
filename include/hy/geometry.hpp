#pragma once

#include <vector>
#include <complex>

namespace hy {
namespace geo {


// 距离: abs(p)
// 角度: arg(p)
// 旋转: p * polar(1.0L, x)
// 缩放: p * polar(k, 0.0L)
#define X real()
#define Y imag()

template <typename T> 
using P = std::complex<T>;

template <typename T>
bool lt(const P<T>& p1, const P<T>& p2) { return (p1.X < p2.X) || (p1.X == p2.X && p1.Y < p2.Y); }
template <typename T>
P<T> max(const P<T>& p1, const P<T>& p2) { return lt(p1, p2)? p2 : p1; }
template <typename T>
P<T> min(const P<T>& p1, const P<T>& p2) { return lt(p1, p2)? p1 : p2; }
// 二维叉积
template <typename T=int64_t>
T crossp(const P<T>& x, const P<T>& y) { return (conj(x) * y).Y; }

template <typename T=int64_t>
struct segment {
  P<T> s, e;
  segment(P<T> s_, P<T> e_): s(s_), e(e_) {}

  int side(const P<T>& p) { /* <0: left, =0: touch, >0: right */ return crossp(e-s, e-p); }

  segment sort() { if (s.X > e.X || s.X == e.X && s.Y > e.Y) swap(s, e); return *this; }

  bool intersect(const P<T>& p) {
    return crossp(e - s, p - s) == 0 && (min(s.X, e.X) <= p.X && max(s.X, e.X) >= p.X) && (min(s.Y, e.Y) <= p.Y && max(s.Y, e.Y) >= p.Y);
  }

  int intersect(const segment& rhs) { // 0: none, 1: unique, 2: infinite
    auto [s1, e1] = *this;
    auto [s2, e2] = rhs;
    if (!side(s2) && !side(e2)) {
      if (lt(e1, s1)) swap(s1, e1);
      if (lt(e2, s2)) swap(s2, e2);
      if (lt(max(s1, s2), min(e1, e2))) return 2;
      else if (max(s1, s2) == min(e1, e2)) return 1;
      else return 0;
    } else if (s1 == s2 || s1 == e2 || e1 == s2 || e1 == e2) {
      return 1;
    } else {
      T cp1 = crossp(e1-s1, s2-s1), cp2 = crossp(e1-s1, e2-s1), 
        cp3 = crossp(e2-s2, s1-s2), cp4 = crossp(e2-s2, e1-s2);
      if (((cp1 <= 0 && cp2 >= 0) || (cp1 >= 0 && cp2 <= 0)) &&
          ((cp3 <= 0 && cp4 >= 0) || (cp3 >= 0 && cp4 <= 0))) return 1;
      else return 0;
    }
  }
};


template <typename T>
struct polygon {
  std::vector<P<T>> points;
  polygon() = default;

  P<T> operator [] (int idx) { return points[idx]; }
  int size() { return (int)points.size(); }
  void push_back(const P<T>& p) { points.push_back(p); }
  P<T> pop_back() {
    auto p = points.back();
    points.pop_back();
    return p;
  }

  T area() { // return 2a where a = area of this polygon
    T ans = 0;
    for (int i = 0; i < size(); ++i) ans += crossp(points[i], points[(i+1)%size()]);
    return abs(ans);
  }

  T perimeter() {
    T ans = 0;
    for (int i = 0; i < size(); ++i) {
      ans += abs(points[i] - points[(i+1)%size()]);
    }
    return ans;
  }

  int where(const P<T>& p) { // 0: outside, 1: inside, 2: boundary
    int cnt = 0;
    for (int i = 0; i < size(); ++i) {
      auto p1 = points[i], p2 = points[(i+1)%size()];
      if (segment(p1, p2).intersect(p)) return 2;
      if (p1.X <= p.X && p2.X > p.X && crossp(p2 - p1, p - p1) < 0) cnt ^= 1;
      else if (p1.X > p.X && p2.X <= p.X && crossp(p1 - p2, p - p2) < 0) cnt ^= 1;
    }
    return cnt;
  }

};

template <typename T>
polygon<T> convex_hull(std::vector<P<T>> points) {
  int n = points.size();
  sort(points.begin(), points.end(), lt<T>);
  polygon<T> pg;
  pg.push_back(points[0]);
  for (int i = 1; i <= 2 * n - 2; ++i) {
    int idx = i < n? i : 2 * n - i - 2, m = pg.size();
    while (m >= 2 && crossp(pg[m-1]-pg[m-2], points[idx] - pg[m-1]) > 0) pg.pop_back(), m--;
    if (idx != 0) pg.push_back(points[idx]);
  }
  return pg;
}

} // namespace geo
} // namespace hy
