#pragma once

#include <map>
#include <functional>

namespace hy {
namespace ds {

template <typename T=int>
struct MonotoneStack {
  using binary_op = function<bool(T, T)>;
  binary_op pred;
  int id; // default index
  MonotoneStack(binary_op pred_, int id_=-1): pred(pred_), id(id_) {}
  std::vector<std::pair<int, T>> stk;
  int insert(int idx, T val) { // ans is the nearest index s.t. pred(f[ans], f[i]) is true.
    while (stk.size() && !pred(stk.back().second, val)) stk.pop_back();
    int ans = stk.empty()? id : stk.back().first;
    stk.emplace_back(idx, val); 
    return ans;
  }
};

}
}