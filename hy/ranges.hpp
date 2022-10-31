#pragma once

#include <limits>
#include <set>

namespace hy {

/**
 * Maintain a set of ranges of form \{[l_1, r_1], [l_2, r_2], ..., [l_k,
 * r_k]\} s.t. r_i + 1 < l_{i+1}
 */
template <typename T = int> struct Ranges {
  static constexpr T mi = std::numeric_limits<T>::min() / 2,
                     mx = std::numeric_limits<T>::max() / 2;

  std::set<std::pair<T, T>> st;

  Ranges() { st.emplace(mi, mi), st.emplace(mx, mx); }

  void add(T L, T R) {
    for (auto it = --st.upper_bound({R + 2, mi}); it->second >= L - 1;
         st.erase(it--)) {
      L = min(L, it->first), R = max(R, it->second);
    }
    st.emplace(L, R);
  }

  void remove(T L, T R) {
    T l = mi, r = mi;
    for (auto it = --st.upper_bound({R + 1, mi}); it->second >= L;
         st.erase(it--)) {
      if (it->second > R) {
        st.insert({R + 1, it->second});
      }
      if (it->first < L) {
        st.insert({it->first, L - 1});
      }
    }
  }

  std::pair<T, T> next(T pos) { return *st.lower_bound({pos, mi}); }

  std::pair<T, T> prev(T pos) { return *(--st.lower_bound({pos, mx})); }
};

} // namespace hy
