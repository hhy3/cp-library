#pragma once

#include <vector>
#include <istream>
#include <ostream>
#include <type_traits>
#include <cassert>
#include <cmath>


namespace hy {
namespace geo {

constexpr double EPS = 1e-10;

template <typename T> struct Point;
template <typename T> struct Circle;
template <typename T> struct Polygon;


template <typename T=double>
struct Point {
  T x, y;

  Point(T _x=0, T _y=0): x(_x), y(_y) {}

  template <typename _T>
  Point(const Point<_T>& rhs): x(rhs.x), y(rhs.y) {};

  T dist2(const Point& rhs) const {
    T dx = x - rhs.x, dy = y - rhs.y;
    return dx * dx + dy * dy;
  }

  T dist(const Point& rhs) const {
    return sqrt(dist2(rhs));
  }

  T cross_product(const Point& rhs) const {
    return x * rhs.y - y * rhs.x;
  }

  T abs() const {
    return sqrt(x * x + y * y);
  }

  template <typename U>
  bool in_circle(const Circle<U>& circle) const {
    if (std::is_integral_v<T> && std::is_integral_v<U>) {
      return dist2(circle.p) < circle.r * circle.r;
    } else {
      return dist2(circle.p) < circle.r * circle.r - EPS;
    }
  }

  friend std::ostream& operator << (std::ostream &os, const Point& p) {
    os << p.x << ' ' << p.y;
    return os;
  }

  friend std::istream& operator >> (std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
  }

};

template <typename T=double>
struct Circle {
  Point<T> p;
  T r;

  Circle(T _x=0, T _y=0, T _r=0): p(_x, _y), r(_r) {}
  Circle(Point<T> _p, T _r): p(_p), r(_r) {}

  template <typename _T>
  Circle(const Circle<_T>& rhs): p(rhs.p), r(rhs.r) {}

};


template <typename T>
struct Polygon {
  int n;
  std::vector<Point<T>> points;

  Polygon(int _n): n(_n) {}
  Polygon(const Polygon& rhs): n(rhs.n), points(rhs.points) {}

};

} // namespace geo
} // namespace hy
