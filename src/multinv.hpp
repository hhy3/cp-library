#pragma once

#include <vector>

/**
 * @brief 求出1-n的关于质数p的乘法逆元
 *        
 *        简介: https://oi-wiki.org/math/number-theory/inverse/
 *        模板题: https://www.luogu.com.cn/problem/P3811       
 *        
 *        Time Complexity: O(n)
 * 
 * @param n 
 * @param p 
 * @return std::vector<int> 
 */
std::vector<int> multinv(int n, int p) {
  std::vector<int> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = long(p - p / i) * inv[p % i] % p;
  }
  return inv;
}