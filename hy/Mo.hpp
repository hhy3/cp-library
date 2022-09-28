#pragma once

#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include <cmath>

namespace hy {

struct Mo {
  int n;
  std::vector<int>& dat;
  Mo(std::vector<int>& dat): n((int)dat.size()), dat(dat) {}

  std::vector<int> query(const std::vector<std::array<int, 2>>& qs) {
    int q = (int)qs.size(), B = (int)std::sqrt(n);
    std::vector<int> idx(q);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&] (int i, int j) {
      return qs[i][0] / B < qs[j][0] / B || qs[i][0] / B == qs[j][0] / B && qs[i][1] < qs[j][1];
    });
    std::vector<int> ans(q);
    for (int l = 0, r = -1, i = 0; i < q; ++i) {
      int L = qs[idx[i]][0], R = qs[idx[i]][1];
      while (L < l) move(--l, 1); // 先扩大
      while (r < R) move(++r, 1);
      while (l < L) move(l++, -1); // 再缩小
      while (R < r) move(r--, -1);
      ans[idx[i]] = calc_ans(); 
    }
    return ans;
  }

  void move(int pos, int sign) {
    // TODO
  }

  int calc_ans() {
    // TODO
  }
};

}
